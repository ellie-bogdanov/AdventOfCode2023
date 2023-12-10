#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

namespace boatRaces // from 11
{
	//Part 1
	void ParseInputPart1(std::vector<std::pair<int, int>>& races);
	int CalcWinsProduct();
	int CalcAmountOfWinsPart1(uint64_t time, uint64_t recordDistance);
	//----

	//Part 2
	void ParseInputPart2(std::pair<uint64_t, uint64_t>& race);
	uint64_t CalcAmountOfWinsPart2();
	//----

}