#ifndef __B__OP
#define __B__OP
#include "types.h"
class BoundaryException : public exception {
	char* message;
public:
	virtual const char* what() const throw(){
		return message;
	}
	BoundaryException setMessage( char* msg ){
		this->message = msg;
		return *this;
	}

};
class BoundaryOperator{
private:
	VMap vertices;
	Graph graph;
public:
	const Graph getGraph(){
		return this->graph;
	}
	Vertex getVertex( int i ){
		if( vertices.right.find( i ) == vertices.right.end() ){
			BoundaryException boundary_error;
			throw boundary_error.setMessage((char*)"Index out of bound!");
		}
		return vertices.right.at( i );
	}
	int getIndex( const Vertex& v ){
		if( vertices.left.find( v ) == vertices.left.end() ){
			BoundaryException boundary_error;
			throw boundary_error.setMessage((char*)"Vertex index out of bound!");
		}
		return vertices.left.at( v );
	}
	int get( int i, int j ){
		if( vertices.right.find( i ) == vertices.right.end() || vertices.right.find( j ) == vertices.right.end() ){
			//nie ma takich wierzcholkow w grafie, tzn. nie moga byc w swoim brzegu:)
			return 0;
		}
		Edge e;
		bool exists;
		tie( e, exists ) = boost::edge( vertices.right.at( i ), vertices.right.at( j ) , graph );
		if( exists ) return 1;
		else return 0;
	}
	int get( Vertex &u, Vertex &v ){
		bool exists;
		Edge e;
		tie( e, exists ) = boost::edge( u, v , graph );
		if( exists ) return 1;
		else return 0;
	}
	void set( int i, int j, int value ){
		Vertex v, u;

		if( vertices.right.find( i ) == vertices.right.end() ){
			v = add_vertex( graph );
			vertices.insert( VMap::value_type( v, i ) );
		}else{
			v = vertices.right.at( i );
		}
		if( vertices.right.find( j ) == vertices.right.end() ){
			u = add_vertex( graph );
			vertices.insert( VMap::value_type( u, j ) );
		}else{
			u = vertices.right.at( j );
		}
		Edge e;
		bool exists;
		tie( e, exists ) = boost::edge( v, u , graph );
		if( value > 0 && !exists ){
			add_edge( v, u , graph );
		}
		if( value <= 0 && exists ){
			remove_edge( v, u, graph );
		}

	}

};
#endif
