#include "pipeMaze.hpp"

void maze::ParseInput(tools::mat<char>& matrix)
{
	std::fstream pipeMazeFile;
	pipeMazeFile.open(maze::path, std::ios::in);

	if (pipeMazeFile.is_open())
	{
		std::string currentLine;
		while (std::getline(pipeMazeFile, currentLine, '\n'))
		{
			for (char ch : currentLine)
				matrix.push_back(ch);
		}
	}
	pipeMazeFile.close();
}

void maze::MoveToTheNextTile(size_t& i, size_t& j, tools::mat<char> matrix, size_t& prevI, size_t& prevJ)
{
	size_t iDirection = 0;
	size_t jDirection = 0;

	switch (matrix.at(i, j))
	{
	case '|':
		if (prevI < i)
			iDirection = 1;
		else
			iDirection = -1;
		break;

	case '-':
		if (prevJ < j)
			jDirection = 1;
		else
			jDirection = -1;
		break;

	case 'L':
		if (prevI == i)
			iDirection = -1;
		else
			jDirection = 1;
		break;

	case 'J':
		if (prevI == i)
			iDirection = -1;
		else
			jDirection = -1;
		break;

	case '7':
		if (prevI == i)
			iDirection = 1;
		else
			jDirection = -1;
		break;

	case 'F':
		if (prevI == i)
			iDirection = 1;
		else
			jDirection = 1;
		break;

	}

	prevI = i;
	prevJ = j;
	i += iDirection;
	j += jDirection;

}

int maze::CalcSteps()
{
	std::fstream pipeMazeFile;
	pipeMazeFile.open(maze::path, std::ios::in);
	std::string firstLine;
	std::getline(pipeMazeFile, firstLine, '\n');
	pipeMazeFile.close();
	tools::mat<char> matrix(firstLine.size());
	maze::ParseInput(matrix);

	size_t iStartPos = 0;
	size_t jStartPos = 0;
	maze::agent firstAgent;
	maze::agent secondAgent;
	for (size_t i = 0; i < matrix.len(); i++)
	{
		bool flag = false;
		for (size_t j = 0; j < matrix.len(); j++)
		{
			if (matrix.at(i, j) == 'S')
			{
				iStartPos = i;
				jStartPos = j;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}


	firstAgent.iPos = iStartPos;
	firstAgent.jPos = jStartPos - 1; // going up according to input
	firstAgent.prevIPos = iStartPos;
	firstAgent.prevJPos = jStartPos;
	secondAgent.iPos = iStartPos - 1; // going left according to input
	secondAgent.jPos = jStartPos;
	secondAgent.prevIPos = iStartPos;
	secondAgent.prevJPos = jStartPos;

	while (true)
	{
		maze::MoveToTheNextTile(firstAgent.iPos, firstAgent.jPos, matrix, firstAgent.prevIPos, firstAgent.prevJPos);
		firstAgent.numOfSteps++;
		if (firstAgent.iPos == secondAgent.iPos && firstAgent.jPos == secondAgent.jPos)
			break;
		maze::MoveToTheNextTile(secondAgent.iPos, secondAgent.jPos, matrix, secondAgent.prevIPos, secondAgent.prevJPos);
		if (firstAgent.iPos == secondAgent.iPos && firstAgent.jPos == secondAgent.jPos)
			break;
	}

	return firstAgent.numOfSteps;
}

int maze::CalcEnclosedTiles()
{
	std::fstream pipeMazeFile;
	pipeMazeFile.open(maze::path, std::ios::in);
	std::string firstLine;
	std::getline(pipeMazeFile, firstLine, '\n');
	pipeMazeFile.close();
	tools::mat<char> matrix(firstLine.size());
	maze::ParseInput(matrix);

	std::vector<std::pair<size_t, size_t>> mainLoopTiles;

	size_t iStartPos = 0;
	size_t jStartPos = 0;
	maze::agent firstAgent;
	maze::agent secondAgent;
	for (size_t i = 0; i < matrix.len(); i++)
	{
		bool flag = false;
		for (size_t j = 0; j < matrix.column_size; j++)
		{
			if (matrix.at(i, j) == 'S')
			{
				iStartPos = i;
				jStartPos = j;
				flag = true;
				matrix.set(i, j, 'J'); // based on input
				break;
			}
		}
		if (flag)
			break;
	}

	firstAgent.iPos = iStartPos - 1;
	firstAgent.jPos = jStartPos;
	firstAgent.prevIPos = iStartPos;
	firstAgent.prevJPos = jStartPos;
	secondAgent.iPos = iStartPos; 
	secondAgent.jPos = jStartPos - 1;
	secondAgent.prevIPos = iStartPos;
	secondAgent.prevJPos = jStartPos;
					
	mainLoopTiles.push_back({ iStartPos, jStartPos });
	mainLoopTiles.push_back({ firstAgent.iPos, firstAgent.jPos });
	mainLoopTiles.push_back({ secondAgent.iPos, secondAgent.jPos });

	while (true)
	{
		maze::MoveToTheNextTile(firstAgent.iPos, firstAgent.jPos, matrix, firstAgent.prevIPos, firstAgent.prevJPos);
		if (firstAgent.iPos == secondAgent.iPos && firstAgent.jPos == secondAgent.jPos)
			break;
		mainLoopTiles.push_back({ firstAgent.iPos, firstAgent.jPos });

		maze::MoveToTheNextTile(secondAgent.iPos, secondAgent.jPos, matrix, secondAgent.prevIPos, secondAgent.prevJPos);
		if (firstAgent.iPos == secondAgent.iPos && firstAgent.jPos == secondAgent.jPos)
			break;
		mainLoopTiles.push_back({ secondAgent.iPos, secondAgent.jPos });
	}

	
	for (size_t i = 0; i < matrix.len(); i++)
	{
		for (size_t j = 0; j < matrix.column_size; j++)
		{
			std::pair<size_t, size_t> coordinates = { i, j };
			if (std::find(mainLoopTiles.begin(), mainLoopTiles.end(), coordinates) != mainLoopTiles.end())
				continue;
			matrix.set(i, j, '.');
		}
	}


	
	//std::vector<char> pipes = { '|', '-', 'L', 'J', '7', 'F', 'S' }; 
	// L7 count together, FJ count together S = F
	int numOfEncolesTiles = 0;
	
	for (size_t i = 0; i < matrix.len(); i++) // 133 too low, 1399, 155
	{
		size_t j = 0;
		size_t k = matrix.column_size - 1;
		while (j < matrix.column_size && matrix.at(i, j) == '.')
		{
			matrix.set(i, j, '0');
			j++;
		}
		while (k >= 0 && matrix.at(i, k) == '.')
		{
			matrix.set(i, k, '0');
			k--;
		}
	}
	
	// ---------------------- //
	for (size_t i = 0; i < matrix.len(); i++)  
	{
		bool isInside = false;
		char prevPipe;
		size_t j = 0;
		for (j; j < matrix.column_size; j++)
		{

			if ((matrix.at(i, j) != '.' && matrix.at(i, j) != '-' && matrix.at(i, j) != '0'))
			{
				prevPipe = matrix.at(i, j);
				break;
			}
		}
		for (j; j < matrix.column_size; j++)
		{
			if (matrix.at(i, j) == '-') 
				continue;

			if (matrix.at(i, j) == '|')
			{
				isInside = !isInside;
				prevPipe = matrix.at(i, j);
				continue;
			}


			if ((prevPipe == 'L' && matrix.at(i, j) == '7') || (prevPipe == 'F' && matrix.at(i, j) == 'J'))
			{
				isInside = !isInside;
				prevPipe = matrix.at(i, j);
				continue;
			}
			//std::cout << matrix.at(i, j);
			else if (matrix.at(i, j) == '.' && isInside)
				numOfEncolesTiles++;
		
			prevPipe = matrix.at(i, j);
		}
				
	
	}
	
	return numOfEncolesTiles;
}