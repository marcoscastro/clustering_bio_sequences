#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tests.h"
#include "kmeans.h"

using namespace std;

void run_tests();
void run_algorithm();

int main(int argc, char *argv[])
{
	srand(time(NULL));

	//run_tests();

	clock_t begin = clock();

	run_algorithm();

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "\nTime: " << elapsed_secs << " seconds.\n";

	return 0;
}

void run_tests()
{
	Tests tests;
	tests.runAllTests();
}

void run_algorithm()
{
	SequenceGenerator gen;
	std::vector<std::string> sequences;

	int amount_sequences = 50;

	gen.generateSequences(sequences, amount_sequences, 1000, 1500);

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

	int clusters = sqrt(sequences.size() / 2);
	int max_iter = 100;
	string method("KMP");
	bool kmeansplusplus = true;
	bool hybrid = true;
	bool show_results = true;

	KMeans kmeans(clusters, sequences.size(), sequences.size(),
				  max_iter, sequences, method, kmeansplusplus,
				  hybrid, show_results);

	kmeans.run();
}
