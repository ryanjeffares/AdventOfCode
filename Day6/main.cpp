#include "main.h"
#include <chrono>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	Solver solver;
	std::cout << solver.SumCountsPartOne() << "\n";

	auto end = std::chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << dur << "\n";
}

/*
*	Answer 1: 6297
*	Took 43.7 ms
* 
*	Answer 2: 3158
*	Took 45.7 ms
*/