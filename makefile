all: solver

solver: indiv.o GA.o solver.o
	icc -o solver indiv.o GA.o solver.o

indiv.o: indiv.cpp
	icc -c indiv.cpp -std=c++11

GA.o: GA.cpp
	icc -c GA.cpp -std=c++11

solver.o: solver.cpp
	icc -c solver.cpp -std=c++11

clean:
	rm -rf *o
