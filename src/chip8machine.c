/**
 * @file chip8machine.c
 * @brief Implements the functions of the Chip8 machine.
 * @authors MERABTENE and MVOUNGOU
 * 
 * This source file provides the definitions for initializing the Chip8 machine structure,
 * including its components such as RAM, display, keyboard, speaker, and processor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <speaker/speaker.h>
#include "processor.h"
#include "ram.h"
#include <display/display.h>
#include <display/sprite.h>
#include <misc/debug.h>
#include <keyboard/keyboard.h>
#include "chip8machine.h"

/**
 * @brief Initializes the Chip8 machine, including its components.
 *
 * This function initializes all the components of the Chip8 machine (RAM, display, keyboard,
 * speaker, and processor) and loads a specified ROM into memory.
 *
 * @param machine A pointer to the Chip8 machine structure to initialize.
 * @param rom_path The path to the ROM file to load into memory.
 * @return 0 on success, 1 on failure.
 */
int Chip8machine_create(struct Chip8machine *machine, const char *rom_path) {
    // Initialize RAM
    if (initialize_RAM(&machine->Ram) != 0) {
        printf("Failed to initialize RAM.\n");
        return 1;
    }

    // Load the ROM into memory starting at address 512
    if (load_memory(&machine->Ram, 512, rom_path) != 0) {
        printf("Failed to load program into memory.\n");
        return 1;
    }

    // Initialize Display
    if (Display_init(&machine->display, 15) != 0) {
        printf("Failed to initialize display.\n");
        return 1;
    }

    // Set Display Colors
    uint8_t screen_r = 50, screen_g = 51, screen_b = 51;
    uint8_t details_r = 72, details_g = 133, details_b = 123;
    if (Display_set_colors(&machine->display, screen_r, screen_g, screen_b, details_r, details_g, details_b) != 0) {
        printf("Failed to set display colors: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize Keyboard
    if (Keyboard_init(&machine->keyboard) != 0) {
        printf("Failed to initialize keyboard.\n");
        return 1;
    }

    // Initialize Speaker
    if (Speaker_init(&machine->speaker) != 0) {
        printf("Failed to initialize speaker.\n");
        return 1;
    }

    // Initialize Processor
    if (initialize_processor(&machine->proc, &machine->Ram, &machine->display, &machine->keyboard, &machine->speaker) != 0) {
        printf("Failed to initialize processor.\n");
        return 1;
    }

    // Successful initialization
    return 0;
}
