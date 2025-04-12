/**
 * @file ram.c
 * @brief Memory management for the Chip8 emulator.
 *
 * This module provides functions to initialize, free, read from, and write to
 * the RAM. It also includes functionality to load programs from binary files into memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include "include/ram.h"
#include <misc/debug.h>

/**
 * @brief Initializes the RAM for the Chip8 emulator.
 *
 * Allocates 4096 bytes of memory for the RAM structure.
 *
 * @param memory pointer to the RAM structure to be initialized.
 * @return 
 *      - 0 if initialization is successful.
 *      - 1 if failed.
 */
int initialize_RAM(struct ram* memory) {
    memory->memory = calloc(4096, sizeof(uint8_t));
    
    if (memory->memory != NULL){
        return 0;
    } else {
        return 1;
    }
}

/**
 * @brief Frees the memory allocated for the RAM structure.
 *
 * Frees both the memory allocated for the data and the RAM structure itself.
 *
 * @param memory Pointer to the RAM structure to be freed.
 */
void delete_memory(struct ram* memory) {
    free(memory->memory);
    free(memory);
}

/**
 * @brief Reads a value from a specific address in RAM.
 *
 * Checks that the address is valid (less than 4096) before reading the value.
 *
 * @param memory Pointer to the RAM structure.
 * @param address Memory address to read from.
 * @param res Pointer where the read value will be stored.
 * @return 
 *      - 0 if the read is successful.
 *      - 1 if the address is out of bounds.
 */
int read_memory(struct ram* memory, uint16_t address, uint8_t* res){
    if(address < 4096) {
        *res = memory->memory[address];
        return 0;
    }
    return 1;
}

/**
 * @brief Writes a value to a specific address in RAM.
 *
 * Checks that the address is valid before writing the value.
 *
 * @param memory Pointer to the RAM structure.
 * @param address Memory address to write to.
 * @param value Value to write into memory.
 * @return 
 *      - 0 if the write is successful.
 *      - 1 if the address is out of bounds.
 */
int write_memory(struct ram* memory, uint16_t address, uint8_t value){
    if(address < 4096) {
        memory->memory[address] = value;
        return 0;
    }
    return 1;
}

/**
 * @brief Loads a binary file into RAM starting from a specified address.
 *
 * Opens the file in binary mode and reads two bytes at a time before writing them into memory
 *
 * @param memory Pointer to the RAM structure.
 * @param address Starting memory address where the file will be loaded.
 * @param filename Name of the binary file to load.
 * 
 * @return 
 *      - 0 if the loading is successful.
 *      - 1 if the file cannot be opened or if a memory write fails.
 */
int load_memory(struct ram* memory, uint16_t address, const char* filename) {
    FILE* id_file = fopen(filename, "rb");
    if(id_file == NULL) {
        return 1;
    }
    
    uint8_t content_file[2];
    
    while (fread(content_file, sizeof(uint8_t), 2, id_file) == 2) {
        int check = write_memory(memory, address++, content_file[0]);
        if(check == 1) {
            fclose(id_file); 
            return 1;
        } 
		
        check = write_memory(memory, address++, content_file[1]);
        if(check == 1) {
            fclose(id_file);
            return 1;
        } 
		
        uint16_t instruction = content_file[0];
        instruction = instruction << 8;
        instruction = instruction | content_file[1];
        printf("%s\n", instruction_as_str(instruction));
    }
    fclose(id_file);
    return 0;
}
