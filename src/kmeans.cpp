#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <sstream>
#include "kmeans.h"
#include "common.h"
#include "distance_strings.h"

Point::Point(int id_point, std::vector<double> & values, std::string & name, std::string & header)
{
	this->id_point = id_point;
	this->values = values;
	this->header = header;
	this->name = name;
	id_cluster = -1;
	total_values = values.size();
}

int Point::getID()
{
	return id_point;
}

int Point::getCluster()
{
	return id_cluster;
}

void Point::setCluster(int id_cluster)
{
	this->id_cluster = id_cluster;
}

double Point::getValue(int index)
{
	return values[index];
}

std::string & Point::getName()
{
	return name;
}

std::string & Point::getHeader()
{
	return header;
}

int Point::getTotalValues()
{
	return total_values;
}

Cluster::Cluster(int id_cluster, Point & point)
{
	this->id_cluster = id_cluster;
	int total_values = point.getTotalValues();

	for(int i = 0; i < total_values; i++)
		central_values.push_back(point.getValue(i));

	points.push_back(point);
}

void Cluster::addPoint(Point & point)
{
	points.push_back(point);
}

bool Cluster::removePoint(int id_point)
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

double Cluster::getCentralValue(int index)
{
	return central_values[index];
}

void Cluster::setCentralValue(int index, double value)
{
	central_values[index] = value;
}

Point Cluster::getPoint(int index)
{
	return points[index];
}

int Cluster::getTotalPoints()
{
	return points.size();
}

int Cluster::getID()
{
	return id_cluster;
}


void KMeans::generatesPoints(std::string & method)
{
	// calculates distances between all sequences

	std::map<std::pair<int, int>, double> table;
	int value_method = 0;

	if(method == "NW")
		value_method = 1;
	else if(method == "WS")
		value_method = 2;
	else if(method == "LCS")
		value_method = 3;
	else if(method == "HAMMING")
		value_method = 4;
	else if(method == "ED")
		value_method = 5;
	else if(method == "SW")
		value_method = 6;

	if(value_method != 0)
	{
		std::vector<double> values;
		double result;

		for(int i = 0; i < total_points; i++)
		{
			for(int j = 0; j < total_attributes; j++)
			{
				if(i > j) // checks has been calculated
					values.push_back(table[std::make_pair(j, i)]);
				else
				{
					if(value_method == 1)
						// uses needleman-wunsch (global alignment)
						result = nwDistance(sequences[i], sequences[j]);
					else if(value_method == 2)
						// uses simon white similarity
						result = wsDistance(sequences[i], sequences[j]);
					else if(value_method == 3)
						// uses LCS (longest common subsequence)
						result = lcsDistance(sequences[i], sequences[j]);
					else if(value_method == 4)
						// uses the hamming distance
						result = hammingDistance(sequences[i], sequences[j]);
					else if(value_method == 5)
						// uses edit distance
						result = levenshteinDistance(sequences[i], sequences[j]);
					else if(value_method == 6)
						// uses smith-waterman (local alignment)
						result = swDistance(sequences[i], sequences[j]);

					values.push_back(result);

					// memorization
					table[std::make_pair(i, j)] = result;
				}
			}

			Point point(i, values, sequences[i], headers[i]);
			points.push_back(point);

			values.clear();
		}
	}
	else
	{
		std::cerr << "\nError: method \"" << method << "\" not found.\n";
		std::cerr << "\nAvailable methods:\n\n";
		std::cerr << "\tNW - needleman-wunsch (global alignment)\n";
		std::cerr << "\tWS - white similarity (similarity ranking)\n";
		std::cerr << "\tLCS - longest common subsequence\n";
		std::cerr << "\tHamming - the hamming distance\n";
		std::cerr << "\tEdit distance - Levenshtein distance\n";
		exit(1);
	}
}

// return ID of nearest center (uses euclidean distance)
int KMeans::getIDNearestCenter(Point & point)
{
	double sum = 0, min_dist, dist;
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

void KMeans::generateResults()
{
	std::string filename_report("report.txt");
	std::ostringstream break_iter, time_elapsed;
	std::string report_content = "";

	break_iter << iter;
	time_elapsed << elapsed_secs;

	report_content += "Break in iteration " + break_iter.str() + "\n";
	report_content += "Time elapsed: " + time_elapsed.str() + " seconds\n";

	if(odin) // outliers
	{
		std::ostringstream stream_outliers, stream_knn;

		stream_outliers << total_outliers;
		stream_knn << knn;

		report_content += "\nODIN (outlier detection)";
		report_content += "\nTotal outliers: " + stream_outliers.str();
		report_content += "\nkNN = " + stream_knn.str() + "\n";
	}

	for(unsigned int i = 0; i < clusters.size(); i++)
	{
		int total_points_cluster = clusters[i].getTotalPoints();
		std::string filename = "cluster";
		std::string content = "";
		std::ostringstream idx_cluster, total_points;

		idx_cluster << (i + 1);
		total_points << total_points_cluster;
		filename += idx_cluster.str() + ".txt";

		report_content += "\nCluster " + idx_cluster.str();
		report_content += "\nAmount sequences: " + total_points.str() + "\n";

		for(int j = 0; j < total_points_cluster; j++)
			content += ">" + clusters[i].getPoint(j).getHeader() + "\n" +
					   clusters[i].getPoint(j).getName() + "\n";

		generateFile(filename, content);
	}

	generateFile(filename_report, report_content);
}

KMeans::KMeans(int total_clusters, int total_points, int total_attributes,
			   std::vector<std::string> & sequences,  std::vector<std::string> & headers,
			   int max_iterations, std::string method, bool kmeansplusplus, bool hybrid,
			   bool elbow, bool odin, double odin_threshold, int knn)
{
	t_begin = clock();

	this->total_clusters = total_clusters;
	this->total_points = total_points;
	this->total_attributes = total_attributes;
	this->sequences = sequences;
	this->headers = headers;
	this->max_iterations = max_iterations;
	this->method = method;
	this->kmeansplusplus = kmeansplusplus;
	this->hybrid = hybrid;
	this->elbow = elbow;
	this->odin = odin;
	this->odin_threshold = odin_threshold;

	generatesPoints(method);

	if(odin) // checks if uses outlier detection
	{
		// knn = K nearest neighbors
		if(knn > 0)
			this->knn = knn;
		else
			this->knn = 0.01 * this->total_points;

		total_outliers = 0;

		/*
			Implementation of the ODIN method
			ODIN = Outlier Detection using Indegree Number
			ODIN is a kNN outlier method, uses kNN graph
		*/

		std::vector<std::vector<int> > list_adjacency(total_points);

		// for each point
		for(int point = 0; point < this->total_points; point++)
		{
			// build the list of distances of the neighbors of the point
			std::vector<double> dists_neighbors;

			for(int neighbor = 0; neighbor < this->total_points; neighbor++)
			{
				if(point != neighbor)
					dists_neighbors.push_back(points[point].getValue(neighbor));
			}

			// get K smallest distance from point to other objects from dataset
			std::sort(dists_neighbors.begin(), dists_neighbors.end());
			double K_smallest_dist = dists_neighbors[this->knn - 1];

			// who are the K nearest neighbors?
			for(int neighbor = 0; neighbor < this->total_points; neighbor++)
			{
				if(point != neighbor)
				{
					if(points[point].getValue(neighbor) <= K_smallest_dist)
						list_adjacency[point].push_back(neighbor);
				}
			}
		}

		std::vector<int> in_degree(total_points);

		for(int point = 0; point < this->total_points; point++)
		{
			// search for point in the lists of adjacency of the others points
			for(int other_point = 0; other_point < this->total_points; other_point++)
			{
				if(point != other_point)
				{
					std::vector<int>::iterator it;

					for(it = list_adjacency[other_point].begin();
							it != list_adjacency[other_point].end(); it++)
					{
						// checks if point is in list adjacency of other_point
						if(point == *it)
							in_degree[point]++; // adds in degree of point
					}
				}
			}
		}

		double outly;

		// checks in-degree number
		for(int point = 0; point < this->total_points; point++)
		{
			// calculates outlyingess of point
			outly = 1.0 / (in_degree[point] + 1.0);

			// checks if point is a outlier comparing outly with threshold
			if(outly > odin_threshold)
			{
				total_outliers++;
				outliers_points.push_back(point);
			}
		}

		// remove outlies of the sequences vector
		for(int i = 0; i < total_outliers; i++)
			this->sequences.erase(this->sequences.begin() + outliers_points[i]);

		// update variables
		this->total_points = this->total_attributes = this->sequences.size();

		// clear points
		points.clear();

		// generates again the points
		generatesPoints(method);
	}
}

// get sequences of the cluster
void KMeans::getClusterSequences(int index_cluster, std::vector<std::string> & sequences)
{
	int total_points = clusters[index_cluster].getTotalPoints();

	for(int i = 0; i < total_points; i++)
		sequences.push_back(clusters[index_cluster].getPoint(i).getName());
}

// returns the central value of a certain cluster
double KMeans::getCentralValue(int index_cluster, int index_central_value)
{
	return clusters[index_cluster].getCentralValue(index_central_value);
}

// returns the value of datapoint of a certain cluster
double KMeans::getValuePoint(int index_cluster, int index_point, int index_value)
{
	return clusters[index_cluster].getPoint(index_point).getValue(index_value);
}

// returns the amount of datapoints of a certain cluster
int KMeans::getSizeCluster(int index_cluster)
{
	return clusters[index_cluster].getTotalPoints();
}

// runs the k means algorithm
void KMeans::run()
{
	if(total_clusters > total_points)
	{
		std::cerr << "\nError: total clusters is bigger than total of data points!\n";
		exit(1);
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
					// transforms for probability
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

			/*
				problem kmeans++ with WS method:
				parameter window: very similar strings
			*/
			if(id_ticket == 1 && method == "WS")
			{
				std::cerr << "\nError in kmeans++ with WS method.\n";
				std::cerr << "Try to change the optional parameter \"window\" in the whiteSimilarity function.\n";
				exit(1);
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

	iter = 1;

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

		/*
			hybrid clustering method based two techniques
			(harmonic mean and arithmetic mean) for
			recalculating the center of each cluster
		*/

		if(hybrid && (iter % 2 == 0))
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
							if((almost_equals_double(clusters[i].getPoint(p).getValue(j), 0)) == false)
								sum += 1.0 / clusters[i].getPoint(p).getValue(j);
						}

						clusters[i].setCentralValue(j, ((almost_equals_double(sum, 0) == true) ? 0 :
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
			break;

		iter++;
	}

	t_end = clock();

	elapsed_secs = double(t_end - t_begin) / CLOCKS_PER_SEC;

	if(elbow == false)
		generateResults();
}
