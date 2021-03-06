# Karl Marrett
# Nan Jiang
# CSE 374 HW6
# Feb 20th
# Makefile for dist program

# default target
dist: bench.o freemem.o get_mem_stats.o print_heap.o getmem.o
	gcc -Wall -g -o dist bench.o freemem.o get_mem_stats.o print_heap.o getmem.o

# individual source files
bench.o: bench.c mem.h 
	gcc -Wall -g -c bench.c

freemem.o: freemem.c mem.h mem_impl.h 
	gcc -Wall -g -c freemem.c

get_mem_stats.o: get_mem_stats.c mem.h mem_impl.h 
	gcc -Wall -g -c get_mem_stats.c

print_heap.o: print_heap.c mem.h mem_impl.h 
	gcc -Wall -g -c print_heap.c

getmem.o: getmem.c mem.h mem_impl.h 
	gcc -Wall -g -c getmem.c

#other target
clean:
	rm -f *.o bench hw6.tar
log:
	git log > git.log
tar:
	tar -cvf dist.tar mem_impl.h bench.c mem.h getmem.c get_mem_stats.c freemem.c print_heap.c Makefile git.log README.md
