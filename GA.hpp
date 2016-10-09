#ifndef GA_HPP
#define GA_HPP

#include "indiv.hpp"
#include <fstream>
#include <random>
#include <utility>
#include <set>

#define objbool(macrokey) (macrokey=="max" ? true : false)

class GAConf {
public:
	GAConf(char const *ini);
	~GAConf();

	int popSize, generations, tSize, seed;
	int minRand, maxRand;
	bool diversity;
	double crossP, mutP, restWeight;
};

template <typename Real>
class GA {
public:
	GA(char const *params, char const *ini);
	~GA();

	Indiv<Real> run();


private:
	std::vector< Indiv<Real> > population;
	std::vector<double> fitness;
	int vars;

	GAConf conf;
	std::mt19937 generator;

	void initialPopulation();

	int tournament();
	std::pair< Indiv<Real> , Indiv<Real> > crossover();
	void mutation(Indiv<Real> &parent);
	void evolve(int bestfit);
	int printStats();

};

#define GA_FUNCS
#include "GA.cpp"

#endif
