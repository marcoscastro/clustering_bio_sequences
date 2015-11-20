#include <iostream>
#include "distance.h"

using namespace std;

// test distance
int main(int argc, char *argv[])
{
	std::string s1("ACTG"), s2("AAAAAAAAAA");

	Distance dist_levenshtein(s1, s2);

	cout << dist_levenshtein.levenshteinDistance() << endl;

	return 0;
}
