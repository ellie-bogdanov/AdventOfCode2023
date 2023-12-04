#pragma once

#include <vector>
#include<string>
#include<fstream>
#include <iostream>

namespace gearRatios
{
	void ParseInput(std::vector<std::vector<char>>& output);

	void PrintMatrix(std::vector<std::vector<char>>& matrix);

	int ReadNumber(std::vector<char>& line, int numIndex);

	int SumOfProductsOfEngineParts();

	int SumOfEngineParts();



}
