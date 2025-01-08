/**
 * @file processor.h
 * @brief Defines the processor structure and the functions that are associate with it for the Chip8 emulator.
 *
 * This header file declares the "processor" structure, which represents the CPU of the Chip8 emulator.
 * 
*/

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "ram.h"
#include <display/display.h>
#include <keyboard/keyboard.h>
#include <stdint.h>

/**
 * @struct processor
 * @brief Represents the CPU of the Chip8 emulator.
 *
 * Contains references to RAM and Display structures, the I register,
 * the program counter, and the general-purpose registers V0 through VF.
 * 
 * - Pointer to the RAM structure
 * - Pointer to the Display structure
 * - I register used for memory operations
 * - Program counter pointing to the current instruction
 * - General-purpose registers Vx
 * 
 */
struct processor {
    struct ram* ram;          
    struct Display* display;   
    uint16_t registerI;
    int counter_program;       
    uint8_t Vx[16];
	uint16_t stack[16];
	int stack_pointer;
	uint8_t delay_timer;
	uint8_t sound_timer;
};

/**
 * @brief Initializes the processor.
 *
 * Sets up the processor with references to RAM and Display (they're pointers), and initializes
 * the I register, program counter, and general-purpose registers.
 *
 * @param proc Pointer to the processor structure to initialize.
 * @return int
 *      - 0 if successful.
 *      - 1 if failed.
 */
int initialize_processor(struct processor * proc, struct ram* memory, struct Display * display);

/**
 * @brief Fetches, decodes, and executes the next instruction.
 *
 * Performs the fetch-decode-execute cycle for the processor.
 *
 * @param proc pointer to the processor structure.
 */
uint16_t fetch_instruction(struct processor* proc);
void decode_execute(struct processor* proc);


#endif 