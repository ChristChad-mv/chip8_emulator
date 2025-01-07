/*-------------------------------------------------------------------------*
 | Copyright (C) 2024 Département Informatique de PolyTech Tours.          |
 |                                                                         |
 | This file is part of PolyChip8, yet another CHIP 8 emulator.            |
 |                                                                         |
 | PolyChip8 is free software; you can redistribute it and/or modify       |
 | it under the terms of the GNU General Public License as published by    |
 | the Free Software Foundation; either version 3 of the License,          |
 | or (at your option) any later version.                                  |
 |                                                                         |
 | PolyChip8 is distributed in the hope that it will be useful,            |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of          |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            |
 | GNU General Public License for more details.                            |
 |                                                                         |
 | You should have received a copy of the GNU General Public License       |
 | along with this program. If not, see <http://www.gnu.org/licenses/>.    |
 *-------------------------------------------------------------------------*/

/**
 * @file main.c
 * @brief Entry point for the Chip8 emulator.
 *
 * This file contains the main function in which we will manipulate every others functions.
 */

#include <keyboard/keyboard.h>
#include <display/display.h>
#include <misc/debug.h>
#include "ram.h"
#include "processor.h"

/**
 * @brief The main function of the Chip8 emulator.
 *
 * This function performs the following steps:
 * 1. Initializes the RAM.
 * 2. Loads a CHIP-8 program into memory.
 * 3. Initializes the display.
 * 4. Initializes the processor.
 * 5. Enters the main emulation loop to fetch, decode, and execute instructions from binary file.
 *
 * @return int Returns 0 if successful execution.
 */
int main() {
    
    /**
     * Create and initialize RAM.
     * Initializes the RAM structure and allocates memory.
     */
    struct ram Ram;
    int checking = initialize_RAM(&Ram);
	
	write_memory(&Ram, 511, 1);
    if (checking == 1) {
        printf("RAM not initialized.\n");
        return 1;
    } 
    
    /**
     * Load CHIP-8 program into memory.
     * Loads a binary CHIP-8 program from the specified file into RAM starting at address 512.
     */
    const char* program_path = "/home/administrateur/Téléchargements/chip8_emulator/chip_8/5-quirks.ch8";
    if (load_memory(&Ram, 512, program_path) != 0) {
        printf("Failed to load program into memory.\n");
        return 1;
   }
    
    /**
     * Create and initialize the display.
     * Initializes the display with the pixels value
     */
    struct Display display;
    if (Display_init(&display, 10)) {
        printf("Failed to initialize display.\n");
        return 1; 
    } else {
        printf("Display initialized successfully.\n");
    }

    /**
     * Create and initialize the processor.
     * Initializes the processor structure.
     */
    struct processor proc;
    if (initialize_processor(&proc, &Ram, &display) != 0) {
        printf("Failed to initialize processor.\n");
        delete_memory(&Ram);
        return 1;
    }
	else {
		printf("Proc initialized successfully.\n");
	}
	
	while(1) {
		decode_execute(&proc);
		Display_update(&display);
	}
    
    
    return 0;
}