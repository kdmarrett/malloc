Karl Marrett
Nan Jiang
CSE 374 HW6
Feb 20th
README for dist program

Dist is program that mimics some of the features of the functions 
malloc and free.  

The getmem.c, print_heap.c, and get mem_stats were developed primarily 
by Nan.  The bench.c and freemem.c program was developed primarily by
Karl.  Each member reviewed the programs of the other developer.  The free
list is a linked list of blocks sorted by memory address.  It is handled by
two recursive functions, addBlock, and handleCombines.  In addblock, the
client passes a block to add to the free list and the block is placed
at the appropriate place in the free list according to its memory
location.  After a block has been placed, each block is checked to see
whether it can be combined with the surrounding blocks.  This is computed
by checking whether the next possible memory location is the same address
of the address of the "next" field. 

