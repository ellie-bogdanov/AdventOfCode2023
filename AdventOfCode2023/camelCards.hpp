#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>

namespace camelCards
{
	enum Cards
	{
		J = 1, T = 10, Q = 12, K = 13, A = 14
	};
	class CamelCards
	{
	public:
		std::map<char, int> hand;
		std::string handStr;
		uint64_t bid;
		int strength; 

		CamelCards(std::string _hand, uint64_t bid);
		void CalcStrength();
		int ConvertToNum(const char card);
		bool IsHandWins(const CamelCards& cc);

		bool operator<(const CamelCards& cc)
		{
			if (strength == cc.strength)
				return !IsHandWins(cc);

			return (strength < cc.strength);
		}

	};
	void ParseInput(std::vector<camelCards::CamelCards>& games);
	uint64_t TotalWinings();
}