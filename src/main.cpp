/*
	Clustering of Biological Sequences

	This is a Open-Source Project
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "kmeans.h"
#include "tests.h"
#include "fasta_file.h"
#include "sequence_generator.h"
#include "common.h"

#define RUN_TESTS 0
#define RUN_TEST_SPLICE_DATA 0
#define RUN_TEST_PROMOTERS_DATA 0

void run_algorithm(int clusters, std::string & fasta_file,
				   int max_iter = 100, const std::string & method = "LCS",
				   bool kmeansplusplus = true, bool hybrid = false, bool odin = false);

int main(int argc, char *argv[])
{
	srand(time(NULL));

	if(RUN_TESTS || RUN_TEST_SPLICE_DATA || RUN_TEST_PROMOTERS_DATA)
	{
		Tests tests;

		if(RUN_TESTS)
			tests.runAllTests();
		if(RUN_TEST_SPLICE_DATA)
			tests.runSpliceDataTest();
		else if(RUN_TEST_PROMOTERS_DATA)
			tests.runPromotersDataTest();
	}
	else
	{
		std::string instructions;

		// checks the number of arguments
		if(argc > 1)
		{
			std::string number_clusters(argv[1]);

			if(number_clusters == "help")
			{
				instructions = "\nTwo parameters are required: number of clusters and fasta file.\
								\n\nCommand example 1:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file>\
								\n\n\tmy_executable 3 my_file.fasta\
								\n\nOptional parameters:\
								\n\n\t[max_iterations] -> maximum of iterations, default is 100.\
								\n\n\t[comparison_method] -> method to compare strings, default is LCS.\
								\n\n\t\tMethods available:\
								\n\n\t\tED -> edit distance (levenshtein distance)\
								\n\n\t\tNW -> Needleman-Wunsch (optimal global alignment)\
								\n\n\t\tSW -> Smith-Waterman (optimal local alignment)\
								\n\n\t\tWS -> White-Similarity or Dice's Coefficient (similarity ranking)\
								\n\n\t\tLCS -> Longest Common Subsequence\
								\n\n\t\tHAMMING -> Hamming distance (only for strings of equal length)\
								\n\nCommand example 2:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method]\
								\n\n\tmy_executable 3 my_file.fasta 50 NW\
								\n\nObservation: KMeans++ is used for default.\
								\n\nYou do not want to use the KMeans++? Try this for example:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method] [uses_kmeansplusplus]\
								\n\n\tmy_executable 3 my_file_fasta 50 NW 0\
								\n\n\tmy_executable 3 my_file_fasta 50 NW 1\
								\n\nThe number 0 indicates that you not will use KMeans++.\
								\nThe number 1 indicates that KMeans++ will be used.\
								\n\nYou want to use the hybrid clustering? Try this:\
								\n\n\tmy_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method] [uses_kmeansplusplus] [uses_hybrid]\
							   	\n\n\tmy_executable 3 my_file.fasta 50 NW 0 1\
							   	\n\n\tExplanation:\
								\n\t\t3 -> number of clusters\
								\n\t\t50 -> maximum iterations\
								\n\t\t0 -> Dont uses KMeans++\
								\n\t\t1 -> Uses the hybrid clustering\
								\n\nTo use ODIN (outliers detection):\
								\n\n\tmy_executable <number_of_clusters> <fasta_file> [max_iterations] [comparison_method] [uses_kmeansplusplus] [uses_hybrid] [uses_odin]\
								\n\tmy_executable 3 my_file.fasta 50 NW 0 1 1\
								\n\nInstructions for use of Elbow Method\n\
								\nElbow method try find out the best number of clusters. Compile the project with main_elbow.cpp.\
								\nThe implementation of the Elbow method requires the external library koolplot.\n\
							   ";

				std::cout << instructions;
			}
			else
			{
				if(contains_number(number_clusters) == true)
				{
					int n_clusters = atoi(number_clusters.c_str());

					if(argc > 2)
					{
						std::string fasta_file(argv[2]);

						if(argc > 3)
						{
							std::string max_iterarions(argv[3]);

							if(contains_number(max_iterarions) == true)
							{
								int max_iter = atoi(max_iterarions.c_str());

								if(argc > 4)
								{
									std::string method(argv[4]);

									if(method != "NW" && method != "WS" &&
											method != "LCS" && method != "HAMMING" &&
											method != "ED" && method != "SW")
										std::cout << "\nError: method not found.\n";
									else
									{
										if(argc > 5)
										{
											std::string kmeansplusplus(argv[5]);
											bool flag_kmeansplusplus = true;

											if(kmeansplusplus == "0")
												flag_kmeansplusplus = false;

											if(argc > 6)
											{
												std::string hybrid(argv[6]);
												bool flag_hybrid = false;

												if(hybrid == "1")
													flag_hybrid = true;

												if(argc > 7)
												{
													std::string odin(argv[7]);
													bool flag_odin = false;

													if(odin == "1")
														flag_odin = true;

													run_algorithm(n_clusters, fasta_file, max_iter,
																  method, flag_kmeansplusplus, flag_hybrid, flag_odin);
												}
												else
													run_algorithm(n_clusters, fasta_file, max_iter,
																  method, flag_kmeansplusplus, flag_hybrid);
											}
											else
												run_algorithm(n_clusters, fasta_file,
															  max_iter, method, flag_kmeansplusplus);
										}
										else
											run_algorithm(n_clusters, fasta_file, max_iter, method);
									}
								}
								else
									run_algorithm(n_clusters, fasta_file, max_iter);
							}
							else
								std::cout << "\nError: max iterations is a positive integer.\n";
						}
						else
							run_algorithm(n_clusters, fasta_file);
					}
					else
						std::cout << "\nError: fasta file not found.\n";

				}
				else
					std::cout << "\nError: number of clusters is a positive integer.\n";
			}
		}
		else
		{
			instructions = "\nInsufficient arguments. Dont panic...\
		\n\nExample of a basic command: \
											\n\n\texecutable_name <number_of_clusters> <fasta_file>\
											\n\n\tmy_executable 3 my_file.fasta\
											\n\nWant more options ? Execute the command : executable_name help\n";

			std::cout << instructions;
		}
	}

	return 0;
}

void run_algorithm(int clusters, std::string & fasta_file, int max_iter,
				   const std::string & method, bool kmeansplusplus, bool hybrid, bool odin)
{
	std::string dataset_name(fasta_file);
	FastaFile ff(dataset_name);
	std::vector<std::pair<std::string, std::string> > dataset;

	dataset = ff.getSequences();

	std::vector<std::pair<std::string, std::string> >::iterator it;
	std::vector<std::string> sequences, headers;

	for(it = dataset.begin(); it != dataset.end(); it++)
	{
		headers.push_back((*it).first);
		sequences.push_back((*it).second);
	}

	/*
	Parameters in order:
	1) number of clusters
	2) total points
	3) total attributes
	4) sequences
	5) max iterations
	6) method for convert to a data point
	7) uses kmeans++ ?
	8) uses hybrid (mean function + harmonic mean) ?
	*/

	KMeans kmeans(clusters, sequences.size(), sequences.size(), sequences,
				  headers, max_iter, method, kmeansplusplus, hybrid, odin);

	kmeans.run();
}
