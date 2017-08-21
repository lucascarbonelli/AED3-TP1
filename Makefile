all: main
CXXFLAGS+=-std=c++0x
clean:
	rm -f *.o
	rm -f main

main: main.cpp opiniones.o
	g++ $(CXXFLAGS) -g -Wall -o main main.cpp opiniones.o 

opiniones.o: opiniones.h opiniones.cpp
	g++ $(CXXFLAGS) -g -Wall -c opiniones.cpp

