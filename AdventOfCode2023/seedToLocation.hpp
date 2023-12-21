#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace seedToLoc
{
	struct Range
	{
		 long long destRangeStart;
		 long long sourceRangeStart;
		 long long rangeLen;
		Range( long long destRangeStart,
			 long long sourceRangeStart,
			 long long rangeLen);
		void PrintRange();
	};

	class Seed
	{
	public:
		long long currentValue;
		long long rangeLen;
		Seed(long long initialValue);
		Seed(long long initialValue,  long long rangeLen);
		Seed();
		bool CheckIfInRange(const seedToLoc::Range& range);
		void CalcNextValue(const seedToLoc::Range& range);

		void PrintSeed();



	};
	long long CalcLowestLocationPart1();
	long long CalcLowestLocationPart2();
	long long CalcLowestLocationPart2Fixed();
	struct SeedRange
	{
		long long startingValue;
		long long rangeLen;
		bool isUpdated = false;
		SeedRange* left;
		SeedRange* right;

		
		SeedRange(SeedRange* seed); // copy constructor
		SeedRange();
		void SplitSeeds(const Range& range);
		void UpdateSeedRanges(const seedToLoc::Range& range);
		long long FindMin();

	};

	SeedRange* NewSeedRange(long long startingValue,  long long rangeLen);
	void DestroyTree(SeedRange* seeds, std::vector<SeedRange*>& seedRanges);

	void ParseInputPart1(std::vector<std::vector<Range>>& mapsOfRanges, std::vector<Seed>& seeds);
	void ParseInputPart2(std::vector<std::vector<Range>>& mapsOfRanges, std::vector<std::pair< long long, 
		 long long>>& seeds);
	void ParseInputPart2Fixed(std::vector<std::vector<seedToLoc::Range>>& mapsOfRanges, std::vector<seedToLoc::SeedRange*>& seedRanges);
	
}