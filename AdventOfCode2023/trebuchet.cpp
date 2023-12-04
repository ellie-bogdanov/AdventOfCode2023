#include "trebuchet.h"

void trebuchet::ParseInput(std::vector<std::string>& input)
{
	std::fstream trebuchetFile;
	trebuchetFile.open("C:\\Users\\guybo\\source\\repos\\AdventOfCode2023\\AdventOfCode2023\\inputs\\trebuchet.txt", std::ios::in);
	if (trebuchetFile.is_open())
	{
		std::string inputStr;
		while (getline(trebuchetFile, inputStr, '\n'))
		{
			input.push_back(inputStr);
		}
	}
}
std::string trebuchet::FirstLastDigitOfStr(std::string& calibrationValue)
{
	std::string allDigitsInStr;

	for (int i = 0; i < calibrationValue.length(); i++)
	{
		int len = calibrationValue.length();
		if (isdigit(calibrationValue.at(i)))
		{
			allDigitsInStr += calibrationValue.at(i);
		}
		else
		{
			switch (calibrationValue.at(i))
			{
			case 'o':
				if (i < len - 2)
				{
					if (calibrationValue.at(i + 1) == 'n' && calibrationValue.at(i + 2) == 'e') // one
					{
						allDigitsInStr += '1';
					}
				}
				break;
			case 't':
				if (i < len - 2)
				{
					if (calibrationValue.at(i + 1) == 'w' && calibrationValue.at(i + 2) == 'o') // two
					{
						allDigitsInStr += '2';
					}
				}
				if (i < len - 4)
				{
					if (calibrationValue.at(i + 1) == 'h' && calibrationValue.at(i + 2) == 'r'
						&& calibrationValue.at(i + 3) == 'e' && calibrationValue.at(i + 4) == 'e') // three
					{
						allDigitsInStr += '3';
					}
				}
				break;
			case 'f':
				if (i < len - 3)
				{
					
					if (calibrationValue.at(i + 1) == 'o' && calibrationValue.at(i + 2) == 'u'
						&& calibrationValue.at(i + 3) == 'r') // four
					{
						allDigitsInStr += '4';
					}
					else if (calibrationValue.at(i + 1) == 'i' && calibrationValue.at(i + 2) == 'v'
						&& calibrationValue.at(i + 3) == 'e') // five
					{
						allDigitsInStr += '5';
					}
				}
				break;
			case 's':
				if (i < len - 2)
				{
					if (calibrationValue.at(i + 1) == 'i' && calibrationValue.at(i + 2) == 'x') // six
					{
						allDigitsInStr += '6';
					}
				}
				if (i < len - 4)
				{
					if (calibrationValue.at(i + 1) == 'e' && calibrationValue.at(i + 2) == 'v'
						&& calibrationValue.at(i + 3) == 'e' && calibrationValue.at(i + 4) == 'n') // seven
					{
						allDigitsInStr += '7';
					}
				}
				break;
			case 'e':
				if (i < len - 4)
				{
					if (calibrationValue.at(i + 1) == 'i' && calibrationValue.at(i + 2) == 'g'
						&& calibrationValue.at(i + 3) == 'h' && calibrationValue.at(i + 4) == 't') // eight
					{
						allDigitsInStr += '8';
					}
				}
				break;
			case 'n':
				if (i < len - 3)
				{
					if (calibrationValue.at(i + 1) == 'i' && calibrationValue.at(i + 2) == 'n'
						&& calibrationValue.at(i + 3) == 'e') // nine
					{
						allDigitsInStr += '9';
					}
				}
				break;
			}
		}



	}
	std::string firstLastDigits;
	if (firstLastDigits.length() == 1)
	{
		return firstLastDigits;
	}
	firstLastDigits += allDigitsInStr.at(0);
	firstLastDigits += allDigitsInStr.at(allDigitsInStr.length() - 1);
	return firstLastDigits;
}

int trebuchet::CalibrationSum()
{
	std::vector<std::string> input;
	trebuchet::ParseInput(input);
	int sum = 0;
	for (std::string val : input)
	{
		std::string firstLastDigit = FirstLastDigitOfStr(val);
		//std::cout << val << '\n';
		sum += StrToInteger(firstLastDigit);
	}
	return sum;
}

int trebuchet::StrToInteger(std::string& str) // Not Working
{
	int val = 0;
	for (int i = 0; i < str.length(); i++)
	{
		int digit = str.at(i) - '0';
		val += digit * pow(10, str.length() - i - 1);
	}
	return val;
}