// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// bench.c for dist program

#include "mem.h"
#include <time.h>

int main(int argc, char** argv) {
	uintptr_t total_size;
	uintptr_t total_free;
	uintptr_t n_free_blocks;
	char* programName;
	int ntrials;
	int pctget;
	int pctlarge;
	int small_limit;
	int large_limit;
	time_t start, end;
	double duration;
	int random_seed;
	srand((unsigned) time(&start));

	programName = argv[0];
	ntrials = 10000;
	pctget = 50;
	pctlarge = 10;
	small_limit = 200;
	large_limit = 20000;
	//int random_seed = rand();	
	
	if (argc > 1)  
		ntrials = atoi(argv[1]);
	if (argc > 2)  
		pctget = atoi(argv[2]);
	if (argc > 3)  
		pctlarge = atoi(argv[3]);
	if (argc > 4)  
		small_limit = atoi(argv[4]);
	if (argc > 5)  {
		large_limit = atoi(argv[5]);
		if ((large_limit + small_limit) > 32767)  {
			fprintf(stderr, "%s: warning: does not " 
				"guarantee correct rand behavior due to "
				"large_limit provided\n", programName);
		}
	}
	if (argc > 6)  
		random_seed = atoi(argv[6]);
		srand((unsigned) random_seed);
	
	int i;
	int size;
	int items;
	int index;
	int tenPercent;
	tenPercent = (int) (ntrials / 10);
	items = 0;
	void** currentBlocks;
	//hold active blocks
	currentBlocks = 
		(void** ) malloc(sizeof(newBlock*) * ntrials);
	start = clock();
	for (i = 0; i < ntrials; i++)  {
		//get mem
		if ((rand() % 100) >= pctget ) {
			if ((rand() % 100) >= pctlarge ) {
				size = (rand() % (large_limit - 
				small_limit)) + small_limit + 1;
			}  else  {
				size = (rand() % small_limit) + 1;
			}
			// add to end of array
			currentBlocks[items] = getmem(size);
			items++;
		// Free mem
		}  else  {
			if (items != 0)  {
				index = rand() % items; //choose a memblock
				freemem(currentBlocks[index]);
				if (index != (items - 1))  {
					//replace with last block
					currentBlocks[index] = 
						currentBlocks[items - 1];
				}
				items--;
			}
		}

		// Stats
		if ((i !=0) && ((i % tenPercent) == 0))  {
			get_mem_stats(
				&total_size, &total_free, &n_free_blocks);
			printf("Total size allocated: %lu\n", total_size);
			printf("Total free size: %lu\n", total_free);
			printf("Free blocks: %lu\n", n_free_blocks);
			printf("Average bytes per free block: %lu\n", 
					(uintptr_t) (total_free / n_free_blocks));
			end = clock();
			duration = (double) (end - start) / (double) CLOCKS_PER_SEC;
			printf("Time elapsed = %f\n", duration);
		}
	}

	//print_heap
	//file *f;
	//f = fopen("test", "w+");
	//print_heap(f);
	
	return 0;
}
