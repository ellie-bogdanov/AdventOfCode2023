#include "hauntedWasteland.hpp"

void wasteland::ParseInput(std::string& instructions,
						   std::map<std::string, std::pair<std::string, std::string>>& directions)
{
	std::fstream hauntedWastelandFile;
	hauntedWastelandFile.open("inputs\\hauntedWasteland.txt", std::ios::in);

	if (hauntedWastelandFile.is_open())
	{
		std::string currentLine;
		std::getline(hauntedWastelandFile, currentLine, '\n');
		instructions = currentLine;
		std::getline(hauntedWastelandFile, currentLine, '\n');
		while (std::getline(hauntedWastelandFile, currentLine, '\n'))
		{
			std::string currentPlace = currentLine.substr(0, 3);
			std::string leftDirection = currentLine.substr(7, 3);
			std::string rightDirection = currentLine.substr(12, 3);
			directions[currentPlace] = { leftDirection, rightDirection };
		}
	}
}
uint64_t wasteland::CalcNumOfStepsPart1()
{
	std::string instructions;
	std::map<std::string, std::pair<std::string, std::string>> directions;
	wasteland::ParseInput(instructions, directions);
	uint64_t numOfSteps = 0;
	std::string currentPlace = "AAA";
	int amountOfZPassed = 0;
	int instructionIndex = 0;
	do
	{
		switch (instructions[instructionIndex])
		{
		case 'L':
			currentPlace = directions[currentPlace].first;
			break;
		case 'R':
			currentPlace = directions[currentPlace].second;
			break;
		default:
			std::cout << "Incorrect instruction" << std::endl;
			break;
		}
		if (currentPlace == "ZZZ")
			amountOfZPassed++;
		numOfSteps++;
		instructionIndex++;
		if (instructionIndex == instructions.size())
			instructionIndex = 0;
	} while (amountOfZPassed < 1);
	return numOfSteps;
}

void wasteland::AreGhostsOnZ(std::vector<std::pair<std::string, uint64_t>>& ghosts, std::vector<bool>& isZSeenByGhost)
{
	for (size_t i = 0; i < ghosts.size(); i++)
	{
		if (ghosts[i].first[2] == 'Z')
			isZSeenByGhost[i] = true;
	}
}

bool wasteland::AreAllTrue(std::vector<bool> booleanVec)
{
	for (bool val : booleanVec)
		if (!val)
			return false;
	return true;
}
uint64_t wasteland::CalcNumOfStepsPart2()
{
	std::vector<std::pair<std::string, uint64_t>> ghosts;
	std::vector<bool> isZSeenByGhost;
	std::string instructions;
	std::map<std::string, std::pair<std::string, std::string>> directions;
	wasteland::ParseInput(instructions, directions);
	for (const auto& direction : directions)
	{
		if (direction.first[2] == 'A')
			ghosts.push_back({ direction.first, 0 });
	}
	for (const auto& ghost : ghosts)
		isZSeenByGhost.push_back(false);
	int instructionIndex = 0;
	while (!wasteland::AreAllTrue(isZSeenByGhost))
	{
		switch (instructions[instructionIndex])
		{
		case 'L':
			
			for (size_t i = 0; i < ghosts.size(); i++)
			{
				ghosts[i].first = directions[ghosts[i].first].first;
			}
			
			break;
		case 'R':
			
			for (size_t i = 0; i < ghosts.size(); i++)
			{

				ghosts[i].first = directions[ghosts[i].first].second;
			}
			
			break;
			
		default:
			std::cout << "wrong direction" << std::endl;
			break;
			
		}
		for (size_t i = 0; i < ghosts.size(); i++)
		{
			if (!isZSeenByGhost[i])
				ghosts[i].second++;
		}
		wasteland::AreGhostsOnZ(ghosts, isZSeenByGhost);
		instructionIndex++;
		if (instructionIndex >= instructions.size())
			instructionIndex = 0;
	}

	uint64_t numOfSteps = ULLONG_MAX;
	uint64_t amountToAdd = 0;
	for (const auto& ghost : ghosts)
		if (ghost.second < numOfSteps)
			numOfSteps = ghost.second;

	std::vector<uint64_t> maxValues;
	amountToAdd = numOfSteps;
	
	for (auto& ghost : ghosts)
	{
		maxValues.push_back(ghost.second);
	}
	while (!wasteland::CheckForModulo(maxValues, numOfSteps))
	{
		numOfSteps += amountToAdd;
	}
	return numOfSteps;
}

bool wasteland::CheckForModulo(std::vector<uint64_t> steps, uint64_t valToCheck)
{
	for (uint64_t step : steps)
		if (valToCheck % step != 0)
			return false;
	return true;
}


