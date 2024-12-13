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
    
	for(int i=0; i < 16; i++) {
		proc->Vx[i] = 0;
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
void fetch_decode_execute(struct processor* proc) {
    uint16_t instruction_fetched = fetch_instruction(&proc);
	
}

uint16_t fetch_instruction(struct processor* proc) {
	
	uint8_t instruction_part_1, instruction_part_2;
	
	if(read_memory(proc->ram, proc->counter_program, instruction_part_1) != 0 || 
		read_memory(proc->ram, proc->counter_program + 1, instruction_part_2) != 0) {
			return 1;
	}
	
	uint16_t instruction = instruction_part_1;
	instruction << 8;
	instruction = instruction | instruction_part_2;
	
	return instruction;
}