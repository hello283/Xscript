CC = g++ -shared -std=c++11 -fPIC -w -O0

array: array.cpp ../../../../src/*.h
	$(CC) array.cpp -o array

stdlib: stdlib.cpp ../../../../src/*.h
	$(CC) stdlib.cpp -o stdlib

all: stdlib array
