#ifndef BLOCK_H
#define BLOCK_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct block {
  uintptr_t size;
  void* next;
};

struct block* newBlock();

#endif
