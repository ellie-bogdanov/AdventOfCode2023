#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <set>
#include <algorithm>
#include <sstream>

//start at index 10

namespace scratchcards
{
	struct Card
	{
	public:
		unsigned long long amountOfCards = 1;
		std::set<long> winingNumbers;
		std::set<long> myNumbers;
		int amountOfWinings = 0;

	};
	void ParseInput(std::vector<scratchcards::Card>& cards);
	void ParseCard(scratchcards::Card& card, std::string cardLine);
	int CalcCardWorth(scratchcards::Card& card);
	int CalcTotalPoints();
	unsigned long long CalcTotalCards();
}