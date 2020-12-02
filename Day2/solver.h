#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>

class Solver
{
private:
    std::vector<std::pair<int, int>> minMaxNumbers;
    std::vector<std::pair<std::string, std::string>> lettersAndPasswords;

    std::vector<std::string> ReadAllLines()
    {
        std::vector<std::string> output;
        std::ifstream file("input.txt");
        std::string line;
        while(std::getline(file, line))
        {
            output.push_back(line);
        }
        return output;
    }

    void FillVectors(std::vector<std::string> lines)
    {
        using std::string;

        for(std::string line : lines)
        {
            int min = std::stoi(line.substr(0, line.find("-")));
            int max = std::stoi(line.substr(line.find("-") + 1, line.find_first_of(" ") - line.find("-") - 1));
            
            std::string letter = line.substr(line.find_first_of(" ") + 1, 1);
            std::string password = line.substr(line.find_first_of(":") + 2, line.npos);

            minMaxNumbers.push_back(std::make_pair(min, max));
            lettersAndPasswords.push_back(std::make_pair(letter, password));
        }
    }

public:
    Solver()
    {
        FillVectors(ReadAllLines());
    }

    int SolvePuzzle()
    {
        int result = 0;
        for(int i = 0; i < minMaxNumbers.size(); i++)
        {
            int min = minMaxNumbers[i].first;
            int max = minMaxNumbers[i].second;
            std::string letter = lettersAndPasswords[i].first;
            std::string password = lettersAndPasswords[i].second;
            int amount = 0;
            for(auto c : password)
            {
                if(c == letter[0])
                {
                    amount++;
                }
            }
            if(amount >= min && amount <= max)
            {
                result++;
            }
        }
        return result;
    }
    
    int SolvePuzzleTwo()
    {
        int result = 0;
        for(int i = 0; i < minMaxNumbers.size(); i++)
        {
            int first = minMaxNumbers[i].first;
            int second = minMaxNumbers[i].second;
            std::string letter = lettersAndPasswords[i].first;
            std::string password = lettersAndPasswords[i].second;
            if((password.substr(first - 1, 1) == letter && password.substr(second - 1, 1) != letter) ||
               (password.substr(first - 1, 1) != letter && password.substr(second - 1, 1) == letter))
               {
                   result++;
               } 
        }
        return result;
    }
};