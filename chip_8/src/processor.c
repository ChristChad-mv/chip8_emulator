/**
 * @file processor.c
 * @brief Implements the processor functions for the Chip8 emulator.
 *
 * This source file provides the definitions for initializing the processor
 * and performing the fetch-decode-execute cycle.
 */

#include <stdio.h>
#include <stdlib.h>
#include "processor.h"
#include "ram.h"
#include <display/display.h>
#include <display/sprite.h>
#include <misc/debug.h>

/**
 * @brief Initializes the processor.
 *
 * Sets up the processor with references to RAM and Display, and initializes
 * the I register, program counter, and general-purpose registers.
 *
 * @param proc Pointer to the processor structure to initialize.
 * @param memory Pointer to the RAM structure.
 * @param display Pointer to the Display structure.
 * @return int
 *      - 0 if initialization is successful.
 *      - 1 if initialization fails.
 */
int initialize_processor(struct processor * proc, struct ram* memory, struct Display * display){
    proc->ram = memory;
    proc->display = display; 
    proc->registerI = 0; 
    proc->counter_program = 512;
    proc->stack_pointer = 0;
	for(int i=0; i < 16; i++) {
		proc->Vx[i] = 0;
		proc->stack[i] = 0;
	}
	
	return 0;
}

/**
 * @brief Fetches, decodes, and executes the next instruction.
 *
 * Performs the fetch-decode-execute cycle for the processor. This function
 * should be called repeatedly in the main emulation loop.
 *
 * @param proc Pointer to the processor structure.
 */

uint16_t fetch_instruction(struct processor* proc) {
	
	uint8_t instruction_part_1, instruction_part_2;
	
	if(read_memory(proc->ram, proc->counter_program, &instruction_part_1) != 0 || 
		read_memory(proc->ram, proc->counter_program + 1, &instruction_part_2) != 0) {
			return 1;
	}
	
	proc->counter_program += 2;
	
	uint16_t instruction = instruction_part_1;
	instruction = instruction << 8;
	instruction = instruction | instruction_part_2;
	
	return instruction;
} 

void fetch_decode_execute(struct processor* proc) {
    uint16_t instruction_fetched = fetch_instruction(proc);
	printf("%s\n", instruction_as_str(instruction_fetched));
	
	
	if ((instruction_fetched & 0xF000) == 0x6000) {
		printf("6xkk\n");
		uint8_t x  = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t kk = instruction_fetched & 0x00FF;
		proc->Vx[x] = kk;
	}
	else if ( (instruction_fetched & 0xF000) == 0xA000 ) {
		printf("Annn\n");
		
		uint16_t n = instruction_fetched & 0x0FFF;
		proc->registerI=n;
		
	}
	else if ( (instruction_fetched & 0xF000) == 0x1000 ) {
		printf("1nnn\n");
		
		uint16_t n = instruction_fetched & 0x0FFF;
		proc->counter_program = n;
		
	} 
	else if ( (instruction_fetched & 0xF000) == 0xD000) {
		printf("Dxyn\n");
		
		uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t y = ( instruction_fetched & 0x00F0) >> 4;
		uint8_t n = instruction_fetched & 0x000F;
		
		uint8_t Vx = proc->Vx[x];
		uint8_t Vy = proc->Vx[y];
		
		struct Sprite sprite;
		Sprite_init(&sprite, n);
		
		for(uint8_t i = 0; i < n; i++) {
			uint8_t byte;
			read_memory(proc->ram, proc->registerI + i, &byte);
			Sprite_add(&sprite, byte);
		}
		Display_DRW(proc->display, &sprite, Vx, Vy, &proc->Vx[0xF]);
		Sprite_destroy(&sprite);
		
	} 
	else if ( instruction_fetched == 0x00E0) {
		printf("00E0\n");
		Display_CLS(proc->display);
		
	} 
	else if  ( (instruction_fetched & 0xF000)== 0x7000){
		printf("7xkk");
		uint8_t x= ( instruction_fetched & 0x0F00) >> 8; 
		uint16_t k= (instruction_fetched & 0x00FF) ;
		
		proc->Vx[x] += k;
		
	} 
	else if ( (instruction_fetched & 0xF000) == 0x3000 ) {
		printf("3xnn");
		uint8_t x = (instruction_fetched & 0x0F00) >> 8;
		uint16_t k = (instruction_fetched & 0x00FF) ;
		if (proc->Vx[x] == k ){			proc->counter_program += 2;
		}
		
	} else if ( (instruction_fetched & 0xF000) == 0x2000 ) {
		printf("2nnn\n");
		
		uint16_t n = instruction_fetched & 0x0FFF;
		
		proc->stack[proc->stack_pointer] = proc->counter_program;
		proc->counter_program = n;
		proc->counter_program = proc->stack[proc->stack_pointer];
	}
	else if ( (instruction_fetched & 0xF000) == 0x4000 ) {
		printf("4xnn");
		uint8_t x = (instruction_fetched & 0x0F00) >> 8;
		uint16_t k = (instruction_fetched & 0x00FF) ;
		if (proc->Vx[x] != k ){
			proc->counter_program += 2;
		}
	}
	else if ( (instruction_fetched & 0xF000) == 0x5000) {
		printf("5xy0\n");
		
		uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t y = ( instruction_fetched & 0x00F0) >> 4;
		
		uint8_t Vx = proc->Vx[x];
		uint8_t Vy = proc->Vx[y];
		
		if(Vx == Vy) {
			proc->counter_program += 2;
		}
	}
	else if ( ( instruction_fetched & 0xF000) == 0x8000) {
		printf ("8xy4\n");
		uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t y = ( instruction_fetched & 0x00F0) >> 4;
		
		uint8_t Vx = proc->Vx[x];
		uint8_t Vy = proc->Vx[y];
		
		
		
	}
	else {
		printf("ERROR\n");
	}
	

}



