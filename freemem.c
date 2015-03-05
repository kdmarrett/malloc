// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// freemem.c for dist program

//TODO When can we reference a field and when do we have to 
// manually find the address of that field
// TODO fields and pointer checks for all the functions HCBWKCSCOD
// TODO assert that next field of p is null?

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
 * freed. p points to address of the size field. 
 */
void freemem(void* p)
{	
	if (p == NULL)  {
		fprintf(stderr, "Warning: pointer passed is NULL and \
			can not be freed.\n");
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
		current = (newBlock*) p; 
		current->next = NULL; //protect current from faulty next
	} else if (((void*)current) > p)  { //address of p is less than current
		newBlock* temp;
		temp = current;
		current = (newBlock*) p; 
		current->next = temp;
	} else  { // traverse freelist further
		current->next = addBlock(current->next, p);
	}
	handleCombines(current);
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
		return;
	//address of next contiguous memory
	newBlock* nextAddress = 
		current + hsize + current->size;
	// check if next possible & matches actual current->next &
	if (nextAddress ==  current->next)  { 
		// combine blocks
		current->size = 
			current->size + current->next->size +
			 hsize;
		current->next = current->next->next;
	}
}

