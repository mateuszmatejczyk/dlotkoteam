
#ifndef __BOUNDARY_OP_BGL__
#define __BOUNDARY_OP_BGL__
//#define DEBUG
using namespace std;
#include "BoundaryOperator.h"
class BoundaryOperatorFactory{
private:

	Graph graph;
	VMap vertices;
	vector< Vertex > criticals;
	int size;
	Vertex at( int );
	int at( Vertex& );
	void addEdges( int , list<int> );
	void setCriticals( vector<Vertex> &_criticals );
	void setCriticals( vector<int> &_criticals );
public:

	void setGraph( Graph& ,vector<Vertex> &_criticals );
	void setGraph( Graph& ,vector<int> &_criticals  );

	BoundaryOperatorFactory();
	virtual ~BoundaryOperatorFactory();
	void readFromFile( string path );
	void writeToFile( string path  , BoundaryOperator &op );
	BoundaryOperator getBoundary( Graph &g, vector<int> &criticals );
	BoundaryOperator getBoundary( );
};

#endif
