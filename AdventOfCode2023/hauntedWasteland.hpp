#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace wasteland
{
	void ParseInput(std::string& instructions, std::map<std::string, std::pair<std::string, std::string>>& directions);
	uint64_t CalcNumOfStepsPart1();
	uint64_t CalcNumOfStepsPart2();
	void AreGhostsOnZ(std::vector<std::pair<std::string, uint64_t>>& ghosts, std::vector<bool>& isZSeenByGhost);
	bool AreAllTrue(std::vector<bool> booleanVec);
	bool CheckForModulo(std::vector<uint64_t> steps, uint64_t valToCheck);
}