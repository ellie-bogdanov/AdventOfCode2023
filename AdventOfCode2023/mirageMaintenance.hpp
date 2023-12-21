#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

namespace mirage
{
	static constexpr bool calcLastVal = false;  // true to calculate part 1, false for part 2
	void ParseInput(std::vector<std::vector<int>>& history);
	int CalcVal(std::vector<int>& values);
	int CalcValuesSum();

}