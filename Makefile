all: build run clean

build:
	g++ src/main.cpp -g -o n1401.exe

run:
	./n1401.exe examples/helloworld.S

clean:
	rm n1401.exe