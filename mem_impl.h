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
#include <assert.h>
#include "mem.h"

newBlock* free_list;
uintptr_t tsize;
// size of header for finding data/top of block

#endif
