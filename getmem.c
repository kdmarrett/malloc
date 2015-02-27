// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// getmem.c that implements malloc function for dist program

#include "mem.h"
#include "mem_impl.h"

#define MSIZE 4000
#define THRESHOLD 32

newBlock* free_list = NULL;
uintptr_t tsize = 0;

void* getmem(uintptr_t size) {	
	if(size < 0) { //if size is less than zero
		return NULL;
	}else if(free_list == NULL) { //if list is empty
		//use malloc to create a block
		newBlock* node;
		if(size > MSIZE || size == MSIZE) { //if it's too big, create a block that satisfy the needs
			tsize = tsize + size;		
			node = malloc(size);
			node->size= size;
		}else if(size < MSIZE && MSIZE-size < THRESHOLD){ //within threshold, return the whole block
			tsize = tsize + MSIZE;
			node = malloc(MSIZE);
			node->size= MSIZE;
		}else { //return the needed memory, and put the rest back to free_list
			tsize = tsize + MSIZE;			
			newBlock* temp;
			temp = malloc(MSIZE);
			temp->size = MSIZE;
			node = temp + sizeof(*temp) + temp->size - size; //check this later (address might be wrong)
			node->size = size; 
			free_list = temp;
			free_list->size = MSIZE - sizeof(*temp) - size;
		}
		return node;
	}
	//if free_list is not NULL
	newBlock* h1;
	newBlock* h2;
	h1 = free_list;
	h1->size = free_list->size;
	h2 = free_list;
	if(h1->size > size) { //the first one is big enough 
		newBlock* tempN;
		if((h1->size-size) > THRESHOLD) { //return the needed memory, and put the rest back to free_list
			tempN = h1 + sizeof(*tempN) + h1->size - size; 
			h1->size = h1->size - size;
			tempN->size = size;
		} else {//within the threshold, return the whole block
			tempN = h1+sizeof(*tempN);
			free_list = h1->next;
			tempN->size = h1->size;
		}
		return tempN;
	}else if(h1->size == size) { //if needed size is equal to the size of first block, return the first block
		free_list = h2->next;
		h1 = h1 + sizeof(*h1);
		h1->size = size;
		return h1;
	}else { //if the size of first block is smaller than needed
		while(h1->next != NULL) {
			if((h1->next)->size > size || (h1->next)->size == size) { 
				h2 = h2->next;
				if(h1->next->size == size || (h1->next->size-size) < THRESHOLD) {
					uintptr_t tempSize = h1->next->size;
					h1->next = h2->next;
					h2->next = NULL;
					h2 = h2 +sizeof(*h2);
					h2->size = tempSize;
					return h2;
				}else if(h2->next != NULL) {
					h1->next = h2->next;
					h2->next = NULL;
				}else if(h2->next == NULL){
					h1->next = NULL;
				}
				newBlock* temp;
				temp = h2 + sizeof(*h2)+h2->size-size;
				temp->size = size;
				h2->size = h2->size-size;
				//put h2 back in free_list
				h1 = free_list;
				if(h2->size < h1->size) {
					h2->next = h1;
					free_list = h2;	
					return temp;			
				} else {
					while(h1->next != NULL) {
						if((h1->next)->size > h2->size) {
							h2->next = h1->next;
							h1->next = h2;
							return temp;
						}else {
							h1 = h1->next;
						}
					}
					h1->next = h2;
					return temp;
				}
				
			}
			h1 = h1->next;
			h2 = h2->next;
		}
		tsize = tsize + size;
		newBlock* create;
		create = malloc(size);
		create->size= size;
		return create;
	}
}
