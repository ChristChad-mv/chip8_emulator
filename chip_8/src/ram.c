#include <stdio.h>
#include <stdlib.h>
#include "include/ram.h"
#include <misc/debug.h>

int initialize_RAM(struct ram* memory) {
	memory->memory = calloc(4096, sizeof(uint8_t));
	
	if (memory->memory != NULL){
		return 0;
	}else {
		return 1;
	}
}

void delete_memory(struct ram* memory) {
	free(memory->memory);
	free(memory);
}

int read_memory(struct ram* memory, uint16_t address, uint8_t* res){
	if(address < 4096) {
		*res = memory->memory[address];
		return 0;
	}
	return 1;
}

int write_memory(struct ram* memory, uint16_t address, uint8_t value){
	if(address < 4096) {
		memory->memory[address] = value;
		return 0;
	}
	return 1;
}

int load_memory(struct ram* memory, uint16_t address, const char* filename) {
	FILE* id_file = fopen(filename, "rb");
	if(id_file == NULL) {
		return 1;
	}
	
	uint8_t content_file[2];
	
	while (fread(content_file, sizeof(uint8_t), 2, id_file) == 2) {
		int check = write_memory(memory, address++, content_file[0]);
		if(check == 1) {
			return 1;
		} 
		check = write_memory(memory, address++, content_file[1]);
		if(check == 1) {
			return 1;
		} 
		uint16_t instruction = content_file[0];
		instruction = instruction << 8;
		instruction = instruction | content_file[1];
		printf("%s\n", instruction_as_str(instruction));
	}
	return 0;
}
