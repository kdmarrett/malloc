// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// bench.c for dist program

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"


int main(int argc, char** argv) {
	//testing print_heap
	FILE *f;
	f = fopen("test", "w+");
	print_heap(f);
	fclose(f);
	return 0;
}
