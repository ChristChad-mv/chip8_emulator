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
 * @author MERABTENE and MVOUNGOU
 * @date January 2025
 * This file contains the main function in which we will manipulate every other function.
 */

#include <keyboard/keyboard.h>
#include <display/display.h>
#include <misc/debug.h>
#include "ram.h"
#include "processor.h"
#include <speaker/speaker.h>
/**
 * @brief The main function of the Chip8 emulator.
 *
 * This function performs the following steps:
 * 1. Initializes the RAM.
 * 2. Loads a CHIP-8 program into memory.
 * 3. Initializes the display.
 * 4. Initializes the Keyboard
 * 5. Initializes the speaker.
 * 6. Initializes the processor.
 * 7. Enters the main emulation loop to fetch, decode, and execute instructions from binary file.
 *
 * @return int Returns 0 if successful execution.
 */
int main() {
    
    /**
     * Creating and initializing the RAM.
     * Initializes the RAM structure and allocates memory.
     */
    struct ram Ram;
    int checking = initialize_RAM(&Ram);

    if (checking == 1) {
        printf("RAM not initialized.\n");
        return 1;
    } 
    
    /**
     * Load CHIP-8 program into memory.
     * Loads a binary CHIP-8 program from the specified file into RAM starting at address 512.
     */
    const char* program_path = "/home/administrateur/Téléchargements/chip8_emulator/chip_8/Paddles.ch8";
    if (load_memory(&Ram, 512, program_path) != 0) {
        printf("Failed to load program into memory.\n");
        return 1;
   }
    
    /**
     * Create and initialize the display.
     * Initializes the display with the pixels value
     */
    struct Display display;
    if (Display_init(&display, 15)) {
        printf("Failed to initialize display.\n");
        return 1; 
    } else {
        printf("Display initialized successfully.\n");
		// personalizing the window with RGB colors  
		uint8_t screen_r= 50, screen_g=51, screen_b=51;
		uint8_t details_r=72,details_g=133, details_b=123;
		if (Display_set_colors (&display, screen_r,screen_g,screen_b,details_r,details_g,details_b) !=0){
			printf("Failed to set the display colors : %s\n", SDL_GetError());
			return 1;
		} else {
			printf("Display colors set successfuly \n");
		}
    }
    /**
	 * Create and initialize the keyboard.
     */
    struct Keyboard keyboard;
    if (Keyboard_init(&keyboard)){
        printf("failed to connect the keyboard");
        return 1;
    }else {
        printf("keyboard integred successfully");
    }
    /**
	 * Create and Initialize the speaker.
     */
    struct Speaker speaker;
    if (Speaker_init(&speaker)){
        printf("Failed to connect the speaker\n");
        return 1;
    }else {
        printf("Speaker integred successfully");
    }
    /**
     * Create and initialize the processor.
     * Initializes the processor structure.
     */
    struct processor proc;
	
    if (initialize_processor(&proc, &Ram, &display, &keyboard,&speaker) != 0) {
        printf("Failed to initialize processor.\n");
        delete_memory(&Ram);
        return 1;
    }
	else {
		printf("Proc initialized successfully.\n");
	}
	

	Uint32 current_timer = SDL_GetTicks();
	 // The main emulation loop of the program 
	while(1) {
		
		decode_execute(&proc);
		Display_update(&display);
		
		Uint32 final_timer = SDL_GetTicks();
		Uint32 time_passed = final_timer - current_timer;
		printf("\n%d\n\n", proc.delay_timer);
		if (time_passed >= 16) {
			if (proc.delay_timer > 0) {
				if (proc.delay_timer > time_passed /16) {
					proc.delay_timer-= (time_passed / 16);
			} else {
				proc.delay_timer=0;
			}
			}
			
			if (proc.sound_timer > 0) {
				if (proc.sound_timer > time_passed /16) {
					proc.sound_timer-= (time_passed / 16);
			} else {
				proc.sound_timer=0;
			}
			}
			
			current_timer = SDL_GetTicks();
		}
		SDL_Delay(1);
		
		printf("%d\n\n\n", proc.delay_timer);
	}
    
    
    return 0;
}

