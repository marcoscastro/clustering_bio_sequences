#ifndef _KMEANS_H_
#define _KMEANS_H_

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
public:
	KMeans()
	{

	}
};

#endif
