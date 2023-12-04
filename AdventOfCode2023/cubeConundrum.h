#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace cubeConundrum
{
	constexpr int redCubeAmount = 12;
	constexpr int greenCubeAmount = 13;
	constexpr int blueCubeAmount = 14;

	void ParseFileInput(std::vector<std::string>& output);
	void ParseStringInput(std::vector<std::string>& output, char delimiter, std::string& input);
	bool IsGameValid(std::vector<std::string>& roundsOutput);
	int LowestPossibleCubeAmount(std::vector<std::string>& roundsOutput);

	int CalcSumOfPowerSets();
	int CalcPossibleGames();
}