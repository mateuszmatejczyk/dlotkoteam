#pragma once


class NeighbourhoodGraphBuilder
{
public:

	NeighbourhoodGraphBuilder(void)
	{
	}

	~NeighbourhoodGraphBuilder(void)
	{
	}

	template <typename T>
	virtual vector< vector<Edge> > operator() ( T Parser, Distance& dist )=0;
};

