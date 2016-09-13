#ifndef GA_HPP
#define GA_HPP

#include "indiv.hpp"
#include <fstream>
#include <random>
#include <utility>
#include <set>
#include <string>

class GAConf {
public:
	GAConf(char const *ini);
	~GAConf();

	int popSize, generations, tSize, seed;
	int minRand, maxRand;
	bool diversity;
	double crossP, mutP;
};

class GA {
public:
	GA(char const *params, char const *ini);
	~GA();

	Indiv run();


private:
	std::vector<Indiv> population;
	std::vector<double> fitness;
	int vars;

	GAConf conf;
	std::mt19937 generator;

	void initialPopulation();

	int tournament();
	std::pair<Indiv,Indiv> crossover();
	void mutation(Indiv &parent);
	void evolve(int maxfit);
	int printStats();

};

#endif