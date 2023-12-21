#pragma once

#include <vector>

namespace galaxy
{
	struct Tile
	{
		long long rowNum;
		long long colNum;
		bool isGalaxy;
	};


	using Space = std::vector<std::vector<galaxy::Tile>>;
	void ParseInput(Space& space);
	void Expand(Space& space, long long expansionSpeed);
	long long CalcLengthSum();


}