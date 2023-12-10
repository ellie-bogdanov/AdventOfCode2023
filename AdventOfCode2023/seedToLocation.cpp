#include "seedToLocation.hpp"

seedToLoc::Seed::Seed( long long initialValue)
{
	currentValue = initialValue;
}

seedToLoc::Seed::Seed( long long initialValue,  long long rangeLen) : currentValue(initialValue), rangeLen(rangeLen)
{

}

seedToLoc::Seed::Seed()
{
	currentValue = 0;
}

void seedToLoc::Seed::PrintSeed()
{
	std::cout << currentValue << " ";
}

bool seedToLoc::Seed::CheckIfInRange(const seedToLoc::Range& range)
{
	return currentValue >= range.sourceRangeStart && currentValue <= range.sourceRangeStart + range.rangeLen;
}

void seedToLoc::Seed::CalcNextValue(const seedToLoc::Range& range) //dest - source
{
	currentValue = currentValue + (range.destRangeStart - range.sourceRangeStart);
}

seedToLoc::Range::Range( long long destRangeStart,
	 long long sourceRangeStart,
	 long long rangeLen) : destRangeStart(destRangeStart), sourceRangeStart(sourceRangeStart), rangeLen(rangeLen)
{

}
void seedToLoc::Range::PrintRange()
{
	std::cout << destRangeStart << " " << sourceRangeStart << " " << rangeLen;
}

void seedToLoc::ParseInputPart1(std::vector<std::vector<seedToLoc::Range>>& mapsOfRanges, std::vector<seedToLoc::Seed>& seeds)
{
	std::fstream seedToLocationFile;
	seedToLocationFile.open("inputs\\seedToLocation.txt", std::ios::in);

	if (seedToLocationFile.is_open())
	{
		std::string currentLine;
		std::getline(seedToLocationFile, currentLine, '\n');
		std::getline(seedToLocationFile, currentLine, '\n');
		std::stringstream sCurrentLine(currentLine);
		std::string currentSeedNum;
		while (std::getline(sCurrentLine, currentSeedNum, ' '))
			seeds.push_back({ stoll(currentSeedNum) });
		
		std::getline(seedToLocationFile, currentLine, '\n');
		std::getline(seedToLocationFile, currentLine, '\n');
		std::vector<seedToLoc::Range> currentRanges;
		while (std::getline(seedToLocationFile, currentLine, '\n'))
		{
			if (currentLine.empty())
			{
				mapsOfRanges.push_back(currentRanges);
				currentRanges.clear();
				continue;
			}
			if (std::isdigit(currentLine.at(0)))
			{
				std::stringstream sCurrentLine(currentLine);
				std::string currentNum;
				 long long currentRange[3];
				int index = 0;
				while (std::getline(sCurrentLine, currentNum, ' '))
				{
					currentRange[index] = std::stoll(currentNum);
					index++;
				}
				currentRanges.push_back({ currentRange[0], currentRange[1] , currentRange[2] });
			}		
			
		}
		mapsOfRanges.push_back(currentRanges);
	}
}

 long long seedToLoc::CalcLowestLocationPart1()
{
	std::vector<std::vector<seedToLoc::Range>> mapsOfRanges;
	std::vector<seedToLoc::Seed> seeds;
	seedToLoc::ParseInputPart1(mapsOfRanges, seeds);

	 long long min = ULLONG_MAX;
	for (seedToLoc::Seed seed : seeds)
	{
		for (std::vector<seedToLoc::Range> mapRange : mapsOfRanges)
		{
			for (const seedToLoc::Range& range : mapRange)
			{
				if (seed.CheckIfInRange(range))
				{
					seed.CalcNextValue(range);
					break;
				}
			}
		}
		if (seed.currentValue < min)
			min = seed.currentValue;
	}
	
	return min;
}

void seedToLoc::ParseInputPart2(std::vector<std::vector<seedToLoc::Range>>& mapsOfRanges, std::vector<std::pair< long long,  long long>>& seeds)
{
	std::fstream seedToLocationFile;
	seedToLocationFile.open("inputs\\seedToLocation.txt", std::ios::in);

	if (seedToLocationFile.is_open())
	{
		std::string currentLine;
		std::getline(seedToLocationFile, currentLine, '\n');
		std::getline(seedToLocationFile, currentLine, '\n');
		std::stringstream sCurrentLine(currentLine);
		std::string currentSeedNum;
		int	seedIndex = 1; // starts from 1 not 0 on purpose
		std::pair< long long,  long long> currentSeedRange;
		while (std::getline(sCurrentLine, currentSeedNum, ' '))
		{
			if (seedIndex % 2 != 0)
			{
				currentSeedRange.first = std::stoll(currentSeedNum);
				seedIndex++;
			}
			else
			{
				currentSeedRange.second = std::stoll(currentSeedNum);
				seeds.push_back(currentSeedRange);
				seedIndex++;
			}

		}

		std::getline(seedToLocationFile, currentLine, '\n');
		std::getline(seedToLocationFile, currentLine, '\n');
		std::vector<seedToLoc::Range> currentRanges;
		while (std::getline(seedToLocationFile, currentLine, '\n'))
		{
			if (currentLine.empty())
			{
				mapsOfRanges.push_back(currentRanges);
				currentRanges.clear();
				continue;
			}
			if (std::isdigit(currentLine.at(0)))
			{
				std::stringstream sCurrentLine(currentLine);
				std::string currentNum;
				 long long currentRange[3];
				int index = 0;
				while (std::getline(sCurrentLine, currentNum, ' '))
				{
					currentRange[index] = std::stoll(currentNum);
					index++;
				}
				currentRanges.push_back({ currentRange[0], currentRange[1] , currentRange[2] });
			}

		}
		mapsOfRanges.push_back(currentRanges);
	}
}

 long long seedToLoc::CalcLowestLocationPart2()
{
	std::vector<std::vector<seedToLoc::Range>> mapsOfRanges;
	std::vector<std::pair< long long,  long long>> seedRanges;
	seedToLoc::ParseInputPart2(mapsOfRanges, seedRanges);

	 long long min = ULLONG_MAX;
	for (std::pair< long long,  long long> seedRange : seedRanges)
	{
		for (size_t i = seedRange.first; i <= seedRange.first + seedRange.second; i++)
		{
			seedToLoc::Seed currentSeed(i);
			for (std::vector<seedToLoc::Range> mapRange : mapsOfRanges)
			{
				for (const seedToLoc::Range& range : mapRange)
				{
					if (currentSeed.CheckIfInRange(range))
					{
						currentSeed.CalcNextValue(range);
						break;
					}
				}
			}
			if (currentSeed.currentValue < min)
				min = currentSeed.currentValue;

		}


	}

	return min;
}
seedToLoc::SeedRange::SeedRange()
{

}


void seedToLoc::ParseInputPart2Fixed(std::vector<std::vector<seedToLoc::Range>>& mapsOfRanges, std::vector<seedToLoc::SeedRange*>& seedRanges)
{
	std::fstream seedToLocationFile;
	seedToLocationFile.open("inputs\\seedToLocation.txt", std::ios::in);

	if (seedToLocationFile.is_open())
	{
		std::string currentLine;
		std::getline(seedToLocationFile, currentLine, '\n');
		std::getline(seedToLocationFile, currentLine, '\n');
		std::stringstream sCurrentLine(currentLine);
		std::string currentSeedNum;
		int	seedIndex = 1; // starts from 1 not 0 on purpose
		std::pair< long long,  long long> seedRange;
		while (std::getline(sCurrentLine, currentSeedNum, ' '))
		{
			if (seedIndex % 2 != 0)
			{
				seedRange.first = std::stoll(currentSeedNum);
				seedIndex++;
			}
			else
			{
				seedRange.second = std::stoll(currentSeedNum);
				
				seedRanges.emplace_back(seedToLoc::NewSeedRange(seedRange.first, seedRange.second));
				seedIndex++;
			}

		}

		std::getline(seedToLocationFile, currentLine, '\n');
		std::getline(seedToLocationFile, currentLine, '\n');
		std::vector<seedToLoc::Range> currentRanges;
		while (std::getline(seedToLocationFile, currentLine, '\n'))
		{
			if (currentLine.empty())
			{
				mapsOfRanges.push_back(currentRanges);
				currentRanges.clear();
				continue;
			}
			if (std::isdigit(currentLine.at(0)))
			{
				std::stringstream sCurrentLine(currentLine);
				std::string currentNum;
				 long long currentRange[3];
				int index = 0;
				while (std::getline(sCurrentLine, currentNum, ' '))
				{
					currentRange[index] = std::stoll(currentNum);
					index++;
				}
				currentRanges.push_back({ currentRange[0], currentRange[1] , currentRange[2] });
			}

		}
		mapsOfRanges.push_back(currentRanges);
	}
}

seedToLoc::SeedRange* seedToLoc::NewSeedRange(long long startingValue,  long long rangeLen)

{
	seedToLoc::SeedRange* temp = new SeedRange;
	temp->startingValue = startingValue;
	temp->rangeLen = rangeLen;
	temp->left = temp->right = nullptr;
	return temp;
}

void seedToLoc::SeedRange::SplitSeeds(const Range& range)
{


	
	
	long long leftStartVal = startingValue;
	long long leftRange = range.sourceRangeStart - leftStartVal;
	long long rightStartVal = range.sourceRangeStart + range.rangeLen;
	long long rightRange = (range.sourceRangeStart + range.rangeLen) - (startingValue + rangeLen);

	if(left == nullptr && right == nullptr && !isUpdated)
	{
		if (startingValue < range.sourceRangeStart &&
			startingValue + rangeLen - 1 > range.sourceRangeStart)
		{
			left = seedToLoc::NewSeedRange(leftStartVal, leftRange);
			startingValue += leftRange;
			rangeLen -= leftRange;
		}
		if (startingValue + rangeLen - 1 > range.sourceRangeStart + range.rangeLen - 1 &&
			startingValue < range.sourceRangeStart + range.rangeLen - 1)
		{
			right = seedToLoc::NewSeedRange(rightStartVal, rightRange);
			rangeLen -= rightRange;
		}
	}
	if (left != nullptr)
		left->SplitSeeds(range);
	if (right != nullptr)
		right->SplitSeeds(range);

	UpdateSeedRanges(range);


}

void seedToLoc::SeedRange::UpdateSeedRanges(const seedToLoc::Range& range)
{

	if ((startingValue >= range.sourceRangeStart) &&
		(startingValue + rangeLen - 1) <= (range.sourceRangeStart + range.rangeLen - 1) && !isUpdated)
	{
		startingValue += range.destRangeStart - range.sourceRangeStart;
		isUpdated = true;
		//rangeLen += range.destRangeStart - range.sourceRangeStart;
	}
	if (left != nullptr)
		left->UpdateSeedRanges(range);
	if (right != nullptr)
		right->UpdateSeedRanges(range);

}

seedToLoc::SeedRange::SeedRange(seedToLoc::SeedRange* seed)
{
	startingValue = seed->startingValue;
	rangeLen = seed->rangeLen;
	left = nullptr;
	right = nullptr;
}

 long long seedToLoc::SeedRange::FindMin()
{
	if (this == nullptr)
		return LLONG_MAX;

	long long res = startingValue;
	long long lres = left->FindMin();
	long long rres = right->FindMin();

	if (lres < res)
		res = lres;
	if (rres < res)
		res = rres;
	return res;

}

 void seedToLoc::DestroyTree(seedToLoc::SeedRange* seeds, std::vector<seedToLoc::SeedRange*>& seedRanges)
 {
	 if (seeds->left != nullptr)
		 DestroyTree(seeds->left, seedRanges);
	 if (seeds->right != nullptr)
		 DestroyTree(seeds->right, seedRanges);

	seedToLoc::SeedRange* removed = seedToLoc::NewSeedRange(seeds->startingValue, seeds->rangeLen);
	seedRanges.push_back(removed);
	 
	 

 }

 long long seedToLoc::CalcLowestLocationPart2Fixed()
{
	std::vector<std::vector<seedToLoc::Range>> rangeMaps;
	std::vector<seedToLoc::SeedRange*> seedRanges;

	seedToLoc::ParseInputPart2Fixed(rangeMaps, seedRanges);
	long long min = LLONG_MAX;


	for (std::vector<seedToLoc::Range> rangeMap : rangeMaps)
	{


		for(seedToLoc::Range range : rangeMap)
		{
			for (seedToLoc::SeedRange* seedRange : seedRanges)
			{
				if (seedRange != nullptr)
					seedRange->SplitSeeds(range);
				
				//seedRange->UpdateSeedRanges(range);

			}
			
		}
		
		int currentLength = seedRanges.size();
		for (int i = 0; i < currentLength; i++)
		{
			seedToLoc::DestroyTree(seedRanges[0], seedRanges);
			seedRanges.erase(seedRanges.begin());
		}
	}
	
	for (seedToLoc::SeedRange* seeds : seedRanges)
	{
		long long newMin = seeds->FindMin();
		if (newMin < min)
			min = newMin;
	}

	return min;
}