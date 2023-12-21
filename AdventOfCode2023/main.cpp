#include <iostream>
#include "hotSprings.hpp"

#include<chrono>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::vector<char>> allCombinations;

	std::cout << springs::CalcAllValidPossibilities() << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;
	return 0;
}

