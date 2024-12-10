#include <stdio.h>
#include <stdlib.h>
#include "processor.h"
#include "ram.h"
#include <display/display.h>


int initialize_processor(struct processor * proc, struct ram* memory, struct Display * display){
	proc->ram = memory;
	proc->display = display; 
	proc->registerI = 0; 
	proc->counter_program = 512;
	proc->Vx = {0};
 }