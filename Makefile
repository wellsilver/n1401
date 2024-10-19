all: build run clean

build:
	g++ src/main.cpp -g -o i1401.o

run:
	./i1401.o examples/helloworld.S

clean:
	rm i1401.o