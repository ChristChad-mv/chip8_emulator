/**
 * @file processor.c
 * @brief Implements the processor functions for the Chip8 emulator.
 *
 * This source file provides the definitions for initializing the processor
 * and performing the fetch-decode-execute cycle.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	proc->delay_timer = 0;
	proc->sound_timer = 0;
	
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

void decode_execute(struct processor* proc) {
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
	else if ( (instruction_fetched & 0xF000) == 0xB000 ){
			printf("Bnnn\n");
			uint16_t n = instruction_fetched & 0x0FFF;
			proc->counter_program = n + proc->Vx[0];
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
		Display_DRW(proc->display, &sprite, Vx, Vy, &proc->Vx[0xF]);;
		Sprite_destroy(&sprite);
		
	}
	else if ( instruction_fetched == 0x00E0) {
		printf("00E0\n");
		Display_CLS(proc->display);
	} 
	else if ( instruction_fetched == 0x00EE) {
		printf("00EE\n");
		if (proc->stack_pointer == 0) {
			printf("RET WITH SP==0\n");
		}
		else {
			proc->stack_pointer -= 1;
			proc->counter_program = proc->stack[proc->stack_pointer];
		}
	} 
	else if  ( (instruction_fetched & 0xF000) == 0x7000){
		printf("7xkk\n");
		uint8_t x= ( instruction_fetched & 0x0F00) >> 8; 
		uint16_t k= (instruction_fetched & 0x00FF) ;
		
		proc->Vx[x] += k;
	} 
	else if ( (instruction_fetched & 0xF000) == 0x3000 ) {
		printf("3xnn\n");
		uint8_t x = (instruction_fetched & 0x0F00) >> 8;
		uint16_t k = (instruction_fetched & 0x00FF) ;
		if (proc->Vx[x] == k ){			proc->counter_program += 2;
		}
		
	} else if ( (instruction_fetched & 0xF000) == 0x2000 ) {
		printf("2nnn\n");
		if (proc->stack_pointer == 16) {
			printf("CALL WITH SP==16\n");
		} else {
			uint16_t n = instruction_fetched & 0x0FFF;
			
			proc->stack[proc->stack_pointer] = proc->counter_program;
			proc->stack_pointer += 1;
			proc->counter_program = n;
		}
	}
	else if ( (instruction_fetched & 0xF000) == 0x4000 ) {
		printf("4xnn\n");
		uint8_t x = (instruction_fetched & 0x0F00) >> 8;
		uint8_t k = (instruction_fetched & 0x00FF) ;
		if (proc->Vx[x] != k ){
			proc->counter_program += 2;
		}
	}
	else if ( (instruction_fetched & 0xF00F) == 0x5000) {
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
		
		uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t y = ( instruction_fetched & 0x00F0) >> 4;
        
		//uint8_t Vx = proc->Vx[x];
        uint8_t Vy = proc->Vx[y];
        // pour eviter une confusion puisque la partie 8xy est la meme
        // on utilise un case of 
        
        switch (instruction_fetched & 0x000F) {
            
            case 0x0:
                printf("8xy0\n");
                proc->Vx[x] = proc->Vx[y];
                break;
            case 0x1:
                printf("8xy1\n");
                proc->Vx[x] = proc->Vx[x] | proc->Vx[y];	
                break;
            case 0x2:
                printf("8xy2\n");
                proc->Vx[x] = proc->Vx[x] & proc->Vx[y];
                break;
            case 0x3:
                printf("8xy3\n");
                proc->Vx[x] = proc->Vx[x] ^ proc->Vx[y];
                break;
            case 0x4:
                printf("8xy4\n");
                //uint8_t Vf = proc->Vx[0xF]; // c'est le registre numero 15=F
 
                uint16_t sum = (uint16_t)proc->Vx[x] + proc->Vx[y];
                if ( sum > 255) {
					proc->Vx[0xF] = 1;
                } else {
                    proc->Vx[0xF] = 0;
                }
				proc->Vx[x] = sum & 0xFF;
                break;
            case 0x5:
                printf("8xy5\n");
                if (proc->Vx[x] >= Vy) {
					proc->Vx[0xF] = 1;
				} else {
                    proc->Vx[0xF] = 0;
                }
                proc->Vx[x] -= Vy;
                break;
            case 0x6:
                printf("8xy6\n");
                proc->Vx[0xF] = proc->Vx[x] & (0x01);
				proc->Vx[x] = proc->Vx[x] >> 1;
                break;
            case 0x7:
                printf("8xy7\n");
                if ( proc->Vx[x] < Vy) {
                    proc->Vx[0xF]= 1;
                } else {
                    proc->Vx[0xF]=0;
                }
                proc->Vx[x] = proc->Vx[y] - proc->Vx[x]; 
                break;
            case 0xE : 
               // inverse de 8xy6 
                printf("8xyE\n");
                proc->Vx[0xF] = (proc->Vx[x] >> 7); // recupere le bit le plus significatif et le met dans vf
				proc->Vx[x] = proc->Vx[x] << 1;  //multiplie par deux 
				break;
			default:
				printf("ERROR: 8xy?\n");
        }
    }
    else if ( (instruction_fetched & 0xF000) == 0xF000 ) {

		printf("Fxnn\n");
        uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
        uint8_t Vx = proc->Vx[x];		
        
		// We can now test all version of the instruction Fx.
        switch (instruction_fetched & 0x00FF) {
			
			case 0x07:
				printf("FX07\n");
				proc->Vx[x] = proc->delay_timer;
				break;
			case 0x15:
				printf("FX15\n");
				proc->delay_timer = Vx;
				break;
			case 0x18:
				printf("FX18");
				proc->sound_timer = Vx;
				break;
            case 0x55:
				printf("FX55\n");
				for (uint8_t i = 0; i <= x; i++) {
					write_memory(proc->ram, proc->registerI + i, proc->Vx[i]);
				}
				proc->registerI += x + 1;   
				break;
            case 0x65 : 
				printf ("FX65\n");
				for (uint8_t i = 0; i <= x; i++) {
					uint8_t value;
					read_memory(proc->ram, proc->registerI + i, &value);
					proc->Vx[i]=value;
				}
				proc->registerI += x + 1;   
				break;
            case 0x33 : 
				printf("FX33\n");
				 // ne marche pas !!!!!!!!!!!!!!!!!!!!!!!!!!!!
				// on decortique l'adresse en dizaines unités et centaines et on sauvgarde dans registrI
				// registerI+1 et I+2 d'ou l'incrementation de 3
				uint8_t hundreds = (uint8_t)(Vx / 100);
				uint8_t tens = (uint8_t)((Vx / 10) % 10);
				uint8_t ones = (uint8_t)(Vx % 10);
				
				write_memory(proc->ram, proc->registerI, hundreds);
				write_memory(proc->ram, proc->registerI+1, tens);
				write_memory(proc->ram, proc->registerI+2, ones);
				
				break;
            case 0x1E : 
				printf("FX1E\n");
				proc->registerI = proc->registerI + Vx;
				break; 
			default:
				printf("ERROR: Fx??\n");
        }
	}
	else if ( (instruction_fetched & 0xF0FF) == 0xE0A1 ) {
		proc->counter_program += 2;
	}
	else if ( (instruction_fetched & 0xF000) == 0x0000 ) {
		printf("0nnn\n");
	}
	else {
		printf("ERROR: %u\n", instruction_fetched);
	}
}