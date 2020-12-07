#include "main.h"
#include <chrono>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	Solver solver;
	//std::cout << solver.GetHighestID() << "\n";
	std::cout << solver.FindMissingSeat() << "\n";

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << duration << "\n";
}

/*
* Answer 1: 892
* Took 13.5 ms
*
* Answer 2: 625
* Took 12.9 ms (why shorter lol)
*/