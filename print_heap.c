// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// print_heap.c that prints free list in given format for dist program

# include "mem_impl.h"
extern uintptr_t hsize;

//takes FILE f as parameter
//writes the address and size of each block in free_list into the given file
//if free_list or the file is null, it will print the corresponding error messages

void print_heap(FILE * f) {
	newBlock* current = free_list;
	if(free_list == NULL) {
		printf("The list is NULL\n");
		return;
	}else if(f == NULL){
		printf("file does not exist\n");
		return;
	}else{
		while(current != NULL) {
			fprintf(f, "address: %p size: %d \n", current, (int)current->size);
			current = current->next;
		}
	}

}
