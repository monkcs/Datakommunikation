COMPILER = g++ -O3 -march=native -fwhole-program -flto -Wpedantic -Wall -std=c++2a

.PHONY: all clean run

all: request

request: request.cpp makefile
	$(COMPILER) request.cpp -o $@.out

test:
	$(COMPILER) test-server.cpp -o server.out -lpthread -lboost_system 
	$(COMPILER) test-client.cpp -o client.out -lpthread -lboost_system 

clean:
	rm *.out