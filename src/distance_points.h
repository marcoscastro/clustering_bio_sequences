#ifndef _DISTANCE_POINTS_H_
#define _DISTANCE_POINTS_H_

/*
	Euclidean distance

	Reference:
		https://en.wikipedia.org/wiki/Euclidean_distance

	Parameters:
		vectors of coordinates (points in Euclidean n-space)

	Return:
		euclidean distance
*/
double euclidean(std::vector<double> & v1, std::vector<double> & v2)
{
	int size_v = v1.size();
	double sum = 0;

	for(int i = 0; i < size_v; i++)
		sum += pow(v1[i] - v2[i], 2);

	return sqrt(sum);
}

#endif
