#ifndef _DISTANCE_STRINGS_H_
#define _DISTANCE_STRINGS_H_

#include <algorithm>
#include <vector>
#include <string>
#include <math.h>

/*
	This file contains function prototypes to calculate
	the distance between two sequences (strings)
*/

class DistanceStrings
{

private:
	std::string s1, s2;
	int size_s1, size_s2;

public:
	DistanceStrings(std::string& s1, std::string& s2);
	int levenshteinDistance();
	int needlemanWunsch(int match = 1, int mismatch = -10, int gap = -10);
};

#endif
