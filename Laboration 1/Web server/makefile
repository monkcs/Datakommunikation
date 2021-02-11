COMPILER = g++ -O3 -march=native -fwhole-program -flto -Wpedantic -Wall -std=c++2a

.PHONY: all clean run

all: request

request: request.cpp makefile
	$(COMPILER) request.cpp -o $@

clean:
	rm *.out