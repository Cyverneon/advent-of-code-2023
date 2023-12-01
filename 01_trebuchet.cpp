#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// https://adventofcode.com/2023/day/1
// solution by cyverneon

std::vector<int> findSubstringIndexes(std::string searchString, std::string subString)
{
    std::vector<int> indexes;
    int index = searchString.find(subString, 0);
    while (index != std::string::npos)
    {
        indexes.push_back(index);
        index = searchString.find(subString, index + subString.size());
    }
    return indexes;
}

int main()
{
    std::ifstream input;
    input.open("input.txt");

    std::string number_spellings[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::map<int, std::vector<int>> substringIndexes;

    int total = 0;

    std::vector<int> test = findSubstringIndexes("oneoneoneoneoneone", "one");
    std::cout << test.size() << "\n";

    if (!input)
    {
        std::cout << "Couldn't open input file";
    }
    else
    {
        std::string line;

        while (std::getline(input, line))
        {
            substringIndexes.clear();
            for (int i = 1; i < 10; i++)
            {
                substringIndexes.insert({ i, findSubstringIndexes(line, number_spellings[i-1]) });
            }

            std::string firstDigit = "0";
            std::string secondDigit = "0";
            bool gotFirstDigit = false;

            std::istringstream stream(line);
            char character;
            
            std::cout << line << '\n';
            for (int c = 0; c < line.size(); c++)
            {
                stream >> character;
                if (character >= 48 && character <= 57)
                {
                    if (!gotFirstDigit)
                    {
                        firstDigit = character;
                        gotFirstDigit = true;
                    }
                    secondDigit = character;
                }
                else
                {
                    for (int i = 1; i < 10; i++)
                    {
                        for (int j = 0; j < substringIndexes[i].size(); j++)
                        {
                            if (c == substringIndexes[i][j])
                            {
                                if (!gotFirstDigit)
                                {
                                    firstDigit = (char)(i + 48);
                                    gotFirstDigit = true;
                                }
                                secondDigit = (char)(i + 48);
                            }
                        }
                    }
                }
            }
            std::cout << "firstDigit: " << firstDigit << ", " << "secondDigit: " << secondDigit << '\n';
            total += std::stoi(firstDigit + secondDigit);
        }
    }
    std::cout << total << "\n";
    return 0;
}
