#include "boatRaces.hpp"

void boatRaces::ParseInputPart1(std::vector<std::pair<int, int>>& races)
{
	races = { {}, {}, {}, {} };
	std::fstream boatRacesFile;
	boatRacesFile.open("inputs\\boatRaces.txt", std::ios::in);
	if (boatRacesFile.is_open())
	{
		std::string currentLine;
		int lineIndex = 0;
		
		while (std::getline(boatRacesFile, currentLine, '\n'))
		{
			int pairIndex = 0;
			currentLine = currentLine.substr(11);
			std::stringstream sCurrentLine(currentLine);
			std::string currentNum;
			while (std::getline(sCurrentLine, currentNum, ' '))
			{
				if (!currentNum.empty())
				{
					if (lineIndex == 0)
						races[pairIndex].first = std::stoi(currentNum);
					else
						races[pairIndex].second = std::stoi(currentNum);
					pairIndex++;
					
				}
			}
			lineIndex++;
		}
	}
}

int boatRaces::CalcAmountOfWinsPart1(uint64_t time, uint64_t recordDistance)
{
	int wins = 0;
	for (int i = 1; i < time; i++)
	{
		int distanceTraveled = (time - i) * i;
		if (distanceTraveled > recordDistance)
			wins++;
	}
	return wins;
}

int boatRaces::CalcWinsProduct()
{
	int product = 1;
	std::vector<std::pair<int, int>> races;
	boatRaces::ParseInputPart1(races);
	for (std::pair<int, int> race : races)
		product *= boatRaces::CalcAmountOfWinsPart1(race.first, race.second);

	return product;
}

void boatRaces::ParseInputPart2(std::pair<uint64_t, uint64_t>& race)
{
	std::fstream boatRacesFile;
	boatRacesFile.open("inputs\\boatRaces.txt", std::ios::in);
	if (boatRacesFile.is_open())
	{
		std::string currentLine;
		int lineIndex = 0;
		std::string timeNum;
		std::string distNum;
		while (std::getline(boatRacesFile, currentLine, '\n'))
		{
			currentLine = currentLine.substr(11);
			std::stringstream sCurrentLine(currentLine);
			std::string currentNum;
			while (std::getline(sCurrentLine, currentNum, ' '))
			{
				if (!currentNum.empty())
				{
					if (lineIndex == 0)
						timeNum += currentNum;
					else
						distNum += currentNum;
					
				}
			}
			lineIndex++;
		}
		race.first = std::stoull(timeNum);
		race.second = std::stoull(distNum);
	}
}

uint64_t boatRaces::CalcAmountOfWinsPart2()
{
	uint64_t wins = 0;
	std::pair<uint64_t, uint64_t> race;
	boatRaces::ParseInputPart2(race);
	for (uint64_t i = 1; i < race.first; i++)
	{
		uint64_t distanceTraveled = (race.first - i) * i;
		if (distanceTraveled > race.second)
			wins++;
	}
	return wins;
}

