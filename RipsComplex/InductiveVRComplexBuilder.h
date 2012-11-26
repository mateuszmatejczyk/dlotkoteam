#pragma once
#include "ivrcomplexbuilder.h"

#include <boost\foreach.hpp>
#include <boost\tuple\tuple.hpp>

#include <map>


using namespace std;
using namespace boost;

class InductiveVRComplexBuilder :
	public IVRComplexBuilder
{
public:

	InductiveVRComplexBuilder(void)
	{
	}

	virtual ~InductiveVRComplexBuilder(void)
	{
	}


	virtual boost::shared_ptr< VRComplexGraph >  operator() ( const AdjacencyList& AList, unsigned  int k )
	{
		VRComplexGraph* G = new VRComplexGraph();
		_neighbours.resize(AList.size());
		
		//Add 0-simplexes - vertices
		for( unsigned int i=0;i<AList.size(); ++i )
			boost::add_vertex(Simplex(i), *G);



		graph_traits<VRComplexGraph>::vertex_iterator lastBegin, lastEnd, it;
		tuples::tie( lastBegin, lastEnd ) = vertices(*G);
		--lastEnd;


		for( unsigned int i=0;i<k;++i )
		{
			map< set<int>, VRComplexGraph::vertex_descriptor > simplexMap;

			cout << i << endl;
			for( it=lastBegin; it!= vertices(*G).second; ++it )
			{
				set<int> N;
				bool first=true;
				BOOST_FOREACH( int u, (*G)[*it].V )
					if( first )
					{
						N = neighbours(AList, u );
						first = false;
					}
					else
						intersection( N,neighbours(AList, u) );

				BOOST_FOREACH( int v, N )
				{
					set<int> V = (*G)[*it].V;
					V.insert(v);

					VRComplexGraph::vertex_descriptor vertex;
					if( simplexMap.count( V ) )
						vertex = simplexMap[V];
					else
					{
						double filtration = (*G)[*it].filtration;
						BOOST_FOREACH( const Edge& e, AList[v] )
							if( V.find(e.to) != V.end() &&  filtration < e.w )
								filtration = e.w;
						vertex = simplexMap[V] = add_vertex(Simplex(V, filtration), *G);
					}

					
					add_edge( vertex, *it, *G);
				}

				if( it==lastEnd )
				{
					lastBegin = ++lastEnd;
					lastEnd = vertices(*G).second;
					--lastEnd;
					break;
				}

			}
		}
		deleteNeighbours();
		return boost::shared_ptr< VRComplexGraph > (G);
	}



private:



	vector< set< int >* > _neighbours;

	void deleteNeighbours()
	{
		BOOST_FOREACH( set<int>* s, _lowerNeighbours )
			delete s;
	}

	
	struct EdgeToVertex
	{
		int operator()( const Edge& E )
		{
			return E.to;
		}
	}op;

	set<int>& neighbours( const AdjacencyList& AList, int v )
	{
		if( _neighbours[v] == 0 )
		{
			_neighbours[v] = new set<int> ();
			transform( AList[v].begin(), AList[v].end(), std::inserter(*_neighbours[v], _neighbours[v]->begin()), op );
		}
		return *_neighbours[v];
	}


	vector< set< int >* > _lowerNeighbours;

	void deleteLowerNeighbours()
	{
		BOOST_FOREACH( set<int>* s, _lowerNeighbours )
			delete s;
	}

	set<int>& lowerNeighbours( const AdjacencyList& AList, int v )
	{
		if( _lowerNeighbours[v] == 0 )
		{
			_lowerNeighbours[v] = new set<int> ();
			BOOST_FOREACH( const Edge& e, AList[v] )
				if( e.to >= v )
					break;
				else
					_lowerNeighbours[v]->insert(e.to);
		}
		return *_lowerNeighbours[v];
	}

	set<int>& intersection( set<int>& S, const set<int>& T )
	{
		std::set<int>::iterator s = S.begin();
		std::set<int>::const_iterator t = T.begin();
		while ( s != S.end() && t != T.end() ) 
			if (*s < *t)
				S.erase(s++);
			else if (*t < *s)
				++t;
			else 
			{ // *s == *t
				++s;
				++t;
			}

		S.erase(s, S.end());
		return S;
	}

};

