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

void freemem(void* p);

/** Takes a memory address of a newBlock to be
 * freed.  Leaves memory fields to be overwritten
 */
void freemem(void* p)
{	
	if (p == NULL)
		return;
	// get size of block
	uint8ptr_t totalSize = *p;
	if (free_list == NULL) {
		free_list = p;
		return;
	}
	uint8ptr_t size = sizeof(*newBlock);
	uint8ptr_t data = p + sizeof(uint8ptr_t) + sizeof(*newBlock);
}

/** 
 * 
 */
addBlock(newBlock* current, void* p, uint8ptr_t totalSize)
{
	if (current == NULL)  {
		// is adding the address of sufficient?
		return (newBlock*)p;
	}
	if (current->size > totalSize)  {
		//make currnet child of p
		return p;
	} 
	return addBlock(current->next, p, totalSize);
}


