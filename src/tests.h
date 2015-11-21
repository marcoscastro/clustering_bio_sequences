#ifndef _TESTS_H_
#define _TESTS_H_
#include "distance.h"

class Tests
{
public:

	void runAllTests()
	{
		testLevenshteinDistance1();
		testLevenshteinDistance2();
		testLevenshteinDistance3();
		testNeedlemanWunsch1();
		testNeedlemanWunsch2();
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

	bool testLevenshteinDistance2()
	{
		std::string s1("CCCCTGACACACTG"), s2("CTCTG");
		int expected = 9;

		Distance dist(s1, s2);
		int result = dist.levenshteinDistance();

		if(result == expected)
		{
			std::cout << "Success in the test: testLevenshteinDistance2\n";
			return true;
		}

		std::cout << "Fail in the test: testLevenshteinDistance2\n";
		return false;
	}

	bool testLevenshteinDistance3()
	{
		std::string s1("A"), s2("C");
		int expected = 1;

		Distance dist(s1, s2);
		int result = dist.levenshteinDistance();

		if(result == expected)
		{
			std::cout << "Success in the test: testLevenshteinDistance3\n";
			return true;
		}

		std::cout << "Fail in the test: testLevenshteinDistance3\n";
		return false;
	}

	// https://en.wikipedia.org/wiki/Needleman–Wunsch_algorithm
	bool testNeedlemanWunsch1()
	{
		std::string s1("GCATGCU"), s2("GATTACA");
		int expected = 0;

		Distance dist(s1, s2);
		int result = dist.needlemanWunsch();

		if(result == expected)
		{
			std::cout << "Success in the test: testNeedlemanWunsch1\n";
			return true;
		}

		std::cout << "Fail in the test: testNeedlemanWunsch1\n";
		return false;
	}

	// http://www.avatar.se/molbioinfo2001/dynprog/dynamic.html
	bool testNeedlemanWunsch2()
	{
		std::string s1("GAATTCAGTTA"), s2("GGATCGA");
		int expected = 6;

		Distance dist(s1, s2);
		int result = dist.needlemanWunsch(1, 0, 0);

		if(result == expected)
		{
			std::cout << "Success in the test: testNeedlemanWunsch2\n";
			return true;
		}

		std::cout << "Fail in the test: testNeedlemanWunsch2\n";
		return false;
	}
};

#endif
