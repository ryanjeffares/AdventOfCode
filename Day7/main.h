#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <iterator>
#include <algorithm>

struct Rule
{
	std::string colour;
	std::vector<std::string> bagColours;
	std::vector<int> numColours;	
};

class Solver
{
private:
	std::vector<std::string> allLines;
	std::vector<Rule> rules;

	std::vector<std::string> Split(const std::string str, const std::string regexStr)
	{
		std::regex regexz(regexStr);
		std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
			std::sregex_token_iterator());
		return list;
	}

public:
	Solver()
	{
		std::ifstream file("input.txt");
		std::string line;
		while (std::getline(file, line))
		{
			allLines.push_back(line);
		}
	}

	void GetRules()
	{
		for (std::string& rule : allLines)
		{
			// mirrored magenta bags contain 3 mirrored gray bags, 2 plaid beige bags, 4 dull brown bags, 3 pale plum bags.
			// first two words = colour
			// after contain, int and colour
			// after each comma			
			if (rule.find("contain no other bags") != std::string::npos)
			{
				continue;
			}
			Rule currentRule;
			currentRule.colour = rule.substr(0, rule.find("bags") - 1);

			auto pos = rule.find("contain") + 8;			
			std::string contents = rule.substr(pos, std::string::npos);
			if (contents[contents.size() - 1] == '.')
			{
				contents.pop_back();
			}
			auto contentsVec = Split(contents, ", ");
			for (int i = 0; i < contentsVec.size(); i++)
			{
				if (contentsVec[i][contentsVec[i].size() - 1] == 's')
				{
					contentsVec[i] = contentsVec[i].substr(0, contentsVec[i].length() - 5);
				}
				else
				{
					contentsVec[i] = contentsVec[i].substr(0, contentsVec[i].length() - 4);
				}
				std::string c;
				c += contentsVec[i][0]; // none of the amounts are 10 or more - i checked :)
				currentRule.bagColours.push_back(contentsVec[i].substr(2, std::string::npos));
				currentRule.numColours.push_back(atoi(c.c_str()));
			}						
			rules.push_back(currentRule);
		}
	}

	int FindBagColours()
	{
		int totalCount = 0;		
		std::vector<std::string> checkedColours;

		// for each rule, check all colours
		// check their rules, etc recursively
		// add each checked colour to vector
		// if colour is already in, continue
		// if shiny gold found, add 1 to count and continue

		for (auto& rule : rules)
		{			
			int tempCount = 0;	// temp in to count bags checked on one recursive check
			CheckColours(rule, totalCount, checkedColours, tempCount);
		}
		return totalCount;
	}

	void CheckColours(Rule& rule, int& count, std::vector<std::string>& checked, int& tempCount)
	{				
		for (auto& colour : rule.bagColours)
		{				
			tempCount++;	// increment the temp counter
			if (std::find(checked.begin(), checked.end(), colour) == checked.end()) // if we havent already checked this colour...
			{							
				checked.push_back(colour);	// mark it as checked
				auto it = std::find_if(rules.begin(), rules.end(), [&colour](const Rule& _rule) {return _rule.colour == colour; });
				if (it != rules.end())	// continue down the same path with the bag that matches the colour we just checked
				{							
					CheckColours(*it, count, checked, tempCount);
				}
			}	
			else if (colour == "shiny gold")	// if we can hold a shiny gold bag
			{
				count += tempCount;				// add the amount of bags weve checked to the total count
			}
		}
	}
};

// bag        yellow		   red			
//			/   |   \	    /   |   \
//		  blue red  green
//		 / | \
//	  gold pink orange
//		   |	\
//		  gold  blue
//				 |
//				gold				