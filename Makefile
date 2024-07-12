all: build run clean

build:
	g++ src/main.cpp -g -o main.exe

run:
	gdb --ex r --args ./main.exe .\examples\helloworld.S -o helloworld.o
#	./i1401.exe helloworld.o

clean:
	rm main.exe