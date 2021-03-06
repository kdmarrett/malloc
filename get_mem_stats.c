// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// get_mem_stats.c for dist program

#include "mem_impl.h"
extern uintptr_t hsize;

void get_mem_stats(uintptr_t* total_size,
	uintptr_t* total_free, uintptr_t* n_free_blocks) {
	*total_size = tsize; // assigned by the global var
	newBlock* current = free_list;
	uintptr_t tf = 0;
	uintptr_t nfb = 0;
	while(current != NULL) {
		nfb++;
		tf = tf + current->size;
		current = current->next;
	}
	*total_free = tf;
	*n_free_blocks = nfb;
}
