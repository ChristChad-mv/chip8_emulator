#include <stdio.h>
#include <stdlib.h>
#include "include/ram.h"


int initialize_RAM() {
	memory = (struct ram*)malloc(sizeof(struct ram));
	memory->memory = calloc(4096, sizeof(unit8_t));
	
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

int read_memory(struct ram* memory, unit16_t address, unit8_t* res){
	if(address < 4096 && address >= 512) {
		*res = memory->memory[address];
		return 0;
	}
	return 1;
}

int write_memory(struct ram* memory, unit16_t address, unit16_t value){
	if(address < 4096 && address >= 512) {
		memory->memory[address] = value;
		return 0;
	}
	return 1;
}

int load_memory(struct ram* memory, unit16_t address, const char* filename) {
	FILE* id_file = fopen(filename, "rb");
	if(id_file == NULL) {
		return 1;
	}
	
	unit8_t content_file[2];
	
	size_t number_instruction; 
	while (fread(content_file, sizeof(unit8_t), 2, id_file) == 2) {
		unit16_t instruction = content_file[0];
		instruction = instruction << 8;
		instruction = instruction | content_file[1];
		int check = write_memory(memory, adress, instruction);
		if(check == 1) {
			return 1;
		} 
	}
	return 0;
}