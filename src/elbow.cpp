#include "elbow.h"

/*
	Parameters:
		sequences -> biological sequences
		k_low -> lower limit of the number of clusters
		k_upper -> upper limit of the number of clusters
*/
Elbow::Elbow(int clusters, std::vector<std::string> & sequences,
			 std::vector<std::string> & headers, int max_iterations,
			 std::string method, bool kmeansplusplus, bool hybrid, int k_low, int k_high)
{
	this->clusters = clusters;
	this->sequences = sequences;
	this->headers = headers;
	this->max_iterations = max_iterations;
	this->method = method;
	this->kmeansplusplus = kmeansplusplus;
	this->hybrid = hybrid;
	this->k_low = k_low;
	this->k_high = k_high;

	if(k_low < 0 || (k_high < k_low))
	{
		if(k_low < 0)
		{
			std::cerr << "\nError: lower limit (k_low) can not be a number negative.\n";
			exit(1);
		}

		if(k_high < k_low)
		{
			std::cerr << "\nError: upper limit (k_high) is smaller than lower limit (k_low).\n";
			exit(1);
		}
	}
}

/*
	The elbow method is to run k-means clustering on the
	dataset for a range of values of "k", and for each value
	of "k" calculate the sum of squared errors (SSE)
*/
void Elbow::run()
{
	int size_sequences = sequences.size();

	if(!size_sequences)
	{
		std::cerr << "\nError: the sequences set cannot be empty!\n";
		exit(1);
	}

	// initializes the SSE's of the clusters
	for(int i = k_low; i <= k_high; i++)
	{
		SSE[i] = 0;
		amount_clusters.push_back(i);
	}

	// for each value of "k" clusters
	for(int k = k_low; k <= k_high; k++)
	{
		KMeans kmeans(k, size_sequences, size_sequences, sequences,
					  headers, max_iterations, method, kmeansplusplus, hybrid, true);
		kmeans.run();

		// for each cluster
		for(int cluster = 0; cluster < k; cluster++)
		{
			int size_cluster = kmeans.getSizeCluster(cluster);

			// for each datapoint of the cluster
			for(int datapoint = 0; datapoint < size_cluster; datapoint++)
			{
				// for each value
				for(int value = 0; value < size_sequences; value++)
				{
					SSE[k] += pow(kmeans.getValuePoint(cluster, datapoint, value) -
								  kmeans.getCentralValue(cluster, value), 2.0);
				}
			}
		}
	}

	// plot the graph

	const char * header = "Elbow Method";
	char winTitle[50];

	std::vector<double> SSE_y;
	std::map<int, double>::iterator it;

	for(int k = k_low; k <= k_high; k++)
		SSE_y.push_back(SSE[k]);

	Plotdata x(amount_clusters), y(SSE_y);

	sprintf(winTitle, "%s", header);
	plot(x, y, winTitle);
}
