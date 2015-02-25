// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// mem.h for dist program

#ifndef MEM_H
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>

void* getmem(uintptr_t size);
void freemem(void* p);
void get_mem_stats(uintptr_t* total_size, uintptr_t* 
	total_free, uintptr_t* n_free_blocks);
void print_heap(FILE* f);

#endif