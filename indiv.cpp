#ifndef INDIV_FUNCS
#include "indiv.hpp"

#else

template <typename Real>
Indiv<Real>::Indiv() {

}

template <typename Real>
Indiv<Real>::Indiv(std::vector<Real> indvalues) {
	ind.reserve(indvalues.size());
	ind = indvalues;
}

template <typename Real>
Indiv<Real>::~Indiv() {

}

template <typename Real>
int Indiv<Real>::size() {
	return ind.size();
}

template <typename Real>
Real& Indiv<Real>::operator[](int index) {
	return ind[index];
}

template <typename Real>
std::vector<Real> Indiv<Real>::getInd() {
	std::vector<Real> indcopy;
	indcopy = ind;
	return indcopy;
}

template <typename Real>
double Indiv<Real>::fitness(double weight) {
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

template <typename Real>
void Indiv<Real>::pushObjective(bool max, std::vector<double> fxa) {
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

template <typename Real>
int Indiv<Real>::getRestriction(std::string keyword) {
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

template <typename Real>
void Indiv<Real>::pushRestriction(std::vector<double> Aline, double bvalue, int rest) {
	A.push_back(Aline);
	b.push_back(bvalue);
	rests.push_back(rest);
}

template <typename Real>
bool Indiv<Real>::isMaxP() {
	return isMax;
}

template <typename Real>
void Indiv<Real>::printProblem() {
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

template <typename IndivTemp>
std::ostream& operator<<(std::ostream &output, const Indiv<IndivTemp> &I) {
	for (int i=0; i<I.ind.size(); ++i) {
		output<<"x"<<i+1<<"="<<I.ind[i]<<" ";
	}
	output<<"\n";
	return output;
}

template <typename Real>
std::vector<double> Indiv<Real>::fx(0);

template <typename Real>
std::vector<double> Indiv<Real>::trueObj(0);

template <typename Real>
std::vector< std::vector<double> > Indiv<Real>::A(0);

template <typename Real>
std::vector<double> Indiv<Real>::b(0);

template <typename Real>
std::vector<int> Indiv<Real>::rests(0);

template <typename Real>
bool Indiv<Real>::isMax = true;

#endif
