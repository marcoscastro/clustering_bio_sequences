#include <iostream>
#include <string>
#include "tests.h"
#include "common.h"
#include "distance_strings.h"

void Tests::runAllTests()
{
	testLevenshteinDistance1();
	testLevenshteinDistance2();
	testLevenshteinDistance3();

	testNeedlemanWunsch1();
	testNeedlemanWunsch2();

	testDoubleEquals();

	testWhiteSimilarity1();
	testWhiteSimilarity2();

	testLcsDistance();

	testHammingDistance();

	testSmithWaterman();
}

bool Tests::testLevenshteinDistance1()
{
	std::string s1("AACTGG"), s2("ACTGGGG");
	double expected = 3;
	double result = levenshteinDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLevenshteinDistance1\n";
		return true;
	}

	std::cout << "Fail in the test: testLevenshteinDistance1\n";
	return false;
}

bool Tests::testLevenshteinDistance2()
{
	std::string s1("CCCCTGACACACTG"), s2("CTCTG");
	double expected = 9;
	double result = levenshteinDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLevenshteinDistance2\n";
		return true;
	}

	std::cout << "Fail in the test: testLevenshteinDistance2\n";
	return false;
}

bool Tests::testLevenshteinDistance3()
{
	std::string s1("A"), s2("C");
	double expected = 1;
	double result = levenshteinDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLevenshteinDistance3\n";
		return true;
	}

	std::cout << "Fail in the test: testLevenshteinDistance3\n";
	return false;
}

bool Tests::testNeedlemanWunsch1()
{
	std::string s1("AAAA"), s2("CCCC");
	int expected = 0;
	int result = nwDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testNeedlemanWunsch1\n";
		return true;
	}

	std::cout << "Fail in the test: testNeedlemanWunsch1\n";
	return false;
}

bool Tests::testNeedlemanWunsch2()
{
	std::string s1("GAATTCAGTTA"), s2("GGATCGA");
	int expected = 6;
	int result = nwDistance(s1, s2, 1, 0, 0);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testNeedlemanWunsch2\n";
		return true;
	}

	std::cout << "Fail in the test: testNeedlemanWunsch2\n";
	return false;
}

bool Tests::testDoubleEquals()
{
	double x = 0.333333, y = 0;

	if(almost_equals_double(x, y) == false)
	{
		std::cout << "Success in the test: testDoubleEquals\n";
		return true;
	}

	std::cout << "Fail in the test: testDoubleEquals\n";
	return false;
}

bool Tests::testWhiteSimilarity1()
{
	std::string s1("FRANCE"), s2("FRENCH");

	double expected = 40;
	double result = wsDistance(s1, s2, 2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testWhiteSimilarity1\n";
		return true;
	}

	std::cout << "Fail in the test: testWhiteSimilarity1\n";
	return false;
}

bool Tests::testWhiteSimilarity2()
{
	std::string s1("ACTG"), s2("GTCA");
	double expected = 0;
	double result = wsDistance(s1, s2, 2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testWhiteSimilarity2\n";
		return true;
	}

	std::cout << "Fail in the test: testWhiteSimilarity2\n";
	return false;
}

bool Tests::testLcsDistance()
{
	std::string s1("AGCAT"), s2("GAC");

	double expected = 4;
	double result = lcsDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLcsDistance\n";
		return true;
	}

	std::cout << "Fail in the test: testLcsDistance\n";
	return false;
}

bool Tests::testHammingDistance()
{
	std::string s1("ACAGG"), s2("AGTGG");

	double expected = 3;
	double result = hammingDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testHammingDistance\n";
		return true;
	}

	std::cout << "Fail in the test: testHammingDistance\n";
	return false;
}

bool Tests::testSmithWaterman()
{
	std::string s1("CGAT"), s2("CGAT");
	double expected = 4;
	double result = swDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testSmithWaterman\n";
		return true;
	}

	std::cout << "Fail in the test: testSmithWaterman\n";
	return false;
}