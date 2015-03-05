// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// freemem.c for dist program

#include "mem.h"
#include "mem_impl.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

extern newBlock* free_list;
//size of newBlock overhead PUT IN MEMIMPL.H LATER??
extern uintptr_t hsize;

void freemem(void* p);
newBlock* addBlock(newBlock* current, void* p);
void handleCombines(newBlock* current);


/** Takes a memory address of a newBlock to be
 * freed. p points to address of the size field 
 * at top of struct.
 */
void freemem(void* p)
{	
	if (p == NULL)  {
		fprintf(stderr, "Warning: pointer passed is NULL and"
			" can not be freed.\n");
		return;
	}
	free_list = addBlock(free_list, p);
	return;
}

/** 
 * Add block to free list sorted by memory location 
 */
newBlock* addBlock(newBlock* current, void* p)
{
	if (current == NULL)  {
		printf("Add at null...\n"); // diagnostics
		current = (newBlock*) p; 
		current->next = NULL; //protect current from faulty next
		printf("...Completed at Null\n"); // diagnostics
		//address of p is less than current
	} else if (current > (newBlock*)p)  { 
		printf("Add before...\n"); // diagnostics
		printf("Current address: %p...\n", current); // diagnostics
		printf("New address: %p...\n", p); // diagnostics
		newBlock* temp;
		temp = current;
		current = (newBlock*) p; 
		current->next = temp;
		printf("...Completedputbefore\n"); // diagnostics
	} else  { // traverse freelist further
		printf("...traversing\n"); // diagnostics
		current->next = addBlock(current->next, p);
		printf("...Completed Traverse\n"); // diagnostics
	}
	printf("Try Combining\n"); // diagnostics
	handleCombines(current);
	printf("...Returning after combine\n"); // diagnostics
	return current; // return new freelist
}

/** 
 * Check whether current block can be combined with next block
 * in free list.  Check by computing next possible memory
 * location of next block, see if matches address of current->next 
 */
void handleCombines(newBlock* current)
{
	if (current->next == NULL)  
		return;// do nothing
	//address of next contiguous memory
	newBlock* nextAddress = (newBlock*)
		current + hsize + current->size;
	// check if next possible & matches actual current->next &
	if (nextAddress == current->next)  { 
		// combine blocks
		printf("Current->next address: %p...\n", current->next); // diagnostics
		printf("Next address: %p...\n", nextAddress); // diagnostics
		printf("Combining...\n"); // diagnostics
		current->size = 
			current->size + current->next->size +
			 hsize;
		current->next = current->next->next;
		printf("...CompletedCombine\n"); // diagnostics
	}
}

