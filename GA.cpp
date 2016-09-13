#include "GA.hpp"

GAConf::GAConf(char const *ini) {
	std::ifstream input(ini);
	std::string field;
	char equal;
	while (input>>field>>equal) {
		if (field=="PopulationSize") {
			input>>popSize;
		} else if (field=="Generations") {
			input>>generations;
		} else if (field=="Diversity") {
			input>>diversity;
		} else if (field=="CrossoverProb") {
			input>>crossP;
		} else if (field=="MutationProb") {
			input>>mutP;
		} else if (field=="TournamentSize") {
			input>>tSize;
		} else if (field=="MinMaxRand") {
			input>>minRand>>maxRand;
		} else {
			input>>seed;
		}
	}
}

GAConf::~GAConf() {

}

GA::GA(char const *params, char const *ini) : conf(ini) {
	generator = std::mt19937(conf.seed);
	population.reserve(conf.popSize);
	fitness.reserve(conf.popSize);
	std::ifstream problem(params);
	std::string field, equal;
	while (problem>>field>>equal) {
		if (field=="Vars") {
			problem>>vars;
		} else if (field=="Objective") {
			std::vector<int> obj(vars);
			for (int i=0; i<vars; ++i) {
				int p;
				problem>>p;
				obj[i] = p;
			}
			Indiv::pushObjective(obj);
		} else if (field=="Rest") {
			std::vector<int> rt(vars);
			int bound;
			for (int i=0; i<vars; ++i) {
				int r;
				problem>>r;
				rt[i] = r;
			}
			problem>>bound;
			Indiv::pushRestriction(rt,bound);
		}
	}
}

GA::~GA() {

}

Indiv GA::run() {
	initialPopulation();
	std::cout<<"Generation 0 ";
	int maxfit = printStats();
	for (int gen=0; gen<conf.generations; gen++) {
		evolve(maxfit);
		std::cout<<"Generation "<<gen+1<<" ";
		maxfit = printStats();
	}
	Indiv::printProblem();
	return population[maxfit];
}

void GA::initialPopulation() {
	if (population.size()) {
		population.clear();
	}
	for (int i=0; i<conf.popSize; ++i) {
		std::vector<int> ind(vars);
		std::uniform_int_distribution<int> chooseGen(conf.minRand,conf.maxRand);
		for (int i=0; i<vars; ++i) {
			ind[i] = chooseGen(generator);
		}
		Indiv newInd(ind);
		double fit = newInd.fitness();
		population.push_back(newInd);
		fitness.push_back(fit);
	}
}

int GA::tournament() {
	std::set<int> sample;
	std::uniform_int_distribution<int> chooseParent(0,conf.popSize-1);
	while (sample.size()!=conf.tSize) {
		int p = chooseParent(generator);
		sample.insert(p);
	}
	std::set<int>::iterator it = sample.begin();
	int index = *it;
	double maxfit = fitness[*it];
	++it;
	while (it!=sample.end()) {
		if (fitness[*it] > maxfit) {
			maxfit = fitness[*it];
			index = *it;
		}
		++it;
	}
	return index;
}

std::pair<Indiv, Indiv> GA::crossover() {
	int p1 = tournament(), p2 = tournament();
	while (p2==p1) {
		p2 = tournament();
	}
	std::uniform_int_distribution<int> cut(1,vars-1);
	int cutpoint = cut(generator);
	std::pair<Indiv,Indiv> children;
	std::vector<int> ind1, ind2, get1 = population[p1].getInd(), get2 = population[p2].getInd();
	ind1.insert(ind1.begin(),get1.begin(),get1.begin()+cutpoint);
	ind1.insert(ind1.end(),get2.begin()+cutpoint,get2.end());
	ind2.insert(ind2.begin(),get2.begin(),get2.begin()+cutpoint);
	ind2.insert(ind2.end(),get1.begin()+cutpoint,get1.end());
	Indiv i1(ind1), i2(ind2);
	children.first = i1;
	children.second = i2;
	return children;
}

void GA::mutation(Indiv &parent) {
	std::uniform_real_distribution<double> mut(0,1);
	std::uniform_int_distribution<int> gen(conf.minRand,conf.maxRand);
	std::vector<int> parentcopy = parent.getInd();
	int isMutated = 0;
	for (int i=0; i<parentcopy.size(); ++i) {
		if (mut(generator)<=conf.mutP) {
			isMutated++;
			int g = gen(generator);
			while (g==parentcopy[i]) {
				g = gen(generator);
			}
			parentcopy[i] = g;
		}
	}
	if (isMutated) {
		Indiv M(parentcopy);
		parent = M;
	}
}

void GA::evolve(int maxfit) {
	std::vector<Indiv> newpop;
	std::vector<double> newfit;
	newpop.reserve(population.size());
	newfit.reserve(fitness.size());
	newpop.push_back(population[maxfit]);
	newfit.push_back(fitness[maxfit]);
	std::uniform_real_distribution<double> genOp(0,1);
	while (newpop.size()!=conf.popSize) {
		double op = genOp(generator);
		if (op<=conf.crossP) {
			std::pair<Indiv, Indiv> children = crossover();
			double fit1 = children.first.fitness();
			newpop.push_back(children.first);
			newfit.push_back(fit1);
			if (newpop.size()!=conf.popSize) {
				double fit2 = children.second.fitness();
				newpop.push_back(children.second);
				newfit.push_back(fit2);
			}
		} else {
			int rep = tournament();
			Indiv R(population[rep].getInd());
			mutation(R);
			double fit = R.fitness();
			newpop.push_back(R);
			newfit.push_back(fit);
		}
	}
	std::swap(population,newpop);
	std::swap(fitness,newfit);
}

int GA::printStats() {
	double avg=fitness[0], min=fitness[0], max=fitness[0];
	int minindex=0, maxindex=0;
	for (int i=1; i<population.size(); ++i) {
		avg += fitness[i];
		if (fitness[i]>max) {
			max = fitness[i];
			maxindex = i;
		}
		if (fitness[i]<min) {
			min = fitness[i];
			minindex = i;
		}
	}
	avg /= fitness.size();
	std::cout<<"MIN FIT: "<<min<<" MAX FIT: "<<max<<" AVG FIT: "<<avg<<'\n';
	return maxindex;
}