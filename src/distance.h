#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

/*
	This file contains function prototypes to calculate
	the distance between two sequences (strings)
*/

class Distance
{

private:
	std::string s1, s2;
	int size_s1, size_s2;

public:
	Distance(std::string& s1, std::string& s2);
	int levenshteinDistance();
	int needlemanWunsch(int match = 1, int mismatch = -1, int gap = -1);
};

#endif
