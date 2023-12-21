#pragma once

#include <vector>
#include <string>

namespace springs
{
	struct SpringGroup
	{
	public:
		std::vector<char> originalGroup;
		std::vector<std::vector<char>> allPossibilities;
		std::vector<std::string> unkownGroupPossibilities;
		std::vector<int> contiguousGroupSize;
		size_t amountOfUnknowns;
		
		
		void GenerateAllPossibillities(std::vector<char> possibility, uint64_t& amountOfValid);
		
		bool CheckValidPossibility(const std::vector<char>& possility);
		
	};
	bool CheckForAllValid(const std::vector<char>& possibility);
	void AddPossibily(std::vector<char>& possibility);
	int CalcAllValidPossibilities();
	void TestingGenerate(std::vector<std::vector<char>>& allCombinations, size_t amountToTest);

	void PrintSprings();
	std::string vecToStr(std::vector<char> vec);
	void ParseInputPart1(std::vector<springs::SpringGroup>& allSprings);
	void ParseInputPart2(std::vector<springs::SpringGroup>& allSprings);


}