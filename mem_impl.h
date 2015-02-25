#ifndef BLOCK_H
#define BLOCK_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct block {
  int size;
  uintptr_t* next;
  char* data;
};

struct block* newBlock();

#endif
