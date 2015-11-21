#ifndef _KMEANS_H_
#define _KMEANS_H_
#include "distance_strings.h"

class Point
{

private:
	int id_point, id_cluster;
	std::vector<double> values;
	std::string name;
	int total_values;

public:
	Point(int id_point, std::vector<double> & values, std::string & name)
	{
		this->id_point = id_point;
		this->values = values;
		this->name = name;
		id_cluster = -1;
		total_values = values.size();
	}

	int getID()
	{
		return id_point;
	}

	int getCluster()
	{
		return id_cluster;
	}

	void setCluster(int id_cluster)
	{
		this->id_cluster = id_cluster;
	}

	double getValue(int index)
	{
		return values[index];
	}

	std::string getName()
	{
		return name;
	}

	int getTotalValues()
	{
		return total_values;
	}
};


class Cluster
{

private:
	int id_cluster;
	std::vector<double> central_values;
	std::vector<Point> points;

public:
	Cluster(int id_cluster, Point & point)
	{
		this->id_cluster = id_cluster;
		int total_values = point.getTotalValues();

		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i));

		points.push_back(point);
	}

	void addPoint(Point & point)
	{
		points.push_back(point);
	}

	bool removePoint(int id_point)
	{
		int total_points = points.size();

		for(int i = 0; i < total_points; i++)
		{
			if(points[i].getID() == id_point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}

		return false;
	}

	double getCentralValue(int index)
	{
		return central_values[index];
	}

	void setCentralValue(int index, double value)
	{
		central_values[index] = value;
	}

	Point getPoint(int index)
	{
		return points[index];
	}

	int getTotalPoints()
	{
		return points.size();
	}

	int getID()
	{
		return id_cluster;
	}
};


class KMeans
{

private:
	int total_clusters, total_points;
	int total_attributes, max_iterations;
	std::vector<Cluster> clusters;
	std::vector<Point> points;
	std::vector<std::string> sequences;

private:

	void generatesPointsWithNW()
	{
		// calculates distances between all sequences

		for(int i = 0; i < total_points; i++)
		{
			std::vector<double> values;

			for(int j = 0; j < total_attributes; j++)
			{
				DistanceStrings dist(sequences[i], sequences[j]);
				values.push_back(dist.needlemanWunsch());
			}

			Point point(i, values, sequences[i]);
			points.push_back(point);
		}
	}

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point & point)
	{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_attributes; i++)
		{
			sum += pow(clusters[0].getCentralValue(i) -
					   point.getValue(i), 2.0);
		}

		min_dist = sqrt(sum);

		for(int i = 1; i < total_clusters; i++)
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < total_attributes; j++)
			{
				sum += pow(clusters[i].getCentralValue(j) -
						   point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist;
				id_cluster_center = i;
			}
		}

		return id_cluster_center;
	}

	void showClusters()
	{
		for(unsigned int i = 0; i < clusters.size(); i++)
		{
			int total_points_cluster = clusters[i].getTotalPoints();

			std::cout << "Cluster " << i + 1 << "\n";

			for(int j = 0; j < total_points_cluster; j++)
				std::cout << clusters[i].getPoint(j).getName() << "\n";
			std::cout << "\n";
		}
	}

public:
	KMeans(int total_clusters, int total_points, int total_attributes,
		   int max_iterations, std::vector<std::string> & sequences,
		   std::string method = "NW")
	{
		this->total_clusters = total_clusters;
		this->total_points = total_points;
		this->total_attributes = total_attributes;
		this->max_iterations = max_iterations;
		this->sequences = sequences;

		if(method == "NW")
			generatesPointsWithNW();
	}

	void run()
	{
		if(total_clusters > total_points)
		{
			std::cout << "Error: total clusters is the bigger than \
								total of points!\n";
			return;
		}

		std::vector<int> prohibited_indexes;

		// choose total_clusters values for the centers of the clusters
		// this is slow, must be optimized
		for(int i = 0; i < total_clusters; i++)
		{
			while(true)
			{
				int index_point = rand() % total_points;

				if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
						index_point) == prohibited_indexes.end())
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}

		int iter = 1;

		while(true)
		{
			bool done = true;

			// associates each point to the nearest center
			for(int i = 0; i < total_points; i++)
			{
				int id_old_cluster = points[i].getCluster();
				int id_nearest_center = getIDNearestCenter(points[i]);

				if(id_old_cluster != id_nearest_center)
				{
					if(id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID());

					points[i].setCluster(id_nearest_center);
					clusters[id_nearest_center].addPoint(points[i]);
					done = false;
				}
			}

			// recalculating the center of each cluster
			for(int i = 0; i < total_clusters; i++)
			{
				for(int j = 0; j < total_attributes; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if(total_points_cluster > 0)
					{
						for(int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster);
					}
				}
			}

			if(done == true || iter >= max_iterations)
			{
				std::cout << "Break in iteration " << iter << "\n\n";
				showClusters();
				break;
			}

			iter++;
		}
	}
};

#endif
