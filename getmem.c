// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// getmem.c that implements malloc function for dist program

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"

#define MSIZE 4000
#define THRESHOLD 20

newBlock* free_list = NULL;

void* getmem(uintptr_t size) {	
	if(size < 0) {
		return NULL;
	}else if(free_list == NULL) {
		newBlock* node;
		if(size > MSIZE || size == MSIZE) {
			node = malloc(size);
			node->size= size;
		}else {
			newBlock* temp;
			temp = malloc(MSIZE);
			temp->size = MSIZE;
			node = temp + sizeof(*temp) + temp->size - size; 
			free_list = temp;
			free_list->size = MSIZE - sizeof(*temp) - size;
		}
		return node;
	}
	newBlock* h1;
	newBlock* h2;
	h1 = free_list;
	h1->size = free_list->size;
	h2 = free_list;
	if(h1->size > size) {
		newBlock* tempN;
		if((h1->size-size) > THRESHOLD) {
			tempN = h1 + sizeof(*tempN) + h1->size - size; 
			h1->size = h1->size - size;
			tempN->size = size;
		} else {
			tempN = h1+sizeof(*tempN);
			free_list = h1->next;
			tempN->size = h1->size;
		}
		return tempN;
	}else if(h1->size == size) {
		free_list = h2->next;
		h1 = h1 + sizeof(*h1);
		h1->size = size;
		return h1;
	}else {
		while(h1->next != NULL) {
			//printf("first while");
			if((h1->next)->size > size || (h1->next)->size == size) {
				//printf("first while");
				h2 = h2->next;
				if(h1->next->size == size || (h1->next->size-size) < THRESHOLD) {
					uintptr_t tempSize = h1->next->size;
					h1->next = h2->next;
					h2->next = NULL;
					h2 = h2 +sizeof(*h2);
					h2->size = tempSize;
					return h2;
					//printf("123");
					
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
							printf("test");
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
		newBlock* create;
		create = malloc(size);
		create->size= size;
		return create;
	}
}
