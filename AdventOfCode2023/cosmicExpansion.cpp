#include "cosmicExpansion.hpp"

#include <fstream>
#include <string>
#include <iostream>


void galaxy::ParseInput(Space& space)
{
	std::fstream cosmicExpansionFile;
	cosmicExpansionFile.open("inputs\\cosmicExpansion.txt", std::ios::in);

	if (cosmicExpansionFile.is_open())
	{
		std::string currentLine;
		while (std::getline(cosmicExpansionFile, currentLine, '\n'))
		{
			std::vector<galaxy::Tile> temp;
			for (char ch : currentLine)
			{
				bool isGalaxy = ch == '#';
				temp.push_back({ 1, 1, isGalaxy });
			}
			space.push_back(temp);

		}
		cosmicExpansionFile.close();
	}
}
void galaxy::Expand(Space& space, long long expansionSpeed)
{
	for (size_t i = 0; i < space.size(); i++)
	{
		bool areNoGalaxies = true;
		for (size_t j = 0; j < space[i].size(); j++)
		{
			if (space[i][j].isGalaxy)
			{
				areNoGalaxies = false;
				break;
			}
		}
		if (areNoGalaxies)
		{
			for (size_t j = 0; j < space[i].size(); j++)
				space[i][j].colNum *= expansionSpeed;
		}
	}


	for (size_t j = 0; j < space[0].size(); j++)
	{
		bool areNoGalaxies = true;
		for (size_t i = 0; i < space.size(); i++)
		{
			if (space[i][j].isGalaxy)
			{
				areNoGalaxies = false;
				break;
			}
		}
		if (areNoGalaxies)
		{
			for (size_t i = 0; i < space.size(); i++)
				space[i][j].rowNum *= expansionSpeed;
		}
	}
}



long long galaxy::CalcLengthSum()
{
	galaxy::Space space;
	galaxy::ParseInput(space);
	galaxy::Expand(space, 1000000);

	long long sum = 0;
	std::vector<std::pair<size_t, size_t>> galaxyLocations;
	for (size_t i = 0; i < space.size(); i++)
	{
		for (size_t j = 0; j < space[i].size(); j++)
		{
			if (space[i][j].isGalaxy)
				galaxyLocations.push_back({i, j});
		}
	}

	for (size_t i = 0; i < galaxyLocations.size() - 1; i++)
	{
		
		for (size_t j = i + 1; j < galaxyLocations.size(); j++)
		{
			long long directionHorizontal = 0;
			long long directionVertical = 0;
			if (galaxyLocations[i].first < galaxyLocations[j].first)
				directionVertical = -1;
			else if(galaxyLocations[i].first > galaxyLocations[j].first)
				directionVertical = 1;

			if (galaxyLocations[i].second < galaxyLocations[j].second)
				directionHorizontal = -1;
			else if (galaxyLocations[i].second > galaxyLocations[j].second)
				directionHorizontal = 1;

			
			bool isIn = false;
			for (size_t k = galaxyLocations[j].first; k != galaxyLocations[i].first; k += directionVertical)
			{
				isIn = true;
				if (k == galaxyLocations[j].first)
				{
					continue;
				}
				sum += space[k][galaxyLocations[j].first].colNum;
			}
			if(isIn)
				sum += space[galaxyLocations[i].first][galaxyLocations[j].first].colNum;
			isIn = false;
			for (size_t l = galaxyLocations[j].second; l != galaxyLocations[i].second; l += directionHorizontal)
			{
				isIn = true;
				if (l == galaxyLocations[j].second)
					continue;
				sum += space[galaxyLocations[j].second][l].rowNum;
			}
			if(isIn)
				sum += space[galaxyLocations[j].second][galaxyLocations[i].second].rowNum;
			
		}
		
	}

	return sum;
}