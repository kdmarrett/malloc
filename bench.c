// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// bench.c for dist program

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"

extern newBlock * free_list;
extern uintptr_t tsize;

int main(int argc, char** argv) {
	//manually add block
	free_list = malloc(500);
	free_list->size = 500-sizeof(*free_list);
	newBlock* h1;
	h1 = malloc(700);
	h1->size = 700 - sizeof(*h1);
	free_list->next = h1;
	newBlock* h2;
	h2 = malloc(900);
	h2->size = 900 - sizeof(*h2);
	h1->next = h2;

	newBlock* h3;
	h3 = malloc(1000);
	h3->size = 1000 - sizeof(*h3);
	h2->next = h3;
	
	newBlock* h4;
	h4 = malloc(2050);
	h4->size = 2050 - sizeof(*h3);
	h3->next = h4;
	//testing getmem
	/*newBlock* test;
	test = getmem(400); 
	int pr = (int) test->size;
	printf("%d\n", pr);
	printf("%p\n", test);*/
	//getmem(200);
	//getmem(479);
	//getmem(983);
	getmem(1030); 
	getmem(5000);
	//testing get_mem_stats
	uintptr_t *total_size = (uintptr_t *) malloc(sizeof(uintptr_t));
	uintptr_t *total_free = (uintptr_t *) malloc(sizeof(uintptr_t));
	uintptr_t *n_free_blocks = (uintptr_t *) malloc(sizeof(uintptr_t));
	get_mem_stats(total_size, total_free, n_free_blocks);
	printf("%lu\n", *total_size);
	printf("%lu\n", *total_free);
	printf("%lu\n", *n_free_blocks);
	//testing print_heap
	FILE *f;
	f = fopen("test", "w+");
	print_heap(f);
	fclose(f);
	return 0;
}
