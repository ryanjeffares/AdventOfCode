#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Solver
{
private:
	std::vector<std::string> allLines;
	std::vector<int> seatIds;
	bool seatsHaveBeenSorted = false;

public:
	Solver()
	{		
		std::ifstream file("input.txt");
		std::string line;
		while (std::getline(file, line))
		{
			allLines.push_back(line);
		}
		GetSeatIds();
	}

	void GetSeatIds()
	{
		int row = 0, column = 0;
		std::pair<int, int> rowRange, seatRange;
		for (auto seat : allLines)
		{			
			rowRange = std::make_pair<int, int>(0, 127);			
			for (int i = 0; i < 6; i++)
			{
				int lower = rowRange.first;
				int upper = rowRange.second;
				switch (seat[i])
				{
				case 'F': 					
					rowRange.second -= (upper - lower + 1) / 2;
					break;
				case 'B': 
					rowRange.first += (upper - lower + 1) / 2;
					break;
				}
			}			
			if (seat[6] == 'F')
			{
				row = rowRange.first;
			}
			else if (seat[6] == 'B')
			{
				row = rowRange.second;
			}

			seatRange = std::make_pair<int, int>(0, 7);
			for (int j = 7; j < 9; j++)
			{
				int lower = seatRange.first;
				int upper = seatRange.second;
				switch (seat[j])
				{
				case 'L':
					seatRange.second -= ((upper - lower + 1) / 2);
					break;
				case 'R': 
					seatRange.first += ((upper - lower + 1) / 2);
					break;
				}
			}
			if (seat[9] == 'L')
			{
				column = seatRange.first;
			}
			else if (seat[9] == 'R')
			{
				column = seatRange.second;
			}

			seatIds.push_back((row * 8) + column);
		}		
	}

	int GetHighestID()
	{		
		std::sort(seatIds.begin(), seatIds.end());
		seatsHaveBeenSorted = true;
		return seatIds[seatIds.size() - 1];
	}

	int FindMissingSeat()
	{
		if (!seatsHaveBeenSorted)
		{
			std::sort(seatIds.begin(), seatIds.end()); // idiot proof
		}
		for (int i = 1; i < seatIds.size(); i++)
		{			
			if (seatIds[i] - 1 != seatIds[i - 1])
			{
				return seatIds[i] - 1;
				break;
			}
		}
	}
};

/*
*	354
*	346
*	348
*	349
*/
