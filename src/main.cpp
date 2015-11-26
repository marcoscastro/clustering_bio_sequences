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

	gen.generateSequences(sequences, 100, 50, 100);

	/*
		Parameters in order:
			1) number of clusters
			2) total points
			3) total attributes
			4) max iterations
			5) sequences
			6) method for convert to a data point
			7) uses kmeans++ ?
			8) uses hybrid (mean function + harmonic mean) ?
			9) show results ?
	*/

	string method("WS");
	bool kmeansplusplus = true;
	bool hybrid = true;
	bool show_results = true;

	KMeans kmeans(5, sequences.size(), sequences.size(),
				  100, sequences, method, kmeansplusplus,
				  hybrid, show_results);

	kmeans.run();

	return 0;
}
