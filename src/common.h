#ifndef _COMMON_H_
#define _COMMON_H_

bool almost_equals(double x, double y, double epsilon = 0.001)
{
	return (fabs(x - y) < epsilon);
}

#endif
