COMPILER = gcc -O3 -march=native -Wpedantic -Wall -Werror

.PHONY: clean

distance-routing.out: makefile node0.o node1.o node2.o node3.o prog3.c prog3.h
	$(COMPILER) -fwhole-program -flto node0.o node1.o node2.o node3.o prog3.c -o $@
	strip --strip-all $@

node0.o: makefile node0.c prog3.h
	$(COMPILER) -c node0.c -o $@

node1.o: makefile node1.c prog3.h
	$(COMPILER) -c node1.c -o $@

node2.o: makefile node2.c prog3.h
	$(COMPILER) -c node2.c -o $@

node3.o: makefile node3.c prog3.h
	$(COMPILER) -c node3.c -o $@


clean:
	rm *.out *.o