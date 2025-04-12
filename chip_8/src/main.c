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
 * @authors MERABTENE and MVOUNGOU
 * @date January 2025
 *
 * This file contains the main function that initializes and controls the emulator.
 */

#include "chip8machine.h"
#include <SDL2/SDL.h>

/**
 * @brief The main function of the Chip8 emulator.
 *
 * This function performs the following steps:
 * 1. Initializes the Chip8 machine, which contains various components.
 * 2. Enters the main emulation loop to fetch, decode, and execute instructions.
 *
 * @return int Returns 0 if successful execution.
 */
int main() {
    struct Chip8machine machine;

    // ROM path
    const char *rom_path = "/home/audrey/Bureau/chip8_emulator/chip_8/5-quirks.ch8";

    // Initialize the Chip8 machine
    if (Chip8machine_create(&machine, rom_path) != 0) {
        printf("System initialization failed\n");
        return 1;
    }

    Uint32 current_timer = SDL_GetTicks();

    // Main emulation loop
    while (1) {
        decode_execute(&machine.proc);
        Display_update(&machine.display);

        Uint32 final_timer = SDL_GetTicks();
        Uint32 time_passed = final_timer - current_timer;

        // Handle timers (delay and sound)
        if (time_passed >= 16) {
            if (machine.proc.delay_timer > 0) {
                 if (machine.proc.delay_timer >time_passed/16){
                                         machine.proc.delay_timer=machine.proc.delay_timer - (time_passed /16);
                                 } else {
                                         machine.proc.delay_timer=0;
                                 }
            }

            if (machine.proc.sound_timer > 0) {
                machine.proc.sound_timer -= time_passed / 16;
                Speaker_on(machine.proc.speaker);
            } else {
                Speaker_off(machine.proc.speaker);
            }

            current_timer = SDL_GetTicks();
        }

        SDL_Delay(1);
    }
    return 0;
}