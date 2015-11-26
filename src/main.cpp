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

	gen.generateSequences(sequences, 200, 1, 50);

	/*
		Parameters in order:
			1) number of clusters
			2) total points
			3) total attributes
			4) max iterations
			5) sequences
			6) method for convert to a data point
			7) uses kmeans++ ?
			8) show results ?
	*/

	KMeans kmeans(10, sequences.size(), sequences.size(),
				  100, sequences, "NW", true, true);

	kmeans.run();

	return 0;
}
