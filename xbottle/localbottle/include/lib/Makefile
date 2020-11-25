CC = g++ -shared -std=c++11 -fPIC -w -O0

array: array.cpp ../../../../src/*.h
	$(CC) array.cpp -o array

stdlib: stdlib.cpp ../../../../src/*.h
	$(CC) stdlib.cpp -o stdlib

web: webs/web.cpp ../../../../src/*.h
	$(CC) webs/web.cpp -o web

array_win: array.cpp ../../../../src/*.h
	$(CC) array.cpp -o array -lws2_32

stdlib_win: stdlib.cpp ../../../../src/*.h
	$(CC) stdlib.cpp -o stdlib -lws2_32

web_win: webs/web.cpp ../../../../src/*.h
	$(CC) webs/web.cpp -o web -lws2_32

all_win: stdlib_win array_win web_win

all: stdlib array web
