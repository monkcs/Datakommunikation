COMPILER = g++ -O3 -march=native -fwhole-program -flto -Wpedantic -Wall -std=c++2a

.PHONY: all clean run

all: server.out client.out

server.out: server.cpp makefile
	$(COMPILER) server.cpp -o $@
	strip server.out

client.out: client.cpp makefile
	$(COMPILER) client.cpp -o $@
	strip client.out

clean:
	rm *.out
