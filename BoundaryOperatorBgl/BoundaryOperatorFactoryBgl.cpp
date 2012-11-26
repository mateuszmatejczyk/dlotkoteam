#include "BoundaryOperatorFactoryBgl.h"
using namespace std;
void BoundaryOperatorFactory::clean(){
	if( this->criticals != NULL ){
		delete this->criticals;

	}
	this->criticals = new vector<int>();
}
BoundaryOperatorFactory::BoundaryOperatorFactory(){
	this->criticals = NULL;
}
BoundaryOperatorFactory::~BoundaryOperatorFactory(){
	if( this->criticals != NULL ){
		delete this->criticals;
	}

}
int BoundaryOperatorFactory::at( Vertex& v){
	return this->vertices.left.at( v );
}

Vertex BoundaryOperatorFactory::at( int  v){
	return this->vertices.right.at( v );
}
void BoundaryOperatorFactory::readFromFile( string path ){

	this->clean();

	ifstream myfile( path.c_str() );
	if( myfile.is_open() ){
		string mstring;
		int tmp;
		if( myfile.good() ){
			getline( myfile, mstring );
			stringstream ss( mstring );
			while( ss >> tmp ){

				this->criticals->push_back( tmp );
			}
	  }
	  getline( myfile, mstring );
	  stringstream ss( mstring );
	  int nvertices;
	  ss >> nvertices;
	  this->size = nvertices;
	  for( int i  = 0 ; i < nvertices; i++ ){
		  Graph::vertex_descriptor v = boost::add_vertex( this->graph );
		  this->vertices.insert( VMap::value_type( v , i ) );
	  }


	  for( int v_number = 0; v_number < nvertices && myfile.good(); v_number++ ){
		  getline( myfile , mstring );
		  stringstream ss( mstring );
		  if( mstring[0] == '%') continue;
		  list<int> edges;
		  while( ss >> tmp ){

			  edges.push_back( tmp );
		  }

		  this->addEdges( v_number, edges );

	  }

	  myfile.close();
	}
}

void BoundaryOperatorFactory::writeToFile( string path , BoundaryOperator &op ){
	ofstream myfile;
	myfile.open( path.c_str() );
	const Graph g = op.getGraph();
	edge_iter e, e_end;
	tie( e, e_end ) = boost::edges( g );
	while( e != e_end ){
		Vertex v = boost::source( *e, g ) ;
		Vertex u = boost::target( *e, g );
		#ifdef DEBUG
			cout<< op.getIndex( v ) << "-->" << op.getIndex( u ) << endl;
		#endif
		myfile<< op.getIndex( v ) << "-->" << op.getIndex( u ) << endl;

		e++;
	}

	myfile.close();
}
BoundaryOperator BoundaryOperatorFactory::getBoundary(  ){
	return this->getBoundary( this->graph, *this->criticals );
}

/*
 * BoundaryOperator => boost::multi_array<Vertex, 2>
 */
BoundaryOperator BoundaryOperatorFactory::getBoundary( Graph &g, vector<int> &_criticals ){
	vector< Vertex > criticals;


	BOOST_FOREACH( int v, _criticals ){
		criticals.push_back( this->at( v ) );
	}
	#ifdef DEBUG
		cout<<"Criticals:\n";
		BOOST_FOREACH( Vertex c, criticals ){
			cout<< this->at( c ) <<" ";
		}
		cout<<"\n===========================\n";
	#endif
	BoundaryOperator op;
	PathsCounter pc( boost::extents[this->size][this->size] );
	vector< Vertex > ordered;


	topological_sort( this->graph , back_inserter( ordered ) );
	reverse( ordered.begin() , ordered.end() );
	#ifdef DEBUG
	 cout<<"Topsort:\n";
	 BOOST_FOREACH( Vertex v, ordered ){
		 cout<< this->at( v )<<" ";
	 }
	 cout<<"\n===========================\n";
    #endif

	BOOST_FOREACH( Vertex s , criticals ){

		BOOST_FOREACH( Vertex v , ordered ){
			pc[ this->at( s ) ][ this->at( v ) ] = 0;
		}
		pc[ this->at( s ) ][ this->at( s ) ] = 1;

		for( vector< Vertex>::iterator c = ( find( ordered.begin(), ordered.end(), s ) ); c != ordered.end(); ++c ){

			if( find( criticals.begin() , criticals.end() , *c ) != criticals.end() && *c != s ){
				op.set( this->at( s ), this->at( *c ), pc[ this->at( s ) ][ this->at( *c ) ] % 2 );
				#ifdef DEBUG
					cout<< "Boundary( " << this->at( s ) << " , " << this->at( *c ) << " ) := P( " << this->at( s ) << " , " << this->at( *c ) << " ) % 2\n";
					cout<< "Boundary( " << this->at( s ) << " , " << this->at( *c ) << " ) := " << pc[ this->at( s ) ][ this->at( *c ) ] % 2 <<endl;
				#endif
			}else{
				adj_iter v, v_end;
				tie( v, v_end ) = boost::adjacent_vertices( *c , this->graph );
				while( v != v_end ){
					#ifdef DEBUG
						int p = pc[ this->at( s ) ][ this->at( *v ) ] ;
					#endif
					pc[ this->at( s ) ][ this->at( *v ) ] += pc[ this->at( s ) ][ this->at( *c ) ];
					#ifdef DEBUG
						cout<< "P( " << this->at( s ) << " , " << this->at( *v ) << " ) += "
								<< "P( "<< this->at( s )<< " , " <<  this->at( *c ) << " )"  <<endl;
						cout<< "P( " << this->at( s ) << " , " << this->at( *v ) << " ) := " <<p << " + " <<
								pc[ this->at( s ) ][ this->at( *c ) ] <<endl;

					#endif
					++v;
				}

			}
		}
	}

	return op;
}

void  BoundaryOperatorFactory::addEdges( int v_number , list<int> edges ){

	Vertex v = this->vertices.right.at( v_number );
	for( list<int>::iterator i = edges.begin(); i != edges.end(); ++i){
		Vertex u = this->vertices.right.at( *i );
		boost::add_edge( v, u, this->graph );
		#ifdef DEBUG
			cout<< this->vertices.left.at( v ) << "-->" << this->vertices.left.at( u ) <<endl ;
		#endif
	}

}


