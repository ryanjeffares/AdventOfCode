#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

struct Group
{
	std::vector<std::string> answers;
	int count;
};

class Solver
{
private:
	std::vector<std::string> allLines;		
	int groupCount = 0;

public:
	Solver()
	{
		std::ifstream file("input.txt");
		std::string line;		
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				groupCount++;
			}			
			allLines.push_back(line);
		}
	}

	std::vector<std::string> GetGroups()
	{
		int index = 0;
		std::vector<std::string> groups(groupCount + 1);
		for (auto s : allLines)
		{
			if (s == "")
			{
				index++;
			}
			groups[index] += s;
		}
		return groups;
	}

	std::vector<Group> GetGroupCounts()
	{
		int index = 0;
		std::vector<Group> groups(groupCount + 1);
		for (auto s : allLines)
		{			
			if (s == "")
			{
				groups[index].count = groups[index].answers.size();
				index++;
			}
			else
			{
				groups[index].answers.push_back(s);
			}			
		}
		return groups;
	}

	int SumCountsPartOne()
	{
		std::vector<std::string> groups = GetGroups();
		int totalCount = 0;
		for (auto& group : groups)
		{
			std::vector<char> answers;
			for (auto c : group)
			{
				if (std::count(answers.begin(), answers.end(), c) == 0)
				{
					answers.push_back(c);
				}
			}			
			totalCount += answers.size();
		}
		return totalCount;
	}

	int SumCountsPartTwo()
	{
		std::vector<Group> groups = GetGroupCounts();		
		int totalCount = 0;
		for (Group& group : groups)
		{
			std::vector<std::string>& currentAnswers = group.answers;			
			// sort the answers in order of length to do the least checks - thanks stack overflow
			// https://stackoverflow.com/questions/18831470/sorting-a-string-vector-based-on-the-string-size
			std::sort(currentAnswers.begin(), currentAnswers.end(), []
				(const std::string& first, const std::string& second) 
				{
					return first.size() < second.size(); 
				});
			int count = 0;			
			for (char c : currentAnswers[0])
			{
				bool allAnswered = true;
				for (int i = 1; i < currentAnswers.size(); i++)
				{
					if (std::count(currentAnswers[i].begin(), currentAnswers[i].end(), c) == 0)
					{
						allAnswered = false;
						break;
					}
				}
				if (allAnswered)
				{
					count++;
				}
			}
			totalCount += count;
		}		
		return totalCount;
	}
};