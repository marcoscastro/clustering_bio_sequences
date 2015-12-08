#include <math.h>
#include "common.h"

bool almost_equals_double(double x, double y, double epsilon)
{
	return (fabs(x - y) < epsilon);
}

bool contains_number(std::string & s)
{
	int size_s = s.size();

	for(int i = 0; i < size_s; i++)
	{
		if(s[i] < '0' || s[i] > '9')
			return false;
	}

	return true;
}
