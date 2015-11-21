#ifndef _COMMON_H_
#define _COMMON_H_

bool double_equals(double x, double y, double epsilon = 0.001)
{
	return (abs(x - y) < epsilon);
}

#endif
