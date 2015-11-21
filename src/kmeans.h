#ifndef _KMEANS_H_
#define _KMEANS_H_

class Point
{

private:
	int id_point, id_cluster;
	std::vector<double> values;
	std::string name;

public:
	Point(int id_point, std::vector<double> & values, std::string & name)
	{
		this->id_point = id_point;
		this->values = values;
		this->name = name;
		id_cluster = -1;
	}

	int getId()
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
};

class KMeans
{
public:
	KMeans()
	{
		
	}
};

#endif
