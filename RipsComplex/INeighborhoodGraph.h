#pragma once

#include "IDistance.h"

#include <vector>
#include <boost/smart_ptr.hpp>

using namespace std;



typedef vector < vector < Edge > > AdjencyList;


class INeighborhoodGraph
{
public:

	INeighborhoodGraph(void)
	{
	}

	~INeighborhoodGraph(void)
	{
	}


	virtual boost::shared_ptr< AdjencyList > getAdjencyList( const vector< vector<double> >& points, double e, IDistance& dist ) = 0;
};

