all: main
CXXFLAGS+=-std=c++0x
clean:
	rm -f *.o
	rm -f main

main: main.cpp casos.o
	g++ $(CXXFLAGS) -g -Wall -o main main.cpp casos.o 

casos.o: casos.h casos.cpp
	g++ $(CXXFLAGS) -g -Wall -c casos.cpp

