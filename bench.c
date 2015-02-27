// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// bench.c for dist program

#include "mem.h"


int main(int argc, char** argv) {
	//testing print_heap
	FILE *f;
	f = fopen("test", "w+");
	print_heap(f);
	fclose(f);
	return 0;
}
