#include "main.h"

int main()
{    
    auto start = std::chrono::high_resolution_clock::now();    
        
    Solver solver;    

    solver.GetPassports();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << duration << "\n";
}

/*
* Answer 1: 182
* Took 20 ms
*
*/