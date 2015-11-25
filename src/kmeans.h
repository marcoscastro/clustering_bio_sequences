#ifndef _KMEANS_H_
#define _KMEANS_H_
#include <map>
#include "distance_strings.h"

class Point
{

private:
	int id_point, id_cluster, total_values;
	std::vector<double> values;
	std::string name;

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
	bool kmeansplusplus, show_results;

private:

	void generatesPointsWithNW()
	{
		// calculates distances between all sequences

		for(int i = 0; i < total_points; i++)
		{
			std::vector<double> values;

			for(int j = 0; j < total_attributes; j++)
				values.push_back(needlemanWunsch(sequences[i], sequences[j]));

			Point point(i, values, sequences[i]);
			points.push_back(point);
		}
	}

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point & point)
	{
		double sum = 0.0, min_dist, dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_attributes; i++)
			sum += pow(clusters[0].getCentralValue(i) -
					   point.getValue(i), 2.0);

		min_dist = sqrt(sum);

		for(int i = 1; i < total_clusters; i++)
		{
			sum = 0.0;

			for(int j = 0; j < total_attributes; j++)
				sum += pow(clusters[i].getCentralValue(j) -
						   point.getValue(j), 2.0);

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
		   std::string method = "NW", bool kmeansplusplus = false,
		   bool show_results = true)
	{
		this->total_clusters = total_clusters;
		this->total_points = total_points;
		this->total_attributes = total_attributes;
		this->max_iterations = max_iterations;
		this->sequences = sequences;

		if(method == "NW")
			generatesPointsWithNW();

		this->kmeansplusplus = kmeansplusplus;
		this->show_results = show_results;
	}

	void run()
	{
		if(total_clusters > total_points)
		{
			std::cout << "Error: total clusters is the bigger than \
								total of points!\n";
			return;
		}

		if(!kmeansplusplus)
		{
			std::vector<int> prohibited_indexes;

			// choose total_clusters values for the centers of the clusters
			// this is slow, must be optimized
			for(int i = 0; i < total_clusters; i++)
			{
				while(true)
				{
					int point_index = rand() % total_points;

					if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
							point_index) == prohibited_indexes.end())
					{
						prohibited_indexes.push_back(point_index);
						points[point_index].setCluster(i);
						Cluster cluster(i, points[point_index]);
						clusters.push_back(cluster);
						break;
					}
				}
			}
		}
		else
		{
			// k-means++ initializer

			std::vector<double> probabilities(total_points);
			std::vector<bool> points_chosen(total_points);
			int cluster_index = 0;

			// take one center, chosen uniformly at random of data point
			int point_index = rand() % total_points;

			Cluster cluster(cluster_index, points[point_index]);

			clusters.push_back(cluster);
			points[point_index].setCluster(cluster_index);
			points_chosen[point_index] = true;
			cluster_index++;

			// until have taken total_centers altogether
			while(cluster_index < total_clusters)
			{
				// for each data point that still was not chosen
				for(int i = 0; i < total_points; i++)
				{
					if(!points_chosen[i])
					{
						/*
							for every data point calculate the minimum
							SSD to any of the stored cluster centers.
							Store these minimum distances, one per data
							point, in a vector.
							SSD = sum of difference squared (euclidean squared)
						*/
						for(int j = 0; j < cluster_index; j++)
						{
							double SSD = 0;

							for(int k = 0; k < total_attributes; k++)
								SSD += pow(points[i].getValue(k)
										   - clusters[j].getCentralValue(k), 2.0);

							if(j == 0)
								probabilities[i] = SSD;
							else if(SSD < probabilities[i])
								probabilities[i] = SSD;
						}
					}
				}

				/*
					convert the vector of probabilities to a discrete
					probability distribution(divide by the sum of the vector)
					use this probability distribution to weight the selection
					of the another data point as next cluster center

					ps.: a data point that has already been selected
					has 0 probability of being select again: its SSD
					to the nearest center is 0
				*/

				double sum_probs = 0;

				for(int i = 0; i < total_points; i++)
				{
					if(!points_chosen[i])
						sum_probs += probabilities[i];
				}

				std::map<int, std::vector<int> > tickets;
				int id_ticket = 1;

				for(int i = 0; i < total_points; i++)
				{
					if(!points_chosen[i])
					{
						// transform probabilitie
						probabilities[i] = (probabilities[i] / sum_probs) * 100;

						/*
							add +0.5 before casting to int because
							the compiler will always truncate
						*/
						probabilities[i] = probabilities[i] + 0.5;
						int amount_tickets = (int)probabilities[i];

						if(amount_tickets == 0)
							amount_tickets = 1;

						for(int j = 1; j <= amount_tickets; j++)
						{
							tickets[i].push_back(id_ticket);
							id_ticket++;
						}
					}
				}

				int choosen_ticket = rand() % (id_ticket - 1) + 1;

				std::map<int, std::vector<int> >::iterator it;
				for(it = tickets.begin(); it != tickets.end(); it++)
				{
					for(unsigned int i = 0; i < (it->second).size(); i++)
					{
						if((it->second)[i] == choosen_ticket)
						{
							point_index = it->first;
							break;
						}
					}
				}

				Cluster cluster(cluster_index, points[point_index]);

				clusters.push_back(cluster);
				points[point_index].setCluster(cluster_index);
				points_chosen[point_index] = true;
				probabilities[point_index] = 0;
				cluster_index++;
			}
		}

		int iter = 1;

		while(true)
		{
			//showClusters();

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

			/*
				hybrid clustering method based two techniques
				(harmonic mean and arithmetic mean) for
				recalculating the center of each cluster
			*/

			if(iter % 2 == 0)
			{
				/*
					recompute centers using harmonic mean

					harmonic mean inflates result for negative numbers
					because decrease the denominator, therefore harmonic
					mean makes absolutely no sense for negative numbers
				*/

				for(int i = 0; i < total_clusters; i++)
				{
					for(int j = 0; j < total_attributes; j++)
					{
						int total_points_cluster = clusters[i].getTotalPoints();
						double sum = 0;

						if(total_points_cluster > 0)
						{
							for(int p = 0; p < total_points_cluster; p++)
							{

								if((double_equals(clusters[i].getPoint(p).getValue(j), 0)) == false)
									sum += 1.0 / clusters[i].getPoint(p).getValue(j);
							}

							clusters[i].setCentralValue(j, ((double_equals(sum, 0) == true) ? 0 :
															total_points_cluster / sum));
						}
					}
				}
			}
			else
			{
				// recompute centers using arithmetic mean

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
			}

			if(done == true || iter >= max_iterations)
			{
				std::cout << "Break in iteration " << iter << "\n\n";
				if(show_results)
					showClusters();
				break;
			}

			iter++;
		}
	}
};

#endif
