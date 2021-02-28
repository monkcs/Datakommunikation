COMPILER = gcc -O3 -march=native -Wpedantic -Wall
.PHONY: clean test

reliable-transport.out: makefile stud.o checksum.o jim_corrected.c
	$(COMPILER) -fwhole-program -flto stud.o checksum.o jim_corrected.c -o $@
	strip --strip-all $@

stud.o: makefile Stud.h Stud.c
	$(COMPILER) -c Stud.c -o $@

checksum.o: makefile checksum.h checksum.c
	$(COMPILER) -c checksum.c -o $@


clean:
	rm *.out *.o

test: reliable-transport.out
	./reliable-transport.out 20 0.2 0.2 1000 0