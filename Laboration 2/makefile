COMPILER = gcc -O3 -march=native -Wpedantic -Wall -Werror
.PHONY: all clean

all: reliable-transport.out

reliable-transport.out: makefile stud.o checksum.o jim_corrected.c
	$(COMPILER) -fwhole-program -flto stud.o checksum.o jim_corrected.c -o $@

stud.o: makefile Stud.h Stud.c
	$(COMPILER) -c Stud.c -o $@

checksum.o: makefile checksum.h checksum.c
	$(COMPILER) -c checksum.c -o $@

clean:
	rm *.out *.o