#include "cubeConundrum.h"

void cubeConundrum::ParseFileInput(std::vector<std::string>& output)
{
	std::fstream cubeConundrumFile;
	cubeConundrumFile.open("C:\\Users\\guybo\\source\\repos\\AdventOfCode2023\\AdventOfCode2023\\inputs\\cubeConundrum.txt", std::ios::in);

	std::string input;
	if(cubeConundrumFile.is_open())
	{
		while (std::getline(cubeConundrumFile, input, '\n'))
		{
			output.push_back(input);
		}
	}
}
void cubeConundrum::ParseStringInput(std::vector<std::string>& output, char delimiter, std::string& input)
{
	std::stringstream inputStream(input);
	std::string currentLine;
	while (std::getline(inputStream, currentLine, delimiter))
	{
		output.push_back(currentLine);
	}
}

bool cubeConundrum::IsGameValid(std::vector<std::string>& roundsOutput)
{
	for (int i = 0; i < roundsOutput.size(); i++)
	{
		std::vector<std::string> singularRoundOutput;
		cubeConundrum::ParseStringInput(singularRoundOutput, ',', roundsOutput.at(i));
		std::vector<std::string> cubeOutput;
		for (std::string cube : singularRoundOutput)
		{
			std::vector<std::string> cubeInfo;
			cubeConundrum::ParseStringInput(cubeInfo, ' ', cube);
			std::string color = cubeInfo.at(2); // at index 0 is empty string
			int amount = stoi(cubeInfo.at(1));
			if (color == "red")
			{
				if (amount > cubeConundrum::redCubeAmount)
				{
					return false;
				}
			}
			else if (color == "green")
			{
				if (amount > cubeConundrum::greenCubeAmount)
				{
					return false;
				}
			}
			else if (color == "blue")
			{
				if (amount > cubeConundrum::blueCubeAmount)
				{
					return false;
				}
			}
			else
			{
				std::cout << "something is wrond????";
			}
		}
	}
	return true;
}

int cubeConundrum::LowestPossibleCubeAmount(std::vector<std::string>& roundsOutput)
{
	int maxRed = 0;
	int maxGreen = 0;
	int maxBlue = 0;
	for (int i = 0; i < roundsOutput.size(); i++)
	{
		std::vector<std::string> singularRoundOutput;
		cubeConundrum::ParseStringInput(singularRoundOutput, ',', roundsOutput.at(i));
		std::vector<std::string> cubeOutput;
		for (std::string cube : singularRoundOutput)
		{
			std::vector<std::string> cubeInfo;
			cubeConundrum::ParseStringInput(cubeInfo, ' ', cube);
			std::string color = cubeInfo.at(2); // at index 0 is empty string
			int amount = stoi(cubeInfo.at(1));
			if (color == "red")
			{
				if (maxRed < amount)
					maxRed = amount;
			}
			else if (color == "green")
			{
				if (maxGreen < amount)
					maxGreen = amount;
			}
			else if (color == "blue")
			{
				if (maxBlue < amount)
					maxBlue = amount;
			}
			else
			{
				std::cout << "something is wrond????";
			}
		}
	}
	return maxRed * maxBlue * maxGreen;
}

int cubeConundrum::CalcPossibleGames()
{
	std::vector<std::string> output;
	cubeConundrum::ParseFileInput(output);
	int possibleGamesSum = 0;

	for (int i = 0; i < output.size(); i++)
	{
		std::vector<std::string> gameOutput;
		cubeConundrum::ParseStringInput(gameOutput, ':', output.at(i));
		std::vector<std::string> roundsOutput;
		cubeConundrum::ParseStringInput(roundsOutput, ';', gameOutput.at(1));
		if (cubeConundrum::IsGameValid(roundsOutput))
		{
			std::vector<std::string> gameIdOutput;
			cubeConundrum::ParseStringInput(gameIdOutput, ' ', gameOutput.at(0));
			int id = stoi(gameIdOutput.at(1));
			possibleGamesSum += id;
		}
	}

	return possibleGamesSum;
}

int cubeConundrum::CalcSumOfPowerSets()
{
	std::vector<std::string> output;
	cubeConundrum::ParseFileInput(output);
	int sumOfPowerSets = 0;

	for (int i = 0; i < output.size(); i++)
	{
		std::vector<std::string> gameOutput;
		cubeConundrum::ParseStringInput(gameOutput, ':', output.at(i));
		std::vector<std::string> roundsOutput;
		cubeConundrum::ParseStringInput(roundsOutput, ';', gameOutput.at(1));
		sumOfPowerSets += cubeConundrum::LowestPossibleCubeAmount(roundsOutput);
	}

	return sumOfPowerSets;
}