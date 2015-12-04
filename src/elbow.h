#include <stdio.h>
#include <koolplot.h>
#include "kmeans.h"

/*
	Elbow method is used to get a hint about the number of clusters.

	The method: compute the sum of squared error (SSE) for some
	values of "k" (number os clusters). The SSE is defined as the
	sum of the squared distance between each member of the cluster
	and its centroid.

	The goal is plot "k" against the SSE, then you will see the error
	decreases as "k" gets larger; this is because when the number of
	clusters increasesm they should be smaller, so distortion is also smaller.
	The idea of the elbow method is to choose the "k" at which the SSE
	decreases abruptly. This produces an "elbow effect" in the graph.

	References for the Elbow method:
		https://www.quora.com/How-can-we-choose-a-good-K-for-K-means-clustering
		https://gist.github.com/rpgove/0060ff3b656618e9136b
*/
class Elbow
{

private:
	std::vector<std::string> sequences;
	std::map<int, double> SSE; // sum of squared errors
	std::vector<double> amount_clusters;
	int k_low, k_high, max_iterations;
	std::string method;
	bool kmeansplusplus, hybrid, show_results;

public:

	/*
		Parameters:
			sequences -> biological sequences
			k_low -> lower limit of the number of clusters
			k_upper -> upper limit of the number of clusters
	*/
	Elbow(std::vector<std::string> & sequences, std::string method,
		  int k_low = 1, int k_high = 10, int max_iterations = 100,
		  bool kmeansplusplus = true, bool hybrid = false, bool show_results = false)
	{
		this->sequences = sequences;
		this->method = method;
		this->k_low = k_low;
		this->k_high = k_high;
		this->max_iterations = max_iterations;
		this->kmeansplusplus = kmeansplusplus;
		this->hybrid = hybrid;
		this->show_results = show_results;

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
	void run()
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
			KMeans kmeans(k, size_sequences, size_sequences, max_iterations,
						  sequences, method, kmeansplusplus, hybrid, show_results);
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
};
