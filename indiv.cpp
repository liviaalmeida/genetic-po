#include "indiv.hpp"

Indiv::Indiv() {

}

Indiv::Indiv(std::vector<int> indvalues) {
	ind.reserve(indvalues.size());
	ind = indvalues;
}

Indiv::~Indiv() {

}


int Indiv::size() {
	return ind.size();
}

int& Indiv::operator[](int index) {
	return ind[index];
}

std::vector<int> Indiv::getInd() {
	std::vector<int> indcopy;
	indcopy = ind;
	return indcopy;
}

double Indiv::fitness(double weight) {
	double fit = 0;
	for (int i=0; i<ind.size(); ++i) {
		fit += ind[i]*fx[i];
	}
	for (int i=0; i<A.size(); ++i) {
		double value = 0;
		for (int j=0; j<ind.size(); ++j) {
			value += ind[j]*A[i][j];
		}
		switch (rests[i]) {
			case eql:
				if (value!=b[i]) {
					fit -= weight*absdouble((rests[i]-value));
				}
				break;
			case les:
				if (value>=b[i]) {
					fit -= weight*absdouble((rests[i]-value));
				}
				break;
			case leq:
				if (value>b[i]) {
					fit -= weight*absdouble((rests[i]-value));
				}
				break;
			case gre:
				if (value<=b[i]) {
					fit -= weight*absdouble((rests[i]-value));
				}
				break;
			case geq:
				if (value<b[i]) {
					fit -= weight*absdouble((rests[i]-value));
				}
				break;
			case dif:
				if (value==b[i]) {
					fit -= weight*absdouble((rests[i]-value));
				}
				break;
		}
	}
	return fit;
}

void Indiv::pushObjective(bool max, std::vector<double> fxa) {
	trueObj = fxa;
	if (max) {
		fx = fxa;
	} else {
		for (int i=0; i<fxa.size(); ++i) {
			fx.push_back(-fxa[i]);
		}
	}
	isMax = max;
}

int Indiv::getRestriction(std::string keyword) {
	if (keyword=="eql") {
		return 0;
	} else if (keyword=="les") {
		return 1;
	} else if (keyword=="leq") {
		return 2;
	} else if (keyword=="gre") {
		return 3;
	} else if (keyword=="geq") {
		return 4;
	} else if (keyword=="dif") {
		return 5;
	}
	return -1;
}

void Indiv::pushRestriction(std::vector<double> Aline, double bvalue, int rest) {
	A.push_back(Aline);
	b.push_back(bvalue);
	rests.push_back(rest);
}

bool Indiv::isMaxP() {
	return isMax;
}

void Indiv::printProblem() {
	std::cout<<(isMax ? "Maximize " : "Minimize ");
	if (trueObj[0]<0) {
		std::cout<<"-";
	}
	std::cout<<trueObj[0]<<"x"<<1;
	for (int i=1; i<trueObj.size(); ++i) {
		if (trueObj[i]>0) {
			std::cout<<" +";
		}
		std::cout<<" "<<trueObj[i]<<"x"<<i+1;
	}
	std::cout<<"\nSubject to:\n";
	for (int i=0; i<A.size(); ++i) {
		if (A[i][0]<0) {
			std::cout<<"-";
		}
		std::cout<<A[i][0]<<"x"<<1;
		for (int j=1; j<A[i].size(); ++j) {
			if (A[i][j]>0) {
				std::cout<<" +";
			}
			std::cout<<" "<<A[i][j]<<"x"<<j+1;
		}
		switch (rests[i]) {
			case eql:
				std::cout<<" = ";
				break;
			case les:
				std::cout<<" < ";
				break;
			case leq:
				std::cout<<" <= ";
				break;
			case gre:
				std::cout<<" > ";
				break;
			case geq:
				std::cout<<" <= ";
				break;
			default:
				std::cout<<" unknown_restriction ";
		}
		std::cout<<b[i]<<"\n";
	}
}

std::ostream& operator<<(std::ostream &output, const Indiv &I) {
	for (int i=0; i<I.ind.size(); ++i) {
		output<<"x"<<i+1<<"="<<I.ind[i]<<" ";
	}
	output<<"\n";
	return output;
}

std::vector<double> Indiv::fx(0);
std::vector<double> Indiv::trueObj(0);
std::vector< std::vector<double> > Indiv::A(0);
std::vector<double> Indiv::b(0);
std::vector<int> Indiv::rests(0);
bool Indiv::isMax = true;
