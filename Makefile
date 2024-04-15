all: build run clean

build:
	g++ src/main.cpp -g -o main.exe

run:
	./main.exe .\examples\helloworld.S -o helloworld.o

clean:
	rm main.exe