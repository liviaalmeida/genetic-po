#ifndef INDIV_HPP
#define INDIV_HPP

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

enum restrictions {eql = 0, les, leq, gre, geq, dif };

#define absdouble(macrovalue) (macrovalue>=0 ? macrovalue : -macrovalue)

template <typename Real>
class Indiv {
public:
	Indiv();
	Indiv(std::vector<Real> indvalues);
	~Indiv();

	int size();
	Real& operator[](int index);
	std::vector<Real> getInd();
	double fitness(double weight);

	static void pushObjective(bool max, std::vector<double> fxa);
	static int getRestriction(std::string keyword);
	static void pushRestriction(std::vector<double> Aline, double bvalue, int rest);
	static bool isMaxP();
	static void printProblem();

	template <typename IndivTemp>
	friend std::ostream& operator<<(std::ostream &output, const Indiv<IndivTemp> &I);

private:
	std::vector<Real> ind;

	static std::vector<double> fx;
	static std::vector<double> trueObj;
	static std::vector< std::vector<double> > A;
	static std::vector<double> b;
	static std::vector<int> rests;
	static bool isMax;
};

#endif
