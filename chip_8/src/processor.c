/**
 * @file processor.c
 * @brief Implements the processor functions for the Chip8 emulator.
 * @Author MERABTENE and MVOUNGOU 
 * This source file provides the definitions for initializing the processor
 * and performing the fetch-decode-execute cycle.
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
int initialize_processor(struct processor * proc, struct ram* memory, struct Display * display, struct Keyboard * keyboard ,struct Speaker * speaker){
    proc->ram = memory;
    proc->display = display; 
    proc ->keyboard=keyboard;
    proc->registerI = 0; 
    proc->counter_program = 512;
    proc->stack_pointer = 0;
	proc->delay_timer = 0;
	proc->sound_timer = 0;
	proc->speaker=speaker;
	
	for(int i=0; i < 16; i++) {
		proc->Vx[i] = 0;
		proc->stack[i] = 0;
	}
	return 0;
}
/**
 * @brief Reads the instruction from the RAM fitches it and then move to the next instruction
 *
 * This function should be called repeatedly in the main emulation loop.
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
/**
 * @brief Decode the fetched instruction 
 * This function is to call repeatedly in the main emulation loop.
 * 
 * @param proc
 */
void decode_execute(struct processor* proc) {
    uint16_t instruction_fetched = fetch_instruction(proc);
	printf("%s\n", instruction_as_str(instruction_fetched));
	
	// 6xkk Load the regiter Vx[x]  with the value of kk
	if ((instruction_fetched & 0xF000) == 0x6000) {
		uint8_t x  = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t kk = instruction_fetched & 0x00FF;
		proc->Vx[x] = kk;
	}
	// Annn Set the registerI to nnn
	else if ( (instruction_fetched & 0xF000) == 0xA000 ) {
		
		uint16_t n = instruction_fetched & 0x0FFF;
		proc->registerI=n;
	}
	// Bnnn jump to location n+Vx[0]
	else if ( (instruction_fetched & 0xF000) == 0xB000 ){
		uint16_t n = instruction_fetched & 0x0FFF;
		proc->counter_program = n + proc->Vx[0];
	}
	 // 1nnn jump to location nnn
	else if ( (instruction_fetched & 0xF000) == 0x1000 ) {		
		uint16_t n = instruction_fetched & 0x0FFF;
		proc->counter_program = n;
		
	} 
	// Dxyn Draw the sprite at coordiante (Vx[x], Vx[y] with n bytes of sprite data
	else if ( (instruction_fetched & 0xF000) == 0xD000) {
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
	//00E0 Clear the display 
	else if ( instruction_fetched == 0x00E0) {
		Display_CLS(proc->display);
	} 
	// 00EE returning from a subroutine (a return from calling a function)
	else if ( instruction_fetched == 0x00EE) {
		if (proc->stack_pointer == 0) {
			printf("RET WITH SP==0\n");
		}
		else {
			proc->stack_pointer -= 1;
			proc->counter_program = proc->stack[proc->stack_pointer];
		}
	} 
	// 7xkk Adds the value kk to the value of register Vx[x]
	else if  ( (instruction_fetched & 0xF000) == 0x7000){
		uint8_t x= ( instruction_fetched & 0x0F00) >> 8; 
		uint16_t k= (instruction_fetched & 0x00FF) ;
		
		proc->Vx[x] += k;
	} 
	// 3xnn increments the program_counter by 2 if Vx[x]=k
	else if ( (instruction_fetched & 0xF000) == 0x3000 ) {
		uint8_t x = (instruction_fetched & 0x0F00) >> 8;
		uint16_t k = (instruction_fetched & 0x00FF) ;
		if (proc->Vx[x] == k ){
			proc->counter_program += 2;
		}
		
	}
	// 2nnn call subroutine at address nnn
	else if ( (instruction_fetched & 0xF000) == 0x2000 ) {
		if (proc->stack_pointer == 16) {
			printf("CALL WITH SP==16\n");
		} else {
			uint16_t n = instruction_fetched & 0x0FFF;
			
			proc->stack[proc->stack_pointer] = proc->counter_program;
			proc->stack_pointer += 1;
			proc->counter_program = n;
		}
	}
	// 4xnn if Vx[x] != k skip to the next instruction
	else if ( (instruction_fetched & 0xF000) == 0x4000 ) {
		uint8_t x = (instruction_fetched & 0x0F00) >> 8;
		uint8_t k = (instruction_fetched & 0x00FF) ;
		if (proc->Vx[x] != k ){
			proc->counter_program += 2;
		}
	}
	//5xy0 Skip next instruction if Vx[x] =Vx[y]
	else if ( (instruction_fetched & 0xF00F) == 0x5000) {

		uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t y = ( instruction_fetched & 0x00F0) >> 4;
		
		uint8_t Vx = proc->Vx[x];
		uint8_t Vy = proc->Vx[y];
		
		if(Vx == Vy) {
			proc->counter_program += 2;
		}
	}
	// instructions type 8xy..
	else if ( ( instruction_fetched & 0xF000) == 0x8000) {
		
		uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
		uint8_t y = ( instruction_fetched & 0x00F0) >> 4;
        
        uint8_t Vy = proc->Vx[y];
		uint8_t Vx=proc->Vx[x];
        // we used a switch case to avoid any confuse if use of classic if condition for 
		// all the instructions that got the same mask
        switch (instruction_fetched & 0x000F) {
            
            case 0x0:
                proc->Vx[x] = Vy;
                break;
            case 0x1:
                proc->Vx[x] = proc->Vx[x] | proc->Vx[y];
                proc->Vx[0xF]=0;
                break;
            case 0x2:
                proc->Vx[x] = proc->Vx[x] & proc->Vx[y];
                proc->Vx[0xF]=0;
                break;
            case 0x3:
                proc->Vx[x] = proc->Vx[x] ^ proc->Vx[y];
                proc->Vx[0xF]=0;
                break;
            case 0x4:
                uint16_t sum = (uint16_t)proc->Vx[x] + proc->Vx[y];
				proc->Vx[x] = sum & 0xFF;
                if ( sum > 255) {
					proc->Vx[0xF] = 1;
                } else {
                    proc->Vx[0xF] = 0;
                }
                break;
            case 0x5:
				proc->Vx[x] = proc->Vx[x] - proc->Vx[y];
				if( Vx >= proc->Vx[y]) {
					proc->Vx[0xF] = 1;
				} else {
					proc->Vx[0xF] = 0;
				}
				
                break;
            case 0x6:
				proc->Vx[x] = proc->Vx[y] >> 1;
                proc->Vx[0xF] = Vy & (0x01);
                break;
            case 0x7:
                proc->Vx[x] = proc->Vx[y] - proc->Vx[x]; 
                if ( proc->Vx[x] < proc->Vx[y]) {
                    proc->Vx[0xF]= 1;
                } else {
                    proc->Vx[0xF]=0;
                }
                break;
            case 0xE :
				proc->Vx[x] = proc->Vx[y] << 1;    
                proc->Vx[0xF] = (Vy >> 7);  
				break;
			default:
				printf("ERROR: 8xy?\n");
        }
    }
	// instructions type Fx..
    else if ( (instruction_fetched & 0xF000) == 0xF000 ) {
        uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
        
        switch (instruction_fetched & 0x00FF) {
            
			case 0x0A : 
                uint8_t pressed;
				if(Keyboard_wait(proc->keyboard, &pressed) == 1) {
					printf("There's a issue with Fx0A instruction");
				}
				proc->Vx[x]=pressed;
                break;
				
			case 0x07:
				proc->Vx[x] = proc->delay_timer;
				break;
				
			case 0x15:
				proc->delay_timer = proc->Vx[x];
				break;
				
			case 0x18:
				proc->sound_timer = proc->Vx[x];
				break;
				
            case 0x55:
				for (uint8_t i = 0; i <= x; i++) {
					if(write_memory(proc->ram, proc->registerI + i, proc->Vx[i]) == 1) {
						printf("There's a error here : Fx55");
					}
				}
				proc->registerI += x + 1;   
				break;
				
            case 0x65 : 
				for (uint8_t i = 0; i <= x; i++) {
					uint8_t value;
					if(read_memory(proc->ram, proc->registerI + i, &value) == 1) {
						printf("There's a error here : Fx65");
					}
					proc->Vx[i]=value;
				}
				proc->registerI += x + 1;   
				break;
				
            case 0x33 : 
				uint8_t hundreds = (uint8_t)(proc->Vx[x] / 100);
				uint8_t tens = (uint8_t)((proc->Vx[x] / 10) % 10);
				uint8_t ones = (uint8_t)(proc->Vx[x] % 10);
				
				write_memory(proc->ram, proc->registerI, hundreds);
				write_memory(proc->ram, proc->registerI+1, tens);
				write_memory(proc->ram, proc->registerI+2, ones);
				
				break;
				
            case 0x1E : 
				proc->registerI = proc->registerI + proc->Vx[x];
				break; 
			default:
				printf("ERROR: Fx??\n");
        }
	}
	// instructions for the keyboard 
	else if ( (instruction_fetched & 0xF000) == 0xE000 ) {
        uint8_t x = ( instruction_fetched & 0x0F00 ) >> 8;
        int pressed;
        switch (instruction_fetched & 0x00FF){
            case 0xA1 :
                if (Keyboard_get(proc->keyboard,proc->Vx[x],&pressed) == 0 && pressed==KEY_UP) {
                    proc->counter_program += 2;
                }
                break;
            case 0x9E : 
                if ( Keyboard_get(proc->keyboard,proc->Vx[x],&pressed) == 0 && pressed==KEY_DOWN){
                    proc->counter_program += 2;
                }
                break;
            
            default:
                printf("ERROR : EX?\n");
        }
	}
	//0nnn Jump to a machine code routine at nnn.
	else if ( (instruction_fetched & 0xF000) == 0x0000 ) {
		printf("0nnn\n");
	} 
	//9xy0 skip to the next instruction if Vx[x] !=Vx[y]
    else if ( (instruction_fetched & 0xF000) == 0x9000 ) {
        uint8_t x=(instruction_fetched & 0x0F00) >> 8;
        uint8_t y=(instruction_fetched & 0x00F0) >> 4;
        if (proc->Vx[x] != proc->Vx[y]){
            proc->counter_program +=2;
        }
	}
    // for all other instruction not recognized !
	else {
		printf("ERROR: %u\n", instruction_fetched);
	}
}
