all: build run clean

build:
	g++ src/main.cpp -g -o n1401.o

run:
	./n1401.o examples/helloworld.S

clean:
	rm n1401.o