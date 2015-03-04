// Karl Marrett
// Nan Jiang
// CSE 374 HW6
// Feb 20th
// bench.c for dist program

// TODO clocking, random seeding, print_heap every 10 iterations

#include "mem.h"
#include "mem_impl.h"

extern newBlock * free_list;
extern uintptr_t tsize;

int main(int argc, char** argv) {
	char* programName;
	int ntrials;
	int pctget;
	int pctlarge;
	int small_limit;
	int large_limit;
	time_t t;
	int random_seed;
	srand((unsigned) time(&t));

	programName = argv[0];
	ntrials = 10000;
	pctget = 50;
	pctlarge = 10;
	small_limit = 200;
	large_limit = 20000;
	//int random_seed = rand();	
	
	if (argc > 1)  
		ntrials = (int) argv[1];
	if (argc > 2)  
		pctget = (int) argv[2];
	if (argc > 3)  
		pctlarge = (int) argv[3];
	if (argc > 4)  
		small_limit = (int) argv[4];
	if (argc > 5)  
		large_limit = (int) argv[5];
		if ((large_limit + small_limit) > 32767)  {
			fprintf(stderr, "%s: warning: does not \ 
				guarantee correct rand behavior due to \
				large_limit provided\n", programName);
		}
	if (argc > 6)  
		random_seed = (int) argv[6];
		srand((unsigned) random_seed);

	int i;
	int size;
	int items;
	int index;
	int items = 0;
	void** currentBlocks = 
		(void** ) malloc(sizeof(newBlock*) * ntrials);
	for (i = 0; i < ntrials; i++)  {
		if ((rand() % 100) >= pctget ) {
			if ((rand() % 100) >= pctlarge ) {
				size = (rand() % (large_limit - 
				small_limit)) + small_limit + 1;
			}  else  {
				size = (rand() % small_limit) + 1;
			}
			// add to end of array
			currentBlocks[items] = get_mem(size);
			items++;
		}  else  {
			if (items == 0)  {
				continue;
			}
			index = rand() % items;
			freemem(currentBlocks[index]);
			if (index != (items - 1))  {
				//replace with last block
				currentBlocks[index] = 
					currentBlocks[items - 1];
				//remove the last (unnecessary)
				//currentBlocks[items - 1] = null;
			}
			items--;
		}
	}
				
	// Misc. testing
	//manually create a free_list
	free_list = malloc(500);
	free_list->size = 500-sizeof(*free_list);
	newBlock* h1;
	h1 = malloc(700);
	h1->size = 700 - sizeof(*h1);
	free_list->next = h1;

	newBlock* h2;
	h2 = malloc(900);
	h2->size = 900 - sizeof(*h2);
	h1->next = h2;
	
	newBlock* h3;
	h3 = malloc(1000);
	h3->size = 1000 - sizeof(*h3);
	h2->next = h3;
	
	newBlock* h4;
	h4 = malloc(1050);
	h4->size = 1050 - sizeof(*h3);
	h3->next = h4;
	
	//testing getmem
	getmem(950); 
	//getmem(5000);

	//get_mem_stats
	uintptr_t *total_size = (uintptr_t *) malloc(sizeof(uintptr_t));
	uintptr_t *total_free = (uintptr_t *) malloc(sizeof(uintptr_t));
	uintptr_t *n_free_blocks = (uintptr_t *) malloc(sizeof(uintptr_t));
	get_mem_stats(total_size, total_free, n_free_blocks);
	printf("%lu\n", *total_size);
	printf("%lu\n", *total_free);
	printf("%lu\n", *n_free_blocks);

	//print_heap
	FILE *f;
	f = fopen("test", "w+");
	print_heap(f);
	fclose(f);
	return 0;
}
