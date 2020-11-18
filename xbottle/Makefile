CC := g++
CXXFLAGS := -lstdc++ -O0 -ldl -pipe -w -g -std=c++11

xbottle: xbottle.cpp ../src/*.h
	$(CC) xbottle.cpp -o xbottle $(CXXFLAGS)

lib: ./localbottle/include/lib/*.cpp
	cd ./localbottle/include/lib && $(MAKE) all
	@echo "LIB SUCCESS"

all: xbottle
	@echo "ALL COMPILE"
