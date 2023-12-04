#include <iostream>
#include "gearRatios.h"

void PopulateVector(std::vector<char>& input, std::string temp)
{
	for (char c : temp)
	{
		input.push_back(c);
	}
}

int main()
{
	int sum = gearRatios::SumOfProductsOfEngineParts();
	std::cout << sum;

	
	return 0;
}