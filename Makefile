all: build run clean

build:
	g++ src/main.cpp -g -o main.exe

run:
	./main.exe

clean:
	rm main.exe