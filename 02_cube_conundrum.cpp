#include <iostream>
#include <vector>
#include <map>

#include <fstream>
#include <sstream>

std::vector<std::map<std::string, int>> games;
int redCubes = 0;
int greenCubes = 0;
int blueCubes = 0;

std::vector<std::string> splitString(std::string string, char delimiter)
{
    std::vector<std::string> returnVector;
    int index;
    while ((index = string.find(delimiter)) != std::string::npos)
    {
        returnVector.push_back(string.substr(0, index));
        string.erase(0, index+1);
    }
    returnVector.push_back(string);
    return returnVector;
}

void addGame(std::string game)
{
    std::map<std::string, int> newGame = {{"red", 0}, {"green", 0}, {"blue", 0}};

    game.erase(0, game.find(":")+2);
    std::vector<std::string> rounds = splitString(game, ';');
    for (int rNo = 0; rNo < rounds.size(); rNo++)
    {
        std::vector<std::string> cubes = splitString(rounds[rNo], ',');
        for (int cNo = 0; cNo < cubes.size(); cNo++)
        {
            std::string num = "";
            for (int i = 0; i < cubes[cNo].size(); i++)
            {
                if (cubes[cNo][i] >= '0' && cubes[cNo][i] <= '9')
                {
                    num += cubes[cNo][i];
                }
            }
            if (cubes[cNo].find("red") != std::string::npos)
                newGame["red"] = std::max(newGame["red"], stoi(num));
            else if (cubes[cNo].find("green") != std::string::npos)
                newGame["green"] = std::max(newGame["green"], stoi(num));
            else if (cubes[cNo].find("blue") != std::string::npos)
                newGame["blue"] = std::max(newGame["blue"], stoi(num));
        }
    }

    games.push_back(newGame);
}

void parseInput(std::string filename)
{
    std::ifstream input;
    input.open(filename);

    if (!input)
    {
        std::cout << "could not open input file" << std::endl;
    }
    else
    {
        std::string line;
        while (std::getline(input, line))
        {
            addGame(line);
        }   
    }
}

int main()
{
    parseInput("input.txt");
    redCubes = 12;
    greenCubes = 13;
    blueCubes = 14;

    int idSum = 0;

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i]["red"] <= redCubes && games[i]["green"] <= greenCubes && games[i]["blue"] <= blueCubes)
        {
            idSum += (i+1);
        }
    }

    std::cout << "Sum of possible game IDs: " << idSum << std::endl;

    int powersSum = 0;

    for (int i = 0; i < games.size(); i++)
    {
        powersSum += (games[i]["red"] * games[i]["green"] * games[i]["blue"]);
    }

    std::cout << "Sum of cubes powers: " << powersSum << std::endl;

    return 0;
}