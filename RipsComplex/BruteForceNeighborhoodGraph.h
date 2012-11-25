#pragma once

#include "Distance.h"
#include "FileParser.h"
#include "NeighbourhoodGraph.h"


class BruteForceNeighborhoodGraph
{
	typedef unsigned int uint;
public:

	template<typename T>
	boost::shared_ptr< AdjacencyList > operator()( ifstream& stream, T parser, double e, Distance& dist )
	{
		typedef typename T::Point Point;
		typedef typename vector< T::Point > Points;

		FileParser fp;
		boost::shared_ptr< Points > points = fp.parse<Point, T>(stream, parser);

		cout	<< "File has been parsed successfully" << endl
				<< "Building Neighbourhood Graph..." << endl;

		AdjacencyList* V = new AdjacencyList( points->size() );
		for( uint i=1;i<V->size();++i )
		{
			cout << (double)(i*100)/(double)V->size() << endl;
			for( uint j=0;j<i;++j )
			{
				double d = dist( (*points)[i],(*points)[j]);
				if( d<=e )
				{
					(*V)[i].push_back( Edge(d,j) );
					(*V)[j].push_back( Edge(d,i) );
				}
			}
		}

		cout << "Done..." << endl;
		return boost::shared_ptr<AdjacencyList> (V);
	}

};

