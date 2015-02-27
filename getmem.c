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
	h2 = free_list;
	if(h1->size > size) {
		newBlock* tempN;
		tempN = h1 + sizeof(*tempN) + h1->size - size; 
		h1->size = h1->size - size;
		tempN->size = size;
		return tempN;
	}else {
		while(h1->next != NULL) {
			if((h1->next)->size > size) {
				//printf("123\n");
				h2 = h2->next;
				if((h1->next)->next != NULL) {
					h1->next = h2->next;
					h2->next = NULL;
				}else {
					h1->next = NULL;
				}
				newBlock* temp;
				temp = h2 + sizeof(*h2)+h2->size-size;
				temp->size = size;
				h2->size = h2->size-size;
				int test = (int) h2->size;
				printf("%d", test);
				//put h2 back in free_list
				h1 = free_list;
				if(h2->size < h1->size) {
					h2->next = h1;
					free_list = h2;				
				} else {
					while(h1->next != NULL) {
						printf("stuck\n");
						//error occurs here, need to be changed
						if((h1->next)->size > h2->size) {
							h2->next = h1->next;
							h1 = h2;
						}else {
							h1 = h1->next;
						}
					}
					h1->next = h2;
					return temp;
				}
				
			}
				//printf("1\n");
				h1 = h1->next;
				h2 = h2->next;
		}
		newBlock* create;
		create = malloc(size);
		create->size= size;
		return create;
	}
}
