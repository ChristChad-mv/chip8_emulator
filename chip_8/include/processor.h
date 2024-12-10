#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "ram.h"
#include <display/display.h>

struct processor {
	struct ram* ram;
	struct Display* display;
	uint16_t registerI;
	int counter_program;
	uint8_t Vx[16];
};
int initialize_processor(struct processor * proc);
void fetch_decode_execute(struct processor* proc);


#endif