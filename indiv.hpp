#ifndef INDIV_HPP
#define INDIV_HPP

enum faceName { FRONT = 0, LEFT, RIGHT, BACK, UP, DOWN };


#include <vector>
#include <iostream>

class Indiv {
public:
	Indiv();
	Indiv(std::vector<int> indvalues);
	~Indiv();

	int size();
	int& operator[](int index);
	std::vector<int> getInd();
	double fitness();

	static void pushObjective(std::vector<int> fxa);
	static void pushRestriction(std::vector<int> Aline, int bvalue);
	static void printProblem();

	friend std::ostream& operator<<(std::ostream &output, const Indiv &I);

private:
	std::vector<int> ind;
	static std::vector<int> fx;
	static std::vector< std::vector<int> > A;
	static std::vector<int> b;
};

#endif