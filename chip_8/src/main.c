/*-------------------------------------------------------------------------*
 | Copyright (C) 2023 Département Informatique de PolyTech Tours.          |
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

#include <display/display.h>
#include <misc/debug.h>
#include "ram.h"

int main() {
        struct ram Ram;
		int checking= initialize_RAM(&Ram);
		if (checking == 1) {
			printf ("Ram not initialized");
		} 
		
		load_memory(&Ram, 512,"/home/administrateur/Téléchargements/chip8_emulator/chip_8/1-chip8-logo.ch8");
		return 0;
}