
#include "GraphCreatorBgl.h"


void SympleksToGraphConvereter::generateFacesAndConnect(list<int> & sympleks){
			if(sympleks.size() == 1)
				return;
			Graph::vertex_descriptor cnumber = sympleksMap[sympleks];
			for(list<int>::iterator it = sympleks.begin() ; it!=sympleks.end() ; ++it){
				list<int> templist(sympleks); 
				templist.remove(*it);
				Graph::vertex_descriptor tag = addSympleks(templist);
				boost::add_edge(cnumber,tag,g);
				++E;
			}
		}
void SympleksToGraphConvereter::writeSympleks(list<int> & sympleks){
		 cout << sympleks.size() << " : " ;
		for(list<int>::iterator it = sympleks.begin() ; it!= sympleks.end() ; ++it)
			cout << *it << " " ;
	 }

SympleksToGraphConvereter::SympleksToGraphConvereter() :V(0), E(0), max_deg(-1){}
	 
string SympleksToGraphConvereter::sympleksToString(const list<int> & sympleks){
		
		stringstream ss(stringstream::in | stringstream::out);
		ss << sympleks.size() ;
		ss << " :";
		for(list<int>::const_iterator it = sympleks.begin() ; it!=sympleks.end() ; ++it){
			ss << " ";
			ss << *it;
		}
		return ss.str();
		
		
}
Graph::vertex_descriptor SympleksToGraphConvereter::addSympleks(list<int> & sympleks){
		if (sympleksMap.find(sympleks) == sympleksMap.end()){
			vertex v = boost::add_vertex(g);
			//vertex v = g.add_vertex();
			sympleksMap[sympleks] = v;
			inverseSympleksMap[v] = sympleks;
			++V;
			 int t = (int) sympleks.size();
			 if(t > (int) vert.size())
				vert.resize(t);
			 vert[t-1].push_back(v);
			 if (max_deg < (t-1))
				max_deg = (t-1);
			generateFacesAndConnect(sympleks);
			
			return v;

		}
		return sympleksMap[sympleks];
	}
void SympleksToGraphConvereter::staticistics(){
		cout << "Number of vertixes " << V<< endl;
		cout << "Number of edges " << E << endl;
		cout << "Max degree is " << max_deg << endl;
		for(int i = 0 ; i <= max_deg ;++i){	
			cout << "Vertixes of dimension " << i << " is " << vert[i].size() << endl;
		}
		cout << "Finieshed statistics" << endl;
	}


void SympleksToGraphConvereter::readFromFile(string path){

	      ifstream myfile(path.c_str());
	      if(myfile.is_open()){
	    	  string mstring;

	    	  while(myfile.good()){
	    		  getline(myfile,mstring);

	    		  if(mstring[0] == '#')
	    			  continue;
	    		  stringstream ss(mstring);
	    		  list<int> sympleks;
	    		  int temp;
	    		  while( ss  >> temp){
	    			  sympleks.push_back(temp);	
	    		  }
				  sympleks.sort();
				  if(sympleks.size() < 1)
					continue;
	    		  addSympleks(sympleks);
	    	  }
	    	  myfile.close();
	      }

	}

void SympleksToGraphConvereter::getBoundry(list<int> & sympleks){
		Graph::vertex_descriptor number = sympleksMap[sympleks];
		
		
		//typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
		//IndexMap index = get(boost::vertex_index, g);
		typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
 
		std::pair<adjacency_iterator, adjacency_iterator> neighbors =
			boost::adjacent_vertices(number, g);
 
		for(; neighbors.first != neighbors.second; ++neighbors.first)
		{
			
			cout << sympleksToString(inverseSympleksMap[*neighbors.first]) << endl;
		}
	}
	/*
	* opis grafu V,E
	* a potem V dwu-linijek postaci  
	* (vertex_number
	* n : a1 a2 ... an takich ze isntieje krawedz z i -> ak , 1<=k <=n)
	*
	*/
void SympleksToGraphConvereter::writeGraphToFileVertexNode(string path){
		
		ofstream myfile;
		myfile.open(path.c_str());
		myfile << V << " " << E << endl;
		IndexMap index = get(boost::vertex_index, g);
		typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
		std::pair<vertex_iter, vertex_iter> vp;
		out_edge_it ei,ei_end;
		for (vp = vertices(g); vp.first != vp.second; ++vp.first);{
			cout << index[*(vp.first)] << endl;
			cout << boost::out_degree(*(vp.first),g) << " : " ;
			for(boost::tie(ei,ei_end) = out_edges(*(vp.first),g) ; ei!= ei_end ; ++ei)
				cout << index[boost::target(*ei,g)] << " ";
		}
			
	
		myfile.close();
	}
	
	void SympleksToGraphConvereter::writeAllVerticesToFile(string path){
		ofstream myfile;
		myfile.open(path.c_str());;
		IndexMap index = get(boost::vertex_index, g);
		
		std::pair<vertex_iter, vertex_iter> vp;
		for (vp = vertices(g); vp.first != vp.second; ++vp.first){
			myfile << index[*vp.first] ;;
			
			myfile << std::endl;
		 }
		 myfile.close();
	}
	/*
	* standardowy opis grafu tzn: V,E - wierzcholki krawedzie
	* i E krawedzi postaci
	* b c reprezentuj¹cych krawêd b -> c
	*
	*/
void SympleksToGraphConvereter::writeGraphToFileStandard(string path){
		ofstream myfile;
		myfile.open(path.c_str());
		myfile << V << " " << E << endl;
		boost::graph_traits<Graph>::edge_iterator ei, ei_end;
	    IndexMap index = get(boost::vertex_index, g);
		for(boost::tie(ei,ei_end) = edges(g); ei!= ei_end; ++ei){
			myfile << index[source(*ei,g)] << " " << index[target(*ei,g)] << endl;
		}
		myfile.close();
	}
	
void SympleksToGraphConvereter::writeLegend(string path){
		ofstream myfile;
		myfile.open(path.c_str());
		 IndexMap index = get(boost::vertex_index, g);
		for(map<list<int>, Graph::vertex_descriptor >:: iterator it = sympleksMap.begin() ; it!= sympleksMap.end() ; ++it)
			myfile << sympleksToString(it->first) << " : " << index[it->second] << endl;
		myfile.close();
}

void SympleksToGraphConvereter::copyGraph(Graph & ngraph){
	boost::copy_graph(g,ngraph);
}




