#ifndef RAM_H
#define RAM_H

#include <stdint.h>

struct ram {
	uint8_t *memory;
};

int initialize_RAM(struct ram* memory);
void delete_memory(struct ram* memory);
int read_memory(struct ram* memory, uint16_t address, uint8_t* res);
int write_memory(struct ram* memory, uint16_t address, uint8_t value);
int load_memory(struct ram* memory, uint16_t address, const char* filename);


#endif