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
    
}
