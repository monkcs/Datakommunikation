COMPILER = g++ -O3 -march=native -fwhole-program -flto -Wpedantic -Wall -std=c++2a

.PHONY: all clean run

all: server

server: server.cpp makefile
	$(COMPILER)	server.cpp -o $@.out

clean:
	rm *.out