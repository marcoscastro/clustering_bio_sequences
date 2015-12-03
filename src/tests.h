#ifndef _TESTS_H_
#define _TESTS_H_
#include "distance_strings.h"
#include "distance_points.h"
#include "sequence_generator.h"
#include "common.h"

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

		testEuclideanDistance();
		testDoubleEquals();

		testWhiteSimilarity1();
		testWhiteSimilarity2();
		
		testLcsDistance();
		
		testHammingDistance();
	}

	bool testLevenshteinDistance1()
	{
		std::string s1("AACTGG"), s2("ACTGGGG");
		int expected = 3;
		int result = levenshteinDistance(s1, s2);

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
		int result = levenshteinDistance(s1, s2);

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
		int result = levenshteinDistance(s1, s2);

		if(result == expected)
		{
			std::cout << "Success in the test: testLevenshteinDistance3\n";
			return true;
		}

		std::cout << "Fail in the test: testLevenshteinDistance3\n";
		return false;
	}

	bool testNeedlemanWunsch1()
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

	bool testNeedlemanWunsch2()
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

	bool testEuclideanDistance()
	{
		double vec1[] = {0, 3, 4, 5};
		double vec2[] = {7, 6, 3, -1};
		std::vector<double> v1, v2;

		for(int i = 0; i < 4; i++)
		{
			v1.push_back(vec1[i]);
			v2.push_back(vec2[i]);
		}

		double expected = 9.74679;
		double result = euclidean(v1, v2);

		if(almost_equals_double(result, expected))
		{
			std::cout << "Success in the test: testEuclideanDistance\n";
			return true;
		}

		std::cout << "Fail in the test: testEuclideanDistance\n";
		return false;
	}

	bool testDoubleEquals()
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

	bool testWhiteSimilarity1()
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

	bool testWhiteSimilarity2()
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
	
	bool testLcsDistance()
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
	
	bool testHammingDistance()
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
};

#endif
