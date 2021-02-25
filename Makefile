CFLAGS = -c -I$(HOME)/Programming/include
LFLAGS = -L$(HOME)/Programming/lib
LIBS = -ldataStructures

Pathfinder: project4.o output.o
	g++ -o Pathfinder $(LFLAGS) project4.o output.o $(LIBS)

project4.o: project4.cc project4.h
	g++ $(CFLAGS) project4.cc 

output.o: output.cpp pathfinder.h
	g++ $(CFLAGS) output.cpp
