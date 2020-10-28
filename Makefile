CC=g++

IDLE: *.cpp src/*
	$(CC) ./idle.cpp -o idle -std=c++11 -w -g -ldl
TEST: *.cpp src/*
	$(CC) ./main.cpp -o main -std=c++11 -w -g -ldl

clean:
	rm -rf main.exe idle.exe idle main

all: IDLE TEST

run: all
	./idle
	