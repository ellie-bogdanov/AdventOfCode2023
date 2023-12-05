#include <iostream>
#include "scratchcards.hpp"


void PopulateVector(std::vector<char>& input, std::string temp)
{
	for (char c : temp)
	{
		input.push_back(c);
	}
}

int main()
{
	unsigned long long sum = scratchcards::CalcTotalCards();
	std::cout << sum;


	return 0;
}