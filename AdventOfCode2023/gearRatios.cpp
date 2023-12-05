#include "gearRatios.h"

void gearRatios::PrintMatrix(std::vector<std::vector<char>>& matrix)
{
	for (std::vector<char> vec : matrix)
	{
		for (char c : vec)
			std::cout << c;
		std::cout << '\n';
	}
}

void gearRatios::ParseInput(std::vector<std::vector<char>>& input)
{
	std::fstream gearRatiosFile;
	gearRatiosFile.open("inputs\\gearRatios.txt", std::ios::in);

	if (gearRatiosFile.is_open())
	{
		std::string currentLine;
		while (std::getline(gearRatiosFile, currentLine, '\n'))
		{
			std::vector<char> line;
			currentLine.push_back('.');
			currentLine.insert(currentLine.begin(), '.');
			for (char c : currentLine)
				line.push_back(c);

			input.push_back(line);

		}

		std::vector<char> dotsVec;
		for (int i = 0; i < input.at(0).size(); i++)
			dotsVec.push_back('.');
		input.push_back(dotsVec);
		input.insert(input.begin(), dotsVec);
	}
}

int gearRatios::ReadNumber(std::vector<char>& line, int numIndex)
{
	
	if (!std::isdigit(line.at(numIndex)))
	{
		return 0;
	}
	
	while (std::isdigit(line.at(numIndex)))
	{
		numIndex--;
	}
	std::string num;
	numIndex++;
	while (std::isdigit(line.at(numIndex)))
	{
		num += line.at(numIndex);
		line.at(numIndex) = '.';
		numIndex++;
	}

	return stoi(num);
}
int gearRatios::SumOfProductsOfEngineParts()
{
	std::vector<std::vector<char>> input;
	ParseInput(input);

	int sum = 0;
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input.at(i).size(); j++)
		{

			if (input.at(i).at(j) == '*')
			{
				int adjacentDigitAmount = 0;
				int productOfNumbersAround = 1;
				bool checkIsDigitConnectedUp = false;
				bool checkIsDigitConnectedDown = false;
				if (std::isdigit(input.at(i - 1).at(j)))
				{
					adjacentDigitAmount++;
					productOfNumbersAround *= gearRatios::ReadNumber(input.at(i - 1), j);
					checkIsDigitConnectedUp = true;
				}
				if (std::isdigit(input.at(i + 1).at(j)))
				{
					adjacentDigitAmount++;
					productOfNumbersAround *= gearRatios::ReadNumber(input.at(i + 1), j);
					checkIsDigitConnectedDown = true;
				}
				if (!checkIsDigitConnectedUp)
				{
					if (std::isdigit(input.at(i - 1).at(j - 1)))
					{
						adjacentDigitAmount++;
						productOfNumbersAround *= gearRatios::ReadNumber(input.at(i - 1), j - 1);
					}
					if (std::isdigit(input.at(i - 1).at(j + 1)))
					{
						adjacentDigitAmount++;
						productOfNumbersAround *= gearRatios::ReadNumber(input.at(i - 1), j + 1);
					}
				}
				if (!checkIsDigitConnectedDown)
				{
					if (std::isdigit(input.at(i + 1).at(j - 1)))
					{
						adjacentDigitAmount++;
						productOfNumbersAround *= gearRatios::ReadNumber(input.at(i + 1), j - 1);
					}
					if (std::isdigit(input.at(i + 1).at(j + 1)))
					{
						adjacentDigitAmount++;
						productOfNumbersAround *= gearRatios::ReadNumber(input.at(i + 1), j + 1);
					}
				}
				if (std::isdigit(input.at(i).at(j - 1)))
				{
					adjacentDigitAmount++;
					productOfNumbersAround *= gearRatios::ReadNumber(input.at(i), j - 1);
				}
				if (std::isdigit(input.at(i).at(j + 1)))
				{
					adjacentDigitAmount++;
					productOfNumbersAround *= gearRatios::ReadNumber(input.at(i), j + 1);
				}

				if (adjacentDigitAmount != 2)
				{
					productOfNumbersAround = 0;
				}

				sum += productOfNumbersAround;
			}
		}
	}
	return sum;
}
int gearRatios::SumOfEngineParts()
{
	std::vector<std::vector<char>> input;
	ParseInput(input);

	int sum = 0;
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input.at(i).size(); j++)
		{
			
			if ((!std::isdigit(input.at(i).at(j))) && (input.at(i).at(j) != '.'))
			{
				sum += gearRatios::ReadNumber(input.at(i - 1), j);
				sum += gearRatios::ReadNumber(input.at(i - 1), j - 1);
				sum += gearRatios::ReadNumber(input.at(i - 1), j + 1);
				sum += gearRatios::ReadNumber(input.at(i + 1), j);
				sum += gearRatios::ReadNumber(input.at(i + 1), j - 1);
				sum += gearRatios::ReadNumber(input.at(i + 1), j + 1);
				sum += gearRatios::ReadNumber(input.at(i), j - 1);
				sum += gearRatios::ReadNumber(input.at(i), j + 1);

			}
			
		}
	}
	return sum;
}