#include <iostream>
#include "seedToLocation.hpp"
#include<chrono>

void PopulateVector(std::vector<char>& input, std::string temp)
{
	for (char c : temp)
	{
		input.push_back(c);
	}
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << seedToLoc::CalcLowestLocationPart2Fixed() << '\n';
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;
	return 0;
}