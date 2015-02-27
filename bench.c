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

int main(int argc, char** argv) {
	//manually add block
	free_list = malloc(500);
	free_list->size = 500-sizeof(*free_list);
	newBlock* h1;
	h1 = malloc(700);
	h1->size = 700 - sizeof(*h1);
	free_list->next = h1;
	newBlock* h2;
	h2 = malloc(5000);
	h2->size = 5000 - sizeof(*h2);
	h1->next = h2;

	newBlock* h3;
	h3 = malloc(6000);
	h3->size = 6000 - sizeof(*h3);
	h2->next = h3;
	//testing getmem
	getmem(3200); 
	//getmem(200);
	//getmem(500);
	//testing print_heap
	FILE *f;
	f = fopen("test", "w+");
	print_heap(f);
	fclose(f);
	return 0;
}
