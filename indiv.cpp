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

double Indiv::fitness() {
	double fit = 0;
	for (int i=0; i<ind.size(); ++i) {
		fit += ind[i]*fx[i];
	}
	for (int i=0; i<A.size(); ++i) {
		double value = 0;
		for (int j=0; j<ind.size(); ++j) {
			value += ind[j]*A[i][j];
		}
		if (value>b[i]) {
			fit = 0;
			break;
		}
	}
	return fit;
}


void Indiv::pushObjective(std::vector<int> fxa) {
	fx = fxa;
}


void Indiv::pushRestriction(std::vector<int> Aline, int bvalue) {
	A.push_back(Aline);
	b.push_back(bvalue);
}

void Indiv::printProblem() {
	std::cout<<"Maximize ";
	if (fx[0]<0) {
		std::cout<<"-";
	}
	std::cout<<fx[0]<<"x"<<1;
	for (int i=1; i<fx.size(); ++i) {
		if (fx[i]>0) {
			std::cout<<" +";
		}
		std::cout<<" "<<fx[i]<<"x"<<i+1;
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
		std::cout<<" <= "<<b[i]<<"\n";
	}
}

std::ostream& operator<<(std::ostream &output, const Indiv &I) {
	for (int i=0; i<I.ind.size(); ++i) {
		output<<"x"<<i+1<<"="<<I.ind[i]<<" ";
	}
	output<<"\n";
	return output;
}

std::vector<int> Indiv::fx(0);
std::vector< std::vector<int> > Indiv::A(0);
std::vector<int> Indiv::b(0);