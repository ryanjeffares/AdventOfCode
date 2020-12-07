#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

struct Passport
{
    std::string byr, iyr, eyr, hgt, hcl, ecl, pid, cid;
};

class Solver
{
private:
	std::string requiredFields[7] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	std::vector<std::string> allLines;  
    std::vector<std::string> firstValidPassports;
    std::vector<Passport> validPassports;
    int count = 0;

    enum fieldName
    {
        eByr, eIyr, eEyr, eHgt, eHcl, eEcl, ePid
    };

    fieldName GetFieldEnum(std::string const& field)
    {
        if (field == "byr") return eByr;
        if (field == "iyr") return eIyr;
        if (field == "eyr") return eEyr;
        if (field == "hgt") return eHgt;
        if (field == "hcl") return eHcl;
        if (field == "ecl") return eEcl;
        if (field == "pid") return ePid;
    }

    void ParseFields(Passport& passport, std::string line)
    {
        for (auto field : requiredFields)
        {
            if (line.find(field) == std::string::npos) continue;
            auto pos = line.find(field) + 4;
            switch (GetFieldEnum(field))
            {
            case eByr: passport.byr = line.substr(pos, line.find("|", pos) - 1);
                break;
            case eIyr: passport.iyr = line.substr(pos, line.find("|", pos) - 1);
                break;
            case eEyr: passport.eyr = line.substr(pos, line.find("|", pos) - 1);
                break;
            case eHgt: passport.hgt = line.substr(pos, line.find("|", pos) - 1);
                break;
            case eHcl: passport.hcl = line.substr(pos, line.find("|", pos) - 1);
                break;
            case eEcl: passport.ecl = line.substr(pos, line.find("|", pos) - 1);
                break;
            case ePid: passport.pid = line.substr(pos, line.find("|", pos) - 1);
                break;
            }
        }
    }

public:
    Solver() 
    {
        std::ifstream file("input.txt");
        std::string line;        
        while (std::getline(file, line))
        {
            if (line.empty())
            {
                count++;
            }
            allLines.push_back(line);
        }
    }

	void GetPassports()
	{        
        int index = 0;
        std::vector<std::string> unorganizedPassports(count + 1);        
        for (std::string s : allLines)
        {
            if (s == "")
            {
                index++;
            }
            unorganizedPassports[index] += s;     
            unorganizedPassports[index] += "|";
        }        
        
        for (auto passport : unorganizedPassports)
        {
            Passport currentPassport;
            ParseFields(currentPassport, passport);
            validPassports.push_back(currentPassport);
        }        
	}

	int ValidatePassportsPartOne(std::vector<std::string> passports)
	{
        int invalidPassports = 0;
        for (std::string passport : passports)
        {
            std::cout << passport << "\n";
            int existingFields = 0;
            for (std::string field : requiredFields)
            {
                if (passport.find(field) != std::string::npos)
                {
                    existingFields++;
                }
            }
            if (existingFields < 7)
            {
                invalidPassports++;
            }
            else 
            {
                firstValidPassports.push_back(passport);
            }
        }    
        return passports.size() - invalidPassports;
	}

    int ValidatePassportsPartTwo()
    {
        // we know we don't have to check the ones we already found were invalid above 
        // so it would look like this
        // byr:1971iyr:2017 hgt:160cmeyr:2020 ecl:hzlpid:157096267
        
    }
};