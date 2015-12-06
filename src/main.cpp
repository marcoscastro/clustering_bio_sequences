#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "kmeans.h"
#include "tests.h"
#include "fasta_file.h"
#include "sequence_generator.h"

#define RUN_TESTS 0
#define RUN_TEST_SPLICE_DATA 0

void run_tests();
void run_algorithm();
void run_test_splice_data();

int main(int argc, char *argv[])
{
	clock_t begin = clock();

	srand(time(NULL));

	if(RUN_TESTS)
	{
		if(!RUN_TEST_SPLICE_DATA)
			run_tests();
		else
			run_test_splice_data();
	}
	else
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

	int amount_sequences = 100;

	gen.generateSequences(sequences, amount_sequences, 50, 100);

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
	int max_iter = 1000;
	std::string method("LCS");
	bool kmeansplusplus = true;
	bool hybrid = true;
	bool show_results = true;

	KMeans kmeans(clusters, sequences.size(), sequences.size(),
				  max_iter, sequences, method, kmeansplusplus,
				  hybrid, show_results);

	kmeans.run();
}

void run_test_splice_data()
{
	std::string dataset_name("splice.data.600.sequences.fasta");
	FastaFile ff(dataset_name);
	std::vector<std::pair<std::string, std::string> > dataset;

	dataset = ff.getSequences();

	std::vector<std::pair<std::string, std::string> >::iterator it;
	std::vector<std::string> sequences;

	for(it = dataset.begin(); it != dataset.end(); it++)
		sequences.push_back((*it).second);

	KMeans kmeans(3, sequences.size(), sequences.size(),
				  100, sequences, "NW", true, false, false);
	kmeans.run();

	std::vector<std::string> cluster1, cluster2, cluster3;

	// get sequences of each cluster
	kmeans.getClusterSequences(0, cluster1);
	kmeans.getClusterSequences(1, cluster2);
	kmeans.getClusterSequences(2, cluster3);

	int cluster1EI = 0, cluster1IE = 0, cluster1N = 0;

	for(unsigned int i = 0; i < cluster1.size(); i++)
	{
		std::string seq = cluster1[i];
		std::string class_seq;

		std::vector<std::pair<std::string, std::string> >::iterator it;

		for(it = dataset.begin(); it != dataset.end(); it++)
		{
			if((*it).second == seq)
			{
				class_seq = (*it).first;

				if(class_seq == "EI")
					cluster1EI++;
				else if(class_seq == "IE")
					cluster1IE++;
				else if(class_seq == "N")
					cluster1N++;
				break;
			}
		}
	}

	int cluster2EI = 0, cluster2IE = 0, cluster2N = 0;

	for(unsigned int i = 0; i < cluster2.size(); i++)
	{
		std::string seq = cluster2[i];
		std::string class_seq;

		std::vector<std::pair<std::string, std::string> >::iterator it;

		for(it = dataset.begin(); it != dataset.end(); it++)
		{
			if((*it).second == seq)
			{
				class_seq = (*it).first;

				if(class_seq == "EI")
					cluster2EI++;
				else if(class_seq == "IE")
					cluster2IE++;
				else if(class_seq == "N")
					cluster2N++;
				break;
			}
		}
	}

	int cluster3EI = 0, cluster3IE = 0, cluster3N = 0;

	for(unsigned int i = 0; i < cluster3.size(); i++)
	{
		std::string seq = cluster3[i];
		std::string class_seq;

		std::vector<std::pair<std::string, std::string> >::iterator it;

		for(it = dataset.begin(); it != dataset.end(); it++)
		{
			if((*it).second == seq)
			{
				class_seq = (*it).first;

				if(class_seq == "EI")
					cluster3EI++;
				else if(class_seq == "IE")
					cluster3IE++;
				else if(class_seq == "N")
					cluster3N++;
				break;
			}
		}
	}

	std::cout << "Cluster 1 - Size: " << cluster1.size() << "\n";
	std::cout << "\nClass EI: " << cluster1EI << " - " << ((double)cluster1EI / cluster1.size()) * 100.0 << "%\n";
	std::cout << "Class IE: " << cluster1IE << " - " << ((double)cluster1IE / cluster1.size()) * 100.0 << "%\n";
	std::cout << "Class N: " << cluster1N << " - " << ((double)cluster1N / cluster1.size()) * 100.0 << "%\n";

	std::cout << "\nCluster 2 - Size: " << cluster2.size() << "\n";
	std::cout << "\nClass EI: " << cluster2EI << " - " << ((double)cluster2EI / cluster2.size()) * 100.0 << "%\n";
	std::cout << "Class IE: " << cluster2IE << " - " << ((double)cluster2IE / cluster2.size()) * 100.0 << "%\n";
	std::cout << "Class N: " << cluster2N << " - " << ((double)cluster2N / cluster2.size()) * 100.0 << "%\n";

	std::cout << "\nCluster 3 - Size: " << cluster3.size() << "\n";
	std::cout << "\nClass EI: " << cluster3EI << " - " << ((double)cluster3EI / cluster3.size()) * 100.0 << "%\n";
	std::cout << "Class IE: " << cluster3IE << " - " << ((double)cluster3IE / cluster3.size()) * 100.0 << "%\n";
	std::cout << "Class N: " << cluster3N << " - " << ((double)cluster3N / cluster3.size()) * 100.0 << "%\n";
}
