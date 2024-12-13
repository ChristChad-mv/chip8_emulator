/**
 * @file ram.h
 * @brief Defines the RAM structure and functions for the Chip8 emulator.
 *
 * This header file declares the "ram" structure and its associated functions,
 * which manage the memory operations for the Chip8 emulator like reading,
 * writing, initializing, and loading programs into memory.
 */

#ifndef RAM_H
#define RAM_H

#include <stdint.h>

/**
 * @struct ram
 * @brief Represents the RAM structure for the Chip8 emulator.
 *
 * Contains a pointer to a dynamically allocated memory array, which is used as a Chip8 memory.
 */
struct ram {
    uint8_t *memory;
};

/**
 * @brief Initializes the RAM for the Chip8 emulator.
 *
 * @param memory Pointer to the "ram" structure to initialize.
 * @return 
 *      - 0 if the RAM is successfully initialized.
 *      - 1 if failed.
 */
int initialize_RAM(struct ram* memory);

/**
 * @brief Frees the memory allocated for the RAM structure.
 *
 * Releases the dynamically allocated memory and sets the pointer to NULL
 * to prevent errors.
 *
 * @param memory Pointer to the "ram" structure to delete.
 */
void delete_memory(struct ram* memory);

/**
 * @brief Reads a value from a specific address in the RAM.
 *
 * Checks if the address is valid. If valid, retrieves the
 * value at the specified address and stores it in the provided "res" pointer.
 *
 * @param memory - Pointer to the "ram" structure.
 * @param address - The memory address to read from.
 * @param res - Pointer to store the value read from memory.
 * @return 
 *      - 0 if the read operation is successful.
 *      - 1 if the address is invalid.
 */
int read_memory(struct ram* memory, uint16_t address, uint8_t* res);

/**
 * @brief Writes a value to a specific address in the RAM.
 *
 * Checks if the address is valid. If valid, writes the
 * value given as a parameter to the specified address.
 *
 * @param memory - Pointer to the "ram" structure.
 * @param address - The memory address to write to.
 * @param value - The value to write into memory.
 * @return 
 *      - 0 if the write operation is successful.
 *      - 1 if the address is invalid.
 */
int write_memory(struct ram* memory, uint16_t address, uint8_t value);

/**
 * @brief Loads a binary program into the RAM from a file.
 *
 * Reads the binary file specified by filename and loads its contents into
 * the memory starting at the specific address.
 *
 * @param memory - Pointer to the "ram" structure.
 * @param address - The starting memory address where the program is loaded.
 * @param filename - The path to the binary file to load.
 * @return 
 *      - 0 if the program is successfully loaded.
 *      - 1 if the file cannot be opened or a memory write operation fails.
 */
int load_memory(struct ram* memory, uint16_t address, const char* filename);

#endif
