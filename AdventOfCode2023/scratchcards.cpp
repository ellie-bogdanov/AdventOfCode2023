#include "scratchcards.hpp"

void scratchcards::ParseInput(std::vector<scratchcards::Card>& cards)
{
	std::fstream scratchcardsFile;
	scratchcardsFile.open("inputs\\scratchcards.txt", std::ios::in);
	if (scratchcardsFile.is_open())
	{
		std::string currentLine;
		int id = 1;
		while (std::getline(scratchcardsFile, currentLine, '\n'))
		{
			int startingIndex = 10;
			currentLine = currentLine.substr(startingIndex);
			Card card;
			scratchcards::ParseCard(card, currentLine);
			cards.push_back(card);
		}
	}
}

void scratchcards::ParseCard(scratchcards::Card& card, std::string cardLine)
{
	std::string currentNum;
	bool isInWiningCards = true;
	for (int i = 0; i < cardLine.size(); i++)
	{
		if (std::isdigit(cardLine.at(i)))
			currentNum += cardLine.at(i);

		else if (cardLine.at(i) == ' ' && !currentNum.empty())
		{

			if (isInWiningCards)
				card.winingNumbers.insert(std::stol(currentNum));
			else
				card.myNumbers.insert(std::stol(currentNum));

			currentNum.clear();
		}
		else if (cardLine.at(i) == '|')
		{
			i++;
			isInWiningCards = false;
		}
		
	}
	card.myNumbers.insert(std::stol(currentNum));
}

int scratchcards::CalcCardWorth(scratchcards::Card& card)
{
	int power = -1;
	for (long num : card.winingNumbers)
	{
		if (std::binary_search(card.myNumbers.begin(), card.myNumbers.end(), num))
			power++;

	}
	card.amountOfWinings = power + 1;
	if (power == -1)
		return 0;

	return std::pow(2, power);
}

unsigned long long scratchcards::CalcTotalCards()
{
	std::vector<scratchcards::Card> cards;
	scratchcards::ParseInput(cards);
	unsigned long long totalAmountOfCards = 0;
	for (int i = 0; i < cards.size(); i++)
	{
		totalAmountOfCards += cards[i].amountOfCards;
		scratchcards::CalcCardWorth(cards[i]);
		for (int j = i + 1; j <= i + cards[i].amountOfWinings; j++)
		{
			if (j == cards.size())
				break;

			cards[j].amountOfCards += cards[i].amountOfCards;
		}

	}

	return totalAmountOfCards;


}

int scratchcards::CalcTotalPoints()
{
	std::vector<scratchcards::Card> cards;
	scratchcards::ParseInput(cards);
	int sum = 0;

	for (scratchcards::Card card : cards)
		sum += scratchcards::CalcCardWorth(card);

	return sum;
}