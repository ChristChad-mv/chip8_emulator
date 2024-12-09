#ifndef RAM_H
#define RAM_H

struct ram {
	unit8_t *memory;
};

int initialize_RAM(struct ram* memory);
void delete_memory(struct ram* memory);
int read_memory(struct ram* memory, unit16_t address, unit8_t* res);
int write_memory(struct ram* memory, unit16_t address, unit8_t value);
int load_memory(struct ram* memory, unit16_t address, const char* filename);


#endif