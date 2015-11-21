#ifndef _TESTS_H_
#define _TESTS_H_
#include "distance_strings.h"
#include "distance_points.h"
#include "common.h"
#include "sequence_generator.h"

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
		testSequenceGenerator();
	}

	bool testLevenshteinDistance1()
	{
		std::string s1("AACTGG"), s2("ACTGGGG");
		int expected = 3;

		DistanceStrings dist(s1, s2);
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

		DistanceStrings dist(s1, s2);
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

		DistanceStrings dist(s1, s2);
		int result = dist.levenshteinDistance();

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
		std::string s1("GCATGCU"), s2("GATTACA");
		int expected = 0;

		DistanceStrings dist(s1, s2);
		int result = dist.needlemanWunsch();

		if(result == expected)
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

		DistanceStrings dist(s1, s2);
		int result = dist.needlemanWunsch(1, 0, 0);

		if(result == expected)
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

		if(double_equals(result, expected))
		{
			std::cout << "Success in the test: testEuclideanDistance\n";
			return true;
		}

		std::cout << "Fail in the test: testEuclideanDistance\n";
		return false;
	}

	void testSequenceGenerator()
	{
		SequenceGenerator gen;
		std::vector<std::string> sequences;

		gen.generateSequences(sequences, 2, 1000, 10000);
		std::string s1(sequences[0]), s2(sequences[1]);
		DistanceStrings dist(s1, s2);

		std::cout << "\nRunning testSequenceGenerator...\n";
		std::cout << "Score: " << dist.needlemanWunsch() << "\n";
		std::cout << "Finished testSequenceGenerator!\n";
	}
};

#endif
