CC=g++ -static

IDLE: *.cpp src/*
	$(CC) ./idle.cpp -o idle -std=c++11 -w -g
TEST: *.cpp src/*
	$(CC) ./main.cpp -o main -std=c++11 -w -g

clean:
	rm -rf main.exe idle.exe idle main

all: IDLE TEST

run: all
	./idle
	