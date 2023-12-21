#include "hotSprings.hpp"

#include <fstream>
#include <iostream>

void springs::ParseInputPart1(std::vector<springs::SpringGroup>& allSprings)
{
	std::fstream hotSpringsFile;
	hotSpringsFile.open("inputs\\hotSpringsSample.txt", std::ios::in);
	if (hotSpringsFile.is_open())
	{
		std::string currentLine;
		while (std::getline(hotSpringsFile, currentLine, '\n'))
		{
			springs::SpringGroup currentGroup = { {}, {}, {}, {}, 0};
			size_t index = 0;
			while (currentLine[index] != ' ')
			{
				currentGroup.originalGroup.push_back(currentLine[index]);
				if (currentLine[index] == '?')
					currentGroup.amountOfUnknowns++;
				index++;
			}
			index++;
			std::string currentNum;
			for (index; index < currentLine.size(); index++)
			{
				if (std::isdigit(currentLine[index]))
					currentNum += currentLine[index];
				else
				{
					currentGroup.contiguousGroupSize.push_back(std::stoi(currentNum));
					currentNum.clear();
				}
			}
			currentGroup.contiguousGroupSize.push_back(std::stoi(currentNum));
			allSprings.push_back(currentGroup);
		}
		hotSpringsFile.close();
	}
}
bool springs::CheckForAllValid(const std::vector<char>& possibility)
{
	for (char ch : possibility)
	{
		if (ch != '.')
		{
			return false;
		}
	}
	return true;
}
void springs::SpringGroup::GenerateAllPossibillities(std::vector<char> possibility, uint64_t& amountOfValid)
{

	
	bool areAllValid = true;
	for (char ch : possibility)
	{
		if (ch != '.')
		{
			areAllValid = false;
			break;
		}
	}

	
	while(!CheckForAllValid(possibility))
	{
		amountOfValid += CheckValidPossibility(possibility);
		AddPossibily(possibility);
	}
	amountOfValid += CheckValidPossibility(possibility);

	
}

void springs::TestingGenerate(std::vector<std::vector<char>>& allCombinations, size_t amountToTest)
{
	std::vector<char> baseCase;
	for (size_t i = 1; i <= amountToTest; i++)
		baseCase.push_back('#');
	while (!CheckForAllValid(baseCase))
	{
		allCombinations.push_back(baseCase);
		springs::AddPossibily(baseCase);
	}

}

void springs::AddPossibily(std::vector<char>& possibility)
{
	size_t index = 0;
	while (possibility[index] == '.')
	{
		possibility[index] = '#';
		index++;
	}
	possibility[index] = '.';
}



bool springs::SpringGroup::CheckValidPossibility(const std::vector<char>& possibility)
{
	std::vector<char> currentRow = originalGroup;
	size_t unknownIndex = 0;
	for (size_t i = 0; i < currentRow.size(); i++)
	{
		if (currentRow[i] == '?')
		{
			currentRow[i] = possibility[unknownIndex];
			unknownIndex++;
		}
	}

	int currentAmountOfBroken = 0;
	size_t groupSizeIndex = 0;
	bool isFirstValid = false;
	
	std::vector<int> groupsOfBroken;
	for (size_t i = 0; i < currentRow.size(); i++)
	{
		if (currentRow[i] == '#')
		{
			currentAmountOfBroken++;
			isFirstValid = true;
		}

		else if (isFirstValid)
		{
			if (groupSizeIndex == contiguousGroupSize.size() || currentAmountOfBroken != contiguousGroupSize[groupSizeIndex])
				return false;

			currentAmountOfBroken = 0;
			groupSizeIndex++;
			isFirstValid = false;
			

		}
	}
	if (currentRow[currentRow.size() - 1] == '#')
	{
		if (groupSizeIndex == contiguousGroupSize.size() || currentAmountOfBroken != contiguousGroupSize[groupSizeIndex])
			return false;
		groupSizeIndex++;
	}
	if (groupSizeIndex != contiguousGroupSize.size())
		return false;

	return true;
}


int springs::CalcAllValidPossibilities()
{
	std::vector<springs::SpringGroup> allSprings;
	springs::ParseInputPart1(allSprings);
	uint64_t amountOfValid = 0;

	for (springs::SpringGroup group : allSprings)
	{
		std::cout << amountOfValid << std::endl;
		std::vector<char> starterPossibility;
		for (size_t i = 0; i < group.amountOfUnknowns; i++)
			starterPossibility.push_back('#');
		group.GenerateAllPossibillities(starterPossibility, amountOfValid);
		/*
		for (std::vector<char> possibility : group.allPossibilities)
		{
			if (group.CheckValidPossibility(possibility))
				amountOfValid++;
		}
		*/
	}
	return amountOfValid;
}


void springs::PrintSprings()
{
	std::vector<springs::SpringGroup> allSprings;
	springs::ParseInputPart1(allSprings);

	for (springs::SpringGroup springGroup : allSprings)
	{
		
		for (int num : springGroup.contiguousGroupSize)
			std::cout << num << " ";
		std::cout << std::endl;
	}
}

std::string springs::vecToStr(std::vector<char> vec)
{
	std::string strVec;
	for (char ch : vec)
		strVec += ch;
	return strVec;
}

void springs::ParseInputPart2(std::vector<springs::SpringGroup>& allSprings)
{
	std::fstream hotSpringsFile;
	hotSpringsFile.open("inputs\\hotSpringsSample.txt", std::ios::in);
	uint64_t maxUnknowns = 0;
	if (hotSpringsFile.is_open())
	{
		std::string currentLine;
		while (std::getline(hotSpringsFile, currentLine, '\n'))
		{
			springs::SpringGroup currentGroup = { {}, {}, {}, {}, 0 };
			size_t index = 0;

			while (currentLine[index] != ' ')
			{
				currentGroup.originalGroup.push_back(currentLine[index]);
				index++;
			}
			currentGroup.originalGroup.push_back('?');
			size_t originalSize = currentGroup.originalGroup.size();
			for (size_t i = 1; i <= 5; i++)
			{
				for (size_t j = 0; j < originalSize; j++)
					currentGroup.originalGroup.push_back(currentGroup.originalGroup[j]);
			}
			currentGroup.originalGroup.pop_back();
			for (size_t i = 0; i < currentGroup.originalGroup.size(); i++)
			{
				if (currentGroup.originalGroup[i] == '?')
					currentGroup.amountOfUnknowns++;
			}
			if (currentGroup.amountOfUnknowns > maxUnknowns)
				maxUnknowns = currentGroup.amountOfUnknowns;
			index++;
			std::string currentNum;
			for (index; index < currentLine.size(); index++)
			{
				if (std::isdigit(currentLine[index]))
					currentNum += currentLine[index];
				else
				{
					currentGroup.contiguousGroupSize.push_back(std::stoi(currentNum));
					currentNum.clear();
				}
			}
			currentGroup.contiguousGroupSize.push_back(std::stoi(currentNum));
			originalSize = currentGroup.contiguousGroupSize.size();
			for (size_t i = 1; i <= 5; i++)
			{
				for (size_t j = 0; j < originalSize; j++)
					currentGroup.contiguousGroupSize.push_back(currentGroup.contiguousGroupSize[j]);
			}
			allSprings.push_back(currentGroup);
		}
		hotSpringsFile.close();
	}
	std::cout << maxUnknowns << std::endl;
}