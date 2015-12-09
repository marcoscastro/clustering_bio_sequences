#ifndef _TESTS_H_
#define _TESTS_H_

class Tests
{
public:
	void runAllTests();
	bool testLevenshteinDistance1();
	bool testLevenshteinDistance2();
	bool testLevenshteinDistance3();
	bool testNeedlemanWunsch1();
	bool testNeedlemanWunsch2();
	bool testDoubleEquals();
	bool testWhiteSimilarity1();
	bool testWhiteSimilarity2();
	bool testLcsDistance();
	bool testHammingDistance();
	bool testSmithWaterman();
	void runSpliceDataTest();
	void runPromotersDataTest();
};

#endif
