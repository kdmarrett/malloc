// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// print_heap.c that prints free list in given format for dist program

#include "mem_impl.h"
#include "mem.h"

//not done yet
extern struct newBlock* free_list;

void print_heap(FILE * f) {
	struct newBlock* current = free_list;
	if(free_list == NULL) {
		printf("The list is NULL\n");
		return;
	}else if(f == NULL){
		printf("file does not exist\n");
		return;
	}else{
		while(current != NULL) {
			printf("123");
			//current = current->next;
		}
	}

}
