#include <cmath>
#include <vector>

using namespace std;

#define M_PI       3.14159265358979323846
typedef pair<double,double> Point;


vector<Point> getCirclePointCloud(int points)
{
	vector<Point> vec(points);
	for( int i=0;i<points;++i )
		vec[i] = make_pair( sin(2*M_PI*i/points),cos(2*M_PI*i/points));
	return vec;
}

vector<Point> getEightPointCloud(int points)
{
	vector<Point> vec(2*points);
	for( int i=0;i<points;++i )
	{
		double	x=sin(2*M_PI*i/points),
				y=cos(2*M_PI*i/points);
		vec[i] = make_pair(x,y);
		vec[2*points+i] = make_pair(x+2,y);
	}
	return vec;
}