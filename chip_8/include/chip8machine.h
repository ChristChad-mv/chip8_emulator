/**
 * @file chip8machine.h
 * @brief Defines the Chip8 machine structure and functions to initialize its components.
 * 
 * This file declares the structure representing the Chip8 machine and provides
 * functions for creating and managing its components, such as RAM, display, keyboard, 
 * speaker, and processor.
 * 
 * @authors MERABTENE and MVOUNGOU
 */

#ifndef CHIP8MACHINE_H
#define CHIP8MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include <display/display.h>
#include <keyboard/keyboard.h>
#include "processor.h"
#include <speaker/speaker.h>

/**
 * @struct Chip8machine
 * @brief Represents the Chip8 machine.
 *
 * This structure contains the main components required by the Chip8 emulator:
 * - RAM (`struct ram`)
 * - Display (`struct Display`)
 * - Keyboard (`struct Keyboard`)
 * - Speaker (`struct Speaker`)
 * - Processor (`struct processor`)
 */
struct Chip8machine {
    struct ram Ram;
    struct Display display;
    struct Keyboard keyboard;
    struct Speaker speaker;
    struct processor proc;
};

/**
 * @brief Initializes the Chip8 machine with its components.
 * 
 * Allocates and initializes each component of the Chip8 machine.
 *
 * @param machine A pointer to the Chip8 machine structure to initialize.
 * @param rom_path The path to the ROM file to load into memory.
 * @return 0 on success, 1 on failure.
 */
int Chip8machine_create(struct Chip8machine *machine, const char *rom_path);


#endif
