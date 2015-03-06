Karl Marrett
Nan Jiang
CSE 374 HW6
Feb 20th
README for dist program

Dist is program that mimics some of the features of the functions malloc
and free.  The getmem.c, print_heap.c, and get mem_stats were developed
primarily by Nan.  The bench.c and freemem.c program was developed
primarily by Karl along with the README text.  Each member reviewed the
programs of the other developer.  The free list is a linked list of blocks
sorted by memory address.  It is handled by two recursive functions,
addBlock, and handleCombines.  In addblock, the client passes a block to
add to the free list and the block is placed at the appropriate place in
the free list according to its memory location.  This is accomplished by
reursively moving down the freelist until a block address in free is
greater than the new address.  Once this block is found addblock sets the
old block to be the new child of the new block and it is returned up the
list.  After every call on addtoblock the method also has a call on
handleCombines which checks whether the current block is located
immediately before the next block.  This is computed by checking whether
the next possible memory location is the same address of the address of the
"next" field.  In our program, a combine would only occur when the two
blocks originated from a previously split block from a single malloc call.
freemem.c operates under the contract with getmem.c that the freelist is
sorted in increasing memory location, otherwise memory combination would be
extremely rare.  Since freemem.c only checks for combines at the current
place of insertion in addblock upwards it assumes that the freelist has
already been checked for combination below the current location.

getmem.c takes a memory size request and allocates enough space for a
struct pointer newBlock to satisfy it.  The function getmem.c searches the
current list of free memory for a block that can satisfy the request.  If
no current blocks are large enough for the request a new block is made.
The behavior of getmem stats can be simplified into a few other basic
cases.  One case is where a block of suitable size could be found such that
splitting the block would still leave a suitable sized block in freelist.
Another case deals with when the request can be made with a current block
but that the threshold of size that would would remain in the freelist
would make a block so small that it has minimal use.  In this case, the
whole block is returned to the user meaning that the extra space is
essentially wasted since it is unknown to the user of the returned block.
getmem.c also had a choice for deciding how much new memory to allot,
instead of simply alloting the requested space, a default request size on
malloc was made on new blocks denoted by the macro MSIZE.

Experimenting with the program was done. In general, with the default
ntrials of 10000 the execution took somewhere between .005 and .001 seconds
on most trials with no other changes in parameters.   This large
fluctuations made it difficult to draw a lot of conclusions from the timing
alone.  More useful was the information about the free size, the blocks and
the average bytes per block.  In general increasing the trial size
decreased the average bytes per free block presumably due to more calls on
getmem successfully finding a matched block.  The largest trial size tested
was ten milion which took about a minute to complete and produced average
block size of 8000.  In general, modifying the other parameters had
somewhat of the expected effect.  For example, raising the large_limit or
pct large tended to increase the average block size whereas the opposite or
lowering the small limit tended to lower it. 

Discussions with TA's and slides from lectures were the main guidance in
this report.  No other major theory of memory management was consulted.




