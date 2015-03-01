// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// header file that includes data structure of memory block for dist program

#ifndef BLOCK_H
#define BLOCK_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct newBlock {
  uintptr_t size;
  struct newBlock* next;
}newBlock;


#endif
