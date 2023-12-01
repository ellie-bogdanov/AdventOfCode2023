#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>


/*
std::fstream crateStacksFile;
crateStacksFile.open("C:\\Users\\guybo\\source\\repos\\AdventOfCode\\crateStacks.txt", std::ios::in);
*/

void ParseInput(std::vector<std::string>& input);
std::string FirstLastDigitOfStr(std::string& calibrationValue);
int StrToInteger(std::string& str);
int CalibrationSum();