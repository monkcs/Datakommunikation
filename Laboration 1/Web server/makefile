COMPILER = g++ -O3 -march=native -fwhole-program -flto -Wpedantic -Wall -std=c++2a

.PHONY: all clean run

all: server

server: server.cpp request.cpp makefile
	$(COMPILER)	server.cpp -o $@.out
	#$(COMPILER) request.cpp -o $@.out

test:
	$(COMPILER) test-server.cpp -o server.out -lpthread -lboost_system 
	$(COMPILER) test-client.cpp -o client.out -lpthread -lboost_system 

clean:
	rm *.out