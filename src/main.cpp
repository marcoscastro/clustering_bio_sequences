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

	gen.generateSequences(sequences, 5, 25, 50);

	/*
		Parameters in order:
			1) number of clusters
			2) total points
			3) total attributes
			4) max iterations
			5) sequences
			6) method for convert to a data point
			7) uses kmeans++ ?
	*/
	KMeans kmeans(2, sequences.size(), sequences.size(),
				  100, sequences, "NW", true);

	kmeans.run();

	return 0;
}
