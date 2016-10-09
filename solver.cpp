#include "GA.hpp"

int main(int argc, char const *argv[])
{
	GA<int> GenAl(argv[1],argv[2]);
	Indiv<int> B = GenAl.run();
	std::cout<<B;
	return 0;
}
