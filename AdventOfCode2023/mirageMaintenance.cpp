#include "mirageMaintenance.hpp"

void mirage::ParseInput(std::vector<std::vector<int>>& values)
{
	std::fstream mirageMaintenanceFile;
	mirageMaintenanceFile.open("inputs\\mirageMaintenance.txt", std::ios::in);

	if (mirageMaintenanceFile.is_open())
	{
		std::string currentLine;
		while (std::getline(mirageMaintenanceFile, currentLine, '\n'))
		{
			std::vector<int> currentHistory;
			std::string currentNum;
			for (char ch : currentLine)
			{
				if (ch == ' ')
				{
					currentHistory.push_back(std::stoi(currentNum));
					currentNum.clear();
				}
				else
					currentNum += ch;
			}
			currentHistory.push_back(std::stoi(currentNum));
			values.push_back(currentHistory);
		}
		mirageMaintenanceFile.close();
	}
}

int mirage::CalcVal(std::vector<int>& values)
{
	
	bool areAllZeroes = true;
	for (int val : values)
	{
		if (val != 0)
		{
			areAllZeroes = false;
			break;
		}
	}

	if (areAllZeroes)
		return 0;

	std::vector<int> nextVals;
	for (size_t i = 1; i < values.size(); i++)
		nextVals.push_back(values[i] - values[i - 1]);

	if(mirage::calcLastVal)
		return values[values.size() - 1] + mirage::CalcVal(nextVals);

	return values[0] - CalcVal(nextVals);
}



int mirage::CalcValuesSum()
{
	std::vector<std::vector<int>> history;
	mirage::ParseInput(history);
	int sum = 0;
	for (std::vector<int>& values : history)
		sum += mirage::CalcVal(values);

	return sum;
}