#ifndef _TESTS_H_
#define _TESTS_H_
#include "distance.h"

class Tests
{
public:

	void run()
	{
		testLevenshteinDistance1();
	}

	bool testLevenshteinDistance1()
	{
		std::string s1("AACTGG"), s2("ACTGGGG");
		int expected = 3;

		Distance dist(s1, s2);
		int result = dist.levenshteinDistance();

		if(result == expected)
		{
			std::cout << "Success in the test: testLevenshteinDistance1\n";
			return true;
		}

		std::cout << "Fail in the test: testLevenshteinDistance1\n";
		return false;
	}
};

#endif
