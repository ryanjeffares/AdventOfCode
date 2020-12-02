#include "solver.h"
#include <chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Solver solver;
    //std::cout << solver.SolvePuzzle() << "\n";
    std::cout << solver.SolvePuzzleTwo() << "\n";
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << duration << "\n";
}

/*
* Answer 1: 556
* Took 5 ms
* Answer 2: 605
* Took 5 ms
*/