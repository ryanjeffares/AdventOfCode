#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

// how many points right will we need to move to get to the bottom
// how many repetitions of the pattern will there be

// 31 across
// 323 down

int CheckTrees(int right, int down, std::vector<std::string> lines)
{
    char tree = '#';
    int numTrees = 0;
    int lineNumber = 0;
    int position = 0;
    
    for(int i = 0; i < 322; i += down)
    {
        position += right;
        if(position > 30)
        {
            position -= 31;
        }
        char target = lines[i + down][position];
        if(target == tree)
        {
            numTrees++;
        }
    }
    return numTrees;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::string> lines;
    std::ifstream file("input.txt");
    std::string line;
    while(std::getline(file, line))
    {
        lines.push_back(line);
    }
    // lines[0] is .#....#..##.#..####....#.......
    // lines[1] is ......#..#....#....###......#.# 
    // etc..

    long answer = CheckTrees(1, 1, lines) * CheckTrees(3, 1, lines) * CheckTrees(5, 1, lines) * CheckTrees(7, 1, lines) * CheckTrees(1, 2, lines);

    std::cout << answer << "\n"; // this prints a way too small number, why?

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << duration << "\n";
}

/*
* Answer 1: 173
* Took 1 ms
*
* Answers for part 2:
* 82
* 173
* 84
* 80
* 46
* Multiplied: 4,385,176,320
* Took 1 ms
*/