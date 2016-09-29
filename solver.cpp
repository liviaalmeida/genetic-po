#include "GA.hpp"

int main(int argc, char const *argv[])
{
	GA GenAl(argv[1],argv[2]);
	Indiv B = GenAl.run();
	std::cout<<B;
	return 0;
}
