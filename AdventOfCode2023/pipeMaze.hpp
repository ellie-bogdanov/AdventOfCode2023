#pragma once

#include<string>
#include <fstream>
#include <vector>
#include <iostream>
#include "tools.cpp"

namespace maze
{
	const std::string path = "inputs\\pipeMaze.txt";

	void ParseInput(tools::mat<char>& matrix);
	void MoveToTheNextTile(size_t& i, size_t& j, tools::mat<char> matrix, size_t& prevI, size_t& prevJ);
	int CalcSteps();
	int CalcEnclosedTiles();

	struct agent
	{
		int numOfSteps = 1;
		size_t iPos;
		size_t jPos;
		size_t prevIPos;
		size_t prevJPos;
	};
}