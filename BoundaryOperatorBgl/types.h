#ifndef B_OP_TYPES
#define B_OP_TYPES
#include "includes.h"

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS > Graph;
typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;
//typedef boost::multi_array<Vertex, 2>  BoundaryOperator;
typedef boost::multi_array< Vertex, 2> PathsCounter;

typedef boost::property_map<Graph, boost::vertex_index_t>::type VertexIndexMap;
typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
typedef boost::graph_traits<Graph>::edge_iterator edge_iter;
typedef boost::graph_traits<Graph>::adjacency_iterator adj_iter;
typedef boost::bimap< Vertex , int > VMap;
#endif
