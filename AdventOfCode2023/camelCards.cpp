#include "camelCards.hpp"

camelCards::CamelCards::CamelCards(std::string _hand, uint64_t bid) : bid(bid), handStr(_hand)
{
	for (size_t i = 0; i < _hand.size(); i++)
	{	
		if (hand.find(_hand[i]) == hand.end())
			hand[_hand[i]] = 1;
		else
			hand[_hand[i]]++;
	}
	CalcStrength();
}

void camelCards::CamelCards::CalcStrength() // 249515436
{
	strength = 1;
	int sameSuit = 0;
	int numOfPairs = 0;
	for (const auto& card : hand)
	{
		if (card.first != 'J' && card.second > sameSuit)
		{
			sameSuit = card.second;
		}
		if (card.first != 'J' && card.second == 2)
			numOfPairs++;

	}
	
	if (sameSuit == 1 && hand['J'] == 1)
	{
		numOfPairs++;
	}

	if (sameSuit == 2 && hand['J'] == 1)
	{
		numOfPairs--;
	}

	sameSuit += hand['J'];


	if (sameSuit == 5)
		strength = 7;
	else if (sameSuit == 4)
		strength = 6;
	else if (sameSuit == 3 && numOfPairs >= 1)
		strength = 5;
	else if (sameSuit == 3)
		strength = 4;
	else if (numOfPairs == 2)
		strength = 3;
	else if (numOfPairs == 1) 
		strength = 2;

}

bool camelCards::CamelCards::IsHandWins(const camelCards::CamelCards& cc)
{
	for (int i = 0; i < handStr.size(); i++)
	{
		if (ConvertToNum(handStr[i]) > ConvertToNum(cc.handStr[i]))
			return true;
		else if (ConvertToNum(handStr[i]) < ConvertToNum(cc.handStr[i]))
			return false;
	}
	std::cout << "something is wrong???" << std::endl;
	return false;
}

int camelCards::CamelCards::ConvertToNum(const char card)
{
	int num = -1;
	if (std::isdigit(card))
		num = card - '0';

	switch (card)
	{
	case 'T':
		num = camelCards::Cards::T;
		break;
	case 'J':
		num = camelCards::Cards::J;
		break;
	case 'Q':
		num = camelCards::Cards::Q;
		break;
	case 'K':
		num = camelCards::Cards::K;
		break;
	case 'A':
		num = camelCards::Cards::A;
		break;
	}

	return num;
}

void camelCards::ParseInput(std::vector<camelCards::CamelCards>& games)
{
	std::fstream camelCardsFile;
	camelCardsFile.open("inputs\\camelCards.txt", std::ios::in);
	if (camelCardsFile.is_open())
	{
		std::string currentLine;
		while (std::getline(camelCardsFile, currentLine, '\n'))
		{
			std::string hand;
			std::string bid;
			size_t index = 0;
			while (currentLine[index] != ' ')
			{
				hand += currentLine[index];
				index++;
			}
			index++;
			for (index; index < currentLine.size(); index++)
				bid += currentLine[index];

			uint64_t numBid = std::stoull(bid);
			camelCards::CamelCards game(hand, numBid);
			if (games.size() == 0)
				games.push_back(game);
			else
			{
				bool isInserted = false;
				for (size_t i = 0; i < games.size(); i++)
				{
					if (game < games[i])
					{
						games.insert(games.begin() + i, game);
						isInserted = true;
						break;
					}
				}
				if(!isInserted)
					games.push_back(game);
			}

		}
	}
}

uint64_t camelCards::TotalWinings()
{
	std::vector<camelCards::CamelCards> games;
	uint64_t totalWins = 0;
	
	ParseInput(games);
	for (uint64_t i = 0; i < games.size(); i++)
	{
		uint64_t amountToAdd = games[i].bid * (i + 1);
		totalWins += amountToAdd;
	}
	
	return totalWins;
}