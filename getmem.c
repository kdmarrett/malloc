// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// getmem.c that implements malloc function for dist program

#include "mem.h"
#include "mem_impl.h"
#include <assert.h>

#define MSIZE 4000
#define THRESHOLD 32

//newBlock* free_list = NULL;
uintptr_t tsize = 0; // total size malloc in program
// size of header for finding data/top of block
uintptr_t hsize = (uintptr_t)(sizeof(newBlock*) + sizeof(uintptr_t));

void* getmem(uintptr_t size) {	
	//assert((size % 16) == 0 && "size must be multiple of 16");
	if(size < 0) { //if size is less than zero
		return NULL;
	}else if(free_list == NULL) { //if list is empty
		//use malloc to create a block
		newBlock* node;
		//case larger than default size
		if(size >= MSIZE) { 
			tsize = tsize + size + hsize;		
			node = (newBlock*) malloc(size + hsize);
			assert(node != NULL && "malloc failed in getmem");
			node->size = size;
		//case within threshold, return whole block waste leftover
		}else if (size < MSIZE && ((MSIZE-size) < THRESHOLD)){ 
			tsize = tsize + MSIZE + hsize;
			node = (newBlock*) malloc(MSIZE + hsize);
			assert(node != NULL && "malloc failed in getmem");
			node->size= MSIZE;
		//case under MSIZE, leave leftover in free_list
		}else { 
			//update total size
			tsize = tsize + MSIZE + hsize;			
			newBlock* temp;
			// top of new block that is returned
			uintptr_t locNode;
			// cast the pointer address
			locNode = (uintptr_t) malloc(MSIZE + hsize);
			//assert(locNode != NULL && "malloc failed in getmem");
			node = (newBlock*) locNode;
			node->size = size; 
			//cut temp out of bottom of node
			temp = (newBlock*) (locNode + hsize + size);
			//minus the size of next and uint
			temp->size = MSIZE - (size + hsize); 
			free_list = temp;
		}
		return node;
	}
	//if free_list is not NULL
	newBlock* h1;
	newBlock* h2;
	h1 = free_list;
	//h1->size = free_list->size;
	h2 = h1->next;// move h2 one node in front of h1 
	if(h1->size > size) { //the first one is big enough 
		newBlock* tempN;
		if((h1->size-size) > THRESHOLD) { //return the needed memory, and put the rest back to free_list
			uintptr_t loc3;
			loc3 = (uintptr_t) h1; // cast the pointer address
			tempN = (newBlock* )(loc3 + h1->size - size); //same as temp above
			h1->size = h1->size - size - hsize; //minus the size of next and uint
			tempN->size = size;
		} else {//within the threshold, return the whole block
			tempN = h1;
			free_list = h1->next; 
			tempN->size = h1->size;
		}
		return tempN;
	}else if(h1->size == size) { //if needed size is equal to the size of first block, return the first block
		free_list = h2;
		h1->size = size;
		return h1;
	}else { //if size first block smaller than needed, go through list
		while(h1->next != NULL) {
			// if h2 suitable block
			if((h1->next)->size > size || (h1->next)->size == size) { 
				if(h1->next->size == size || (h1->next->size-size) < THRESHOLD) { //return the whole block
					uintptr_t tempSize = h1->next->size;
					h1->next = h2->next;
					h2->next = NULL;
					h2->size = tempSize;
					return h2;
				}else { //only take needed memory leave rest current place
					newBlock* temp;
					// cut temp out of bottom of h2
					uintptr_t loc;
					loc = (uintptr_t) h2; // cast the pointer address
					temp = (newBlock* )(loc + h2->size - size); 
					temp->size = size;
					// leave h2, update size
					h2->size = h2->size - (size + hsize); 
					return temp;
				}
			}
			//advance
			h1 = h1->next;
			h2 = h2->next;
		}
		//if cannot find enough space, malloc more
		tsize = tsize + size + hsize;
		newBlock* create;
		create = malloc(size + hsize); //malloc extra space for the struct
		assert(create != NULL && "malloc failed in getmem");
		create->size= size;
		return create;
	}
}
