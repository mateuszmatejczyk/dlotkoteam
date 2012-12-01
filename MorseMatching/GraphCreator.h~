#ifndef GRAPHCREATOR
#define GRAPHCREATOR

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

class SympleksToGraphConvereter{
public :
	map<list<int>,int >  sympleksMap;
	vector<list<int> > inverseSympleksMap;
	vector<list<int> > edge;
	vector<list<int> > vert;
	int V ;
	int E;
	int max_deg;

	void generateFacesAndConnect(list<int> & sympleks);
	void writeSympleks(list<int> & sympleks);
	
	// tu mozna jeszcze zbiory rozlaczne zaimplentowac

	SympleksToGraphConvereter();
	string sympleksToString(list<int> & sympleks);
	int addSympleks(list<int> & sympleks);
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
	/*
	* standardowy opis grafu tzn: V,E - wierzcholki krawedzie
	* i E krawedzi postaci
	* b c reprezentuj¹cych krawêd b -> c
	*
	*/
	void writeGraphToFileStandard(string path);
	void writeLegend(string path);
	void copyGraph(vector<list<int > > &ngraph);
};



#endif
