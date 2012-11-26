
#ifndef __BOUNDARY_OP_BGL__
#define __BOUNDARY_OP_BGL__
//#define DEBUG
using namespace std;
#include "BoundaryOperator.h"
class BoundaryOperatorFactory{
private:

	Graph graph;
	VMap vertices;
	vector<int> *criticals;
	int size;
	Vertex at( int );
	int at( Vertex& );
	void addEdges( int , list<int> );
public:

	void clean();
	BoundaryOperatorFactory();
	virtual ~BoundaryOperatorFactory();
	void readFromFile( string path );
	void writeToFile( string path  , BoundaryOperator &op );
	BoundaryOperator getBoundary( Graph &g, vector<int> &criticals );
	BoundaryOperator getBoundary( );
};

#endif
