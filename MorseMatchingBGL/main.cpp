#include "GraphCreatorBgl.h"
#include <set>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/exception.hpp>
using namespace std;

//#define DEBUG

void init_set(SympleksToGraphConvereter & converter, set<pair<int, vertex> > & unmarked, map<vertex,int> degs){
	int n  = converter.vert.size();
	
	for(int i = 0 ; i < n ; ++i){
		for(list<vertex>::iterator it = converter.vert[i].begin(); it!= converter.vert[i].end() ; ++it){
			unmarked.insert(make_pair(i,*it));
			degs[*it] = i;
		}
	}
}

void morseMatching(SympleksToGraphConvereter & converter, vector<vertex> & critical){
	set<pair<int,vertex> > unmarked;
	map<vertex,int> degs;
	init_set(converter, unmarked, degs);
	IndexMap index = get(boost::vertex_index, converter.g);
	typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
	
	
	out_edge_it ei, ei_end, possible_edge;
	
	set<pair<int,vertex> >::iterator temp;
	set<pair<int,vertex> >::iterator possible;
	while(!unmarked.empty()){
		
		set<pair<int , vertex> >::iterator  crit = unmarked.begin();
		critical.push_back(crit->second);
		//cout << unmarked.size() << " " << " " << crit->second << endl;
		unmarked.erase(crit);
		int minDeg = crit->first;
		bool existPair = true;
		
		
		while(existPair){
			existPair = false;
			bool removeLast = false;
			set<pair<int,vertex> >::iterator  last;
			for(set<pair<int,vertex> >::iterator it = unmarked.upper_bound(make_pair(minDeg+1,-1));  it!= unmarked.end()  ; ++it){
					if(removeLast){
						unmarked.erase(last);
						removeLast = false;
					}
					int counter = 0;
					int currentDeg = it->first;
					
					for(boost::tie(ei,ei_end) = out_edges(it->second,converter.g) ; ei!= ei_end ; ++ei){
						vertex v = boost::target(*ei,converter.g);
						temp = unmarked.find(make_pair(currentDeg - 1, v));
						if(temp!=unmarked.end()){
							
							
							possible_edge = ei;
							++counter ;
							if(counter > 1){
								break;
							}
							possible = temp;
						}
						
					}
					
					if(counter == 1){ // hura udalo sie 
						#ifdef DEBUG
							cout << index[it->second] << " " << index[target(*ei,converter.g)] << endl; 
						#endif
						removeLast = true;
						last = it;
		
						
						unmarked.erase(possible);
						// odwracanie krawedzi
						//converter.g.remove_edge(possible_edge);
						remove_edge(possible_edge,converter.g);
						boost::add_edge(possible->second, it->second,converter.g);
						existPair = true;
						removeLast =true;
					}
			}
		}	
	}
	
}

bool isAcyclic(Graph g){
	try{
		typedef std::list<vertex> MakeOrder;
		MakeOrder make_order;
		boost::topological_sort(g, std::front_inserter(make_order));
		return true;
	}
	catch(boost::not_a_dag e){
		return false;
	}
}

int main(){
	SympleksToGraphConvereter stgc;
	stgc.readFromFile("/home/maciek/Informatyka/Programy/dane/poincare.dat");
	stgc.writeGraphToFileStandard("graph.txt");
	stgc.writeLegend("legend.txt");
	cout << "read graph is acyclic " << isAcyclic(stgc.g) << endl;
	vector<vertex> critical;
	morseMatching(stgc,critical);
	cout << " is acyclic " << isAcyclic(stgc.g) << endl;
	cout << " Critical cells " << endl;
	for(vector<vertex>::iterator it = critical.begin() ; it!= critical.end() ; ++it){
		cout << *it << "    " << (stgc.sympleksToString(stgc.inverseSympleksMap[*it]))	 << endl;
	}

}