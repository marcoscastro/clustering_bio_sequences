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
public:
	Elbow()
	{
		
	}
	
	void run()
	{
		
	}
};