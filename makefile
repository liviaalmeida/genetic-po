ERR = $(shell which icc >/dev/null; echo $$?)
ifeq "$(ERR)" "0"
CXX = icc
else
CXX = g++
endif

all: solver
	echo $(CXX)

solver: indiv.o GA.o solver.o
	$(CXX) -o solver indiv.o GA.o solver.o

indiv.o: indiv.cpp
	$(CXX) -c indiv.cpp -std=c++11

GA.o: GA.cpp
	$(CXX) -c GA.cpp -std=c++11

solver.o: solver.cpp
	$(CXX) -c solver.cpp -std=c++11

clean:
	rm -rf *o
