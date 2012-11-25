#pragma once

#include "NeighbourhoodGraph.h"


#include <boost/graph/adjacency_list.hpp>
#include <boost/smart_ptr.hpp>
#include <set>

struct Simplex
{
	double filtration;
	std::set< int > V;

	Simplex(int vertex)
		: filtration(0)
	{
		V.insert(vertex);
	}

	//usefull for edges
	Simplex( const set<int>& V, double filtration )
		:V(V), filtration(filtration)
	{
	}
};

typedef boost::adjacency_list<
	boost::vecS, boost::listS, boost::directedS,
	Simplex>
  VRComplexGraph;


class IVRComplexBuilder
{
public:

	virtual ~IVRComplexBuilder(void)
	{
	}

	virtual boost::shared_ptr< VRComplexGraph >  operator() ( const AdjacencyList& AList, unsigned int k )=0;
};
