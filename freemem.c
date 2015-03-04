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

void freemem(void* p);

// Header sizes
//size of newBlock overhead THIS SHOULD BE PUT IN MEMIMPL.H LATER
uintptr_t hsize = sizeof(newBlock*) + sizeof(uintptr_t);
uintptr_t hmalloc = 16; //size of malloc block overhead

/** Takes a memory address of a newBlock to be
 * freed. p points to address of the size field. 
 */
void freemem(void* p)
{	
	if (p == NULL)
		return;
	if (free_list == NULL) {
		free_list = p;
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
		current->next = NULL; //guarantee p does not keep next
	} else if (current > p)  { //address of p is less than current
		uint8ptr_t next = p + sizeof(uint8ptr_t);//get next &
		*next = current; //make p point to current
		current = (newBlock*) p; 
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
	if (current->next != NULL)  {
		//address of next contiguous memory
		uint8ptr_t nextAddress = 
			current + hsize + dataSize + hmalloc;
		// check next possible & matches actual current->next &
		if (nextAddress == &(current->next))  { //&current bug?
			// combine blocks
			current->size = 
				current->size + current->next->size +
				hmalloc + hsize;
			current->next = current->next->next;
		}
	}
}

