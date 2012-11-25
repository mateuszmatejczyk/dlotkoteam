#pragma once

#include <vector>

using namespace std;

class PointsDimensionTest
{
public:

	PointsDimensionTest(void)
	{
	}

	virtual ~PointsDimensionTest(void)
	{
	}

	bool operator()( const vector< vector<double> >& P )
	{
		int previous=-1;
		for( vector< vector<double> >::const_iterator it=P.begin(); it!=P.end(); ++it )
			if( previous==-1 )
				previous = it->size();
			else if( previous != it->size() )
				return false;
		return true;
	}
};

