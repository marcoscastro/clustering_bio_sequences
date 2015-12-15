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
	void runHybridSpliceDataTest900Sequences();
	void runNoHybridSpliceDataTest900Sequences();
	void runHybridTestsPromotersData();
	void runPromotersSpliceDataTest();
	void runNoHybridTestsPromotersData();
};

#endif
