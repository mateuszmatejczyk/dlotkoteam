#pragma once


#include <vector>

using namespace std;


struct Edge
{
	double w;
	int to;

	Edge( double w, int to )
		: w(w), to(to)
	{}
};


typedef vector< vector<Edge> > AdjacencyList;

