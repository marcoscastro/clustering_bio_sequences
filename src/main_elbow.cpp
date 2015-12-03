// reference: http://koolplot.codecutter.org/

#include <stdio.h>
#include <koolplot.h>
#include <vector>

using namespace std;

int main()
{
	const char * header = "Elbow Method";
	char winTitle[120];

	vector<double> v_x, v_y;

	v_x.push_back(2);
	v_x.push_back(3);
	v_x.push_back(4);
	v_x.push_back(5);
	v_x.push_back(6);

	v_y.push_back(0.4);
	v_y.push_back(0.6);
	v_y.push_back(0.8);
	v_y.push_back(0.82);
	v_y.push_back(0.83);

	Plotdata x(v_x), y(v_y);

	sprintf(winTitle, "%s", header);
	plot(x, y, winTitle);

	return 0;
}
