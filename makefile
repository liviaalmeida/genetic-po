all: solver

solver: indiv.o GA.o solver.o
	g++ -o solver indiv.o GA.o solver.o

indiv.o: indiv.cpp
	g++ -c indiv.cpp -std=c++11

GA.o: GA.cpp
	g++ -c GA.cpp -std=c++11

solver.o: solver.cpp
	g++ -c solver.cpp -std=c++11

clean:
	rm -rf *o
