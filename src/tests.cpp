#include <iostream>
#include <string>
#include "kmeans.h"
#include "tests.h"
#include "common.h"
#include "fasta_file.h"
#include "distance_strings.h"

void Tests::runAllTests()
{
	testLevenshteinDistance1();
	testLevenshteinDistance2();
	testLevenshteinDistance3();

	testNeedlemanWunsch1();
	testNeedlemanWunsch2();

	testDoubleEquals();

	testWhiteSimilarity1();
	testWhiteSimilarity2();

	testLcsDistance();

	testHammingDistance();

	testSmithWaterman();
}

bool Tests::testLevenshteinDistance1()
{
	std::string s1("AACTGG"), s2("ACTGGGG");
	double expected = 3;
	double result = levenshteinDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLevenshteinDistance1\n";
		return true;
	}

	std::cout << "Fail in the test: testLevenshteinDistance1\n";
	return false;
}

bool Tests::testLevenshteinDistance2()
{
	std::string s1("CCCCTGACACACTG"), s2("CTCTG");
	double expected = 9;
	double result = levenshteinDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLevenshteinDistance2\n";
		return true;
	}

	std::cout << "Fail in the test: testLevenshteinDistance2\n";
	return false;
}

bool Tests::testLevenshteinDistance3()
{
	std::string s1("A"), s2("C");
	double expected = 1;
	double result = levenshteinDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLevenshteinDistance3\n";
		return true;
	}

	std::cout << "Fail in the test: testLevenshteinDistance3\n";
	return false;
}

bool Tests::testNeedlemanWunsch1()
{
	std::string s1("AAAA"), s2("CCCC");
	int expected = 0;
	int result = nwDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testNeedlemanWunsch1\n";
		return true;
	}

	std::cout << "Fail in the test: testNeedlemanWunsch1\n";
	return false;
}

bool Tests::testNeedlemanWunsch2()
{
	std::string s1("GAATTCAGTTA"), s2("GGATCGA");
	int expected = 6;
	int result = nwDistance(s1, s2, 1, 0, 0);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testNeedlemanWunsch2\n";
		return true;
	}

	std::cout << "Fail in the test: testNeedlemanWunsch2\n";
	return false;
}

bool Tests::testDoubleEquals()
{
	double x = 0.333333, y = 0;

	if(almost_equals_double(x, y) == false)
	{
		std::cout << "Success in the test: testDoubleEquals\n";
		return true;
	}

	std::cout << "Fail in the test: testDoubleEquals\n";
	return false;
}

bool Tests::testWhiteSimilarity1()
{
	std::string s1("FRANCE"), s2("FRENCH");

	double expected = 40;
	double result = wsDistance(s1, s2, 2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testWhiteSimilarity1\n";
		return true;
	}

	std::cout << "Fail in the test: testWhiteSimilarity1\n";
	return false;
}

bool Tests::testWhiteSimilarity2()
{
	std::string s1("ACTG"), s2("GTCA");
	double expected = 0;
	double result = wsDistance(s1, s2, 2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testWhiteSimilarity2\n";
		return true;
	}

	std::cout << "Fail in the test: testWhiteSimilarity2\n";
	return false;
}

bool Tests::testLcsDistance()
{
	std::string s1("AGCAT"), s2("GAC");

	double expected = 4;
	double result = lcsDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testLcsDistance\n";
		return true;
	}

	std::cout << "Fail in the test: testLcsDistance\n";
	return false;
}

bool Tests::testHammingDistance()
{
	std::string s1("ACAGG"), s2("AGTGG");

	double expected = 3;
	double result = hammingDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testHammingDistance\n";
		return true;
	}

	std::cout << "Fail in the test: testHammingDistance\n";
	return false;
}

bool Tests::testSmithWaterman()
{
	std::string s1("CGAT"), s2("CGAT");
	double expected = 4;
	double result = swDistance(s1, s2);

	if(almost_equals_double(result, expected))
	{
		std::cout << "Success in the test: testSmithWaterman\n";
		return true;
	}

	std::cout << "Fail in the test: testSmithWaterman\n";
	return false;
}

void Tests::runSpliceDataTest()
{
	std::string dataset_name("splice.data.fasta");
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

	int accept = 0, total_tests = 100;

	for(int test = 0; test < total_tests; test++)
	{

		KMeans kmeans(3, sequences.size(), sequences.size(), sequences,
					  headers, 100, "HAMMING", true, false, false);
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

		double percent_cluster1_class1 = ((double)cluster1EI / cluster1.size()) * 100.0;
		double percent_cluster1_class2 = ((double)cluster1IE / cluster1.size()) * 100.0;
		double percent_cluster1_class3 = ((double)cluster1N / cluster1.size()) * 100.0;

		double percent_cluster2_class1 = ((double)cluster2EI / cluster2.size()) * 100.0;
		double percent_cluster2_class2 = ((double)cluster2IE / cluster2.size()) * 100.0;
		double percent_cluster2_class3 = ((double)cluster2N / cluster2.size()) * 100.0;

		double percent_cluster3_class1 = ((double)cluster3EI / cluster3.size()) * 100.0;
		double percent_cluster3_class2 = ((double)cluster3IE / cluster3.size()) * 100.0;
		double percent_cluster3_class3 = ((double)cluster3N / cluster3.size()) * 100.0;

		if(cluster1.size() >= 550 && cluster2.size() >= 550 && cluster3.size() >= 550)
		{
			if(percent_cluster1_class1 >= 79.9 || percent_cluster1_class2 >= 79.9 || percent_cluster1_class3 >= 79.9)
			{
				if(percent_cluster2_class1 >= 79.9 || percent_cluster2_class2 >= 79.9 || percent_cluster2_class3 >= 79.9)
				{
					if(percent_cluster3_class1 >= 79.9 || percent_cluster3_class2 >= 79.9 || percent_cluster3_class3 >= 79.9)
					{
						accept++;
					}
				}
			}
		}

		std::cout << "Cluster 1 - Size : " << cluster1.size() << "\n";
		std::cout << "\nClass EI : " << cluster1EI << " - " << ((double)cluster1EI / cluster1.size()) * 100.0 << " % \n";
		std::cout << "Class IE : " << cluster1IE << " - " << ((double)cluster1IE / cluster1.size()) * 100.0 << " % \n";
		std::cout << "Class N : " << cluster1N << " - " << ((double)cluster1N / cluster1.size()) * 100.0 << " % \n";

		std::cout << "\nCluster 2 - Size : " << cluster2.size() << "\n";
		std::cout << "\nClass EI : " << cluster2EI << " - " << ((double)cluster2EI / cluster2.size()) * 100.0 << " % \n";
		std::cout << "Class IE : " << cluster2IE << " - " << ((double)cluster2IE / cluster2.size()) * 100.0 << " % \n";
		std::cout << "Class N : " << cluster2N << " - " << ((double)cluster2N / cluster2.size()) * 100.0 << " % \n";

		std::cout << "\nCluster 3 - Size : " << cluster3.size() << "\n";
		std::cout << "\nClass EI : " << cluster3EI << " - " << ((double)cluster3EI / cluster3.size()) * 100.0 << " % \n";
		std::cout << "Class IE : " << cluster3IE << " - " << ((double)cluster3IE / cluster3.size()) * 100.0 << " % \n";
		std::cout << "Class N : " << cluster3N << " - " << ((double)cluster3N / cluster3.size()) * 100.0 << " % \n";

		std::cout << "\nClustering accept: " << accept << "\nIter: " << test + 1 << "\n\n";
	}

	std::cout << "\nClustering accept: " << accept << "\n";
}

void Tests::runPromotersDataTest()
{
	std::string dataset_name("promoters.data.fasta");
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

	int accept = 0, total_tests = 1;

	for(int test = 0; test < total_tests; test++)
	{
		KMeans kmeans(2, sequences.size(), sequences.size(), sequences,
					  headers, 100, "HAMMING", false, false, true);
		kmeans.run();

		std::vector<std::string> cluster1, cluster2;

		// get sequences of each cluster
		kmeans.getClusterSequences(0, cluster1);
		kmeans.getClusterSequences(1, cluster2);

		int cluster1_class1 = 0, cluster1_class2 = 0;

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

					if(class_seq == "+")
						cluster1_class1++;
					else if(class_seq == "-")
						cluster1_class2++;
					break;
				}
			}
		}

		int cluster2_class1 = 0, cluster2_class2 = 0;

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

					if(class_seq == "+")
						cluster2_class1++;
					else if(class_seq == "-")
						cluster2_class2++;
					break;
				}
			}
		}

		double percent_cluster1_class1 = ((double)cluster1_class1 / cluster1.size()) * 100.0;
		double percent_cluster1_class2 = ((double)cluster1_class2 / cluster1.size()) * 100.0;
		double percent_cluster2_class1 = ((double)cluster2_class1 / cluster2.size()) * 100.0;
		double percent_cluster2_class2 = ((double)cluster2_class2 / cluster2.size()) * 100.0;

		if(cluster1.size() >= 50 && cluster2.size() >= 50)
		{
			if(percent_cluster1_class1 >= 89.9 || percent_cluster1_class2 >= 89.9)
			{
				if(percent_cluster2_class1 >= 89.9 || percent_cluster2_class2 >= 89.9)
				{
					accept++;
				}
			}
		}

		std::cout << "Cluster 1 - Size : " << cluster1.size() << "\n";
		std::cout << "\nClass + : " << cluster1_class1 << " - " << ((double)cluster1_class1 / cluster1.size()) * 100.0 << " % \n";
		std::cout << "Class - : " << cluster1_class2 << " - " << ((double)cluster1_class2 / cluster1.size()) * 100.0 << " % \n";

		std::cout << "\nCluster 2 - Size : " << cluster2.size() << "\n";
		std::cout << "\nClass + : " << cluster2_class1 << " - " << ((double)cluster2_class1 / cluster2.size()) * 100.0 << " % \n";
		std::cout << "Class - : " << cluster2_class2 << " - " << ((double)cluster2_class2 / cluster2.size()) * 100.0 << " % \n";

		std::cout << "\nClustering accept: " << accept << "\nIter: " << test + 1 << "\n\n";
	}

	std::cout << "\nClustering accept: " << accept << "\n";
}
