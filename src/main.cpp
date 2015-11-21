#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "tests.h"
#include "kmeans.h"

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(NULL));

	/*
	Tests tests;
	tests.runAllTests();
	*/

	SequenceGenerator gen;
	std::vector<std::string> sequences;

	// Generates 10 sequences of size between 10 e 20
	gen.generateSequences(sequences, 50, 10, 20);

	/*
		Parameters in order:
			number of clusters
			total points
			total attributes
			max iterations
			sequences
	*/
	KMeans kmeans(2, sequences.size(), sequences.size(), 100, sequences);

	kmeans.run();

	return 0;
}
