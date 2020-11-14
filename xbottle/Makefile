CC := g++
CXXFLAGS := -lstdc++ -ldl -pipe -w -g -std=c++11

xbottle: xbottle.cpp ../src/*.h
	$(CC) xbottle.cpp -o xbottle $(CXXFLAGS)

all: xbottle
	@echo "ALL COMPILE"
