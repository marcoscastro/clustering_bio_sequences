#include <stdio.h>
#include <koolplot.h>
#include <map>
#include <string>
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
	std::vector<std::string> sequences, headers;
	std::map<int, double> SSE; // sum of squared errors
	std::vector<double> amount_clusters;
	int clusters, max_iterations, k_low, k_high;
	std::string method;
	bool kmeansplusplus, hybrid;

public:

	/*
		Parameters:
			sequences -> biological sequences
			k_low -> lower limit of the number of clusters
			k_upper -> upper limit of the number of clusters
	*/
	Elbow(int clusters, std::vector<std::string> & sequences,
		  std::vector<std::string> & headers, int max_iterations = 100,
		  std::string method = "LCS", bool kmeansplusplus = true,
		  bool hybrid = false, int k_low = 2, int k_high = 10);

	/*
		The elbow method is to run k-means clustering on the
		dataset for a range of values of "k", and for each value
		of "k" calculate the sum of squared errors (SSE)
	*/
	void run();
};
