#ifndef _TESTS_H_
#define _TESTS_H_
#include "distance_strings.h"
#include "distance_points.h"
#include "sequence_generator.h"
#include "common.h"
#include "read_fasta.h"

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
		testFastaFile();
		testDoubleEquals();

		testWhiteSimilarity1();
		testWhiteSimilarity2();
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
		int result = needlemanWunsch(s1, s2);

		if(almost_equals(result, expected))
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
		int result = needlemanWunsch(s1, s2, 1, 0, 0);

		if(almost_equals(result, expected))
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

		if(almost_equals(result, expected))
		{
			std::cout << "Success in the test: testEuclideanDistance\n";
			return true;
		}

		std::cout << "Fail in the test: testEuclideanDistance\n";
		return false;
	}

	void testFastaFile()
	{
		FastaFile fasta_file("test.fasta");

		fasta_file.showSequences();
	}

	bool testDoubleEquals()
	{
		double x = 0.333333, y = 0;

		if(almost_equals(x, y) == false)
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
		double result = whiteSimilarity(s1, s2);

		if(almost_equals(result, expected))
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
		double result = whiteSimilarity(s1, s2);
		
		std::cout << "similarity: " << result << "\n";
		
		if(almost_equals(result, expected))
		{
			std::cout << "Success in the test: testWhiteSimilarity2\n";
			return true;
		}

		std::cout << "Fail in the test: testWhiteSimilarity2\n";
		return false;
	}
};

#endif
