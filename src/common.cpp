#include <math.h>
#include "common.h"

bool almost_equals_double(double x, double y, double epsilon)
{
	return (fabs(x - y) < epsilon);
}