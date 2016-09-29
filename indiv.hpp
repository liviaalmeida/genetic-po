#ifndef INDIV_HPP
#define INDIV_HPP

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

enum restrictions {eql = 0, les, leq, gre, geq, dif };

#define absdouble(macrovalue) (macrovalue<0 ? -macrovalue : macrovalue)

class Indiv {
public:
	Indiv();
	Indiv(std::vector<int> indvalues);
	~Indiv();

	int size();
	int& operator[](int index);
	std::vector<int> getInd();
	double fitness(bool max);

	static void pushObjective(bool max, std::vector<int> fxa);
	static int getRestriction(std::string keyword);
	static void pushRestriction(std::vector<int> Aline, int bvalue, int rest);
	static bool isMaxP();
	static void printProblem();

	friend std::ostream& operator<<(std::ostream &output, const Indiv &I);

private:
	std::vector<int> ind;
	static std::vector<int> fx;
	static std::vector< std::vector<int> > A;
	static std::vector<int> b;
	static std::vector<int> rests;
	static bool isMax;
};

#endif
