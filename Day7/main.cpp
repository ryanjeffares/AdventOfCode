#include "main.h"

int main()
{
	Solver solver;
	solver.GetRules();

	std::cout << solver.FindBagColours() << "\n";
}