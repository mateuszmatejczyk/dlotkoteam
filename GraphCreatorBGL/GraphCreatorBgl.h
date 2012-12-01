

#ifndef GRAPHCREATORBGL
#define GRAPHCREATORBGL

//============================================================================
// Name        : GraphCreator.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp> // for customizable graphs
#include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
#include <boost/graph/copy.hpp>
#include <utility>
using namespace std;

//	typedef boost::directed_graph<> Graph;
	typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS> Graph;
	typedef Graph::vertex_descriptor vertex;
	typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
	typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
	typedef boost::graph_traits<Graph>::out_edge_iterator out_edge_it;

class SympleksToGraphConvereter{
public :

	Graph g;
	map<list<int>,vertex >  sympleksMap;
	map<vertex, list<int> > inverseSympleksMap;
	vector<list<vertex> > vert;
	
	int V ;
	int E;
	int max_deg;

	void generateFacesAndConnect(list<int> & sympleks);
	void writeSympleks(list<int> & sympleks);
	SympleksToGraphConvereter();
	string sympleksToString(const list<int> & sympleks);	
	Graph::vertex_descriptor addSympleks(list<int> & sympleks);
	void staticistics();
	void readFromFile(string path);
	void getBoundry(list<int> & sympleks);
	/*
	* opis grafu V,E
	* a potem V linijek postaci (i-ta linijka od 0 ... V-1
	* n a1 a2 ... an takich ze isntieje krawedz z i -> ak , 1<=k <=n
	*
	*/
	void writeGraphToFileVertexNode(string path);
	void writeAllVerticesToFile(string path);
	/*
	* standardowy opis grafu tzn: V,E - wierzcholki krawedzie
	* i E krawedzi postaci
	* b c reprezentuj¹cych krawêd b -> c
	*
	*/
	void writeGraphToFileStandard(string path);	
	void writeLegend(string path);
	void copyGraph(Graph & ngraph);
};

#endif
