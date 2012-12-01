#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<queue>
#include "GraphCreator.h"
using namespace std; 

#define DEBUG

void initUnmarked(SympleksToGraphConvereter & converter, set<pair<int,int> > & unmarked){
	for(int i = 0 ; i < converter.max_deg ; ++i){
		for(list<int>::iterator it = converter.vert[i].begin() ; it!= converter.vert[i].end() ; ++it){
			unmarked.insert(make_pair(i,*it));
		}
	}
}

void computeMorseMatching(SympleksToGraphConvereter & converter, vector<int> & critical, vector<pair<int,int> > & reversedEdges){
	set<pair<int,int> > unmarked;
	initUnmarked(converter, unmarked);
	while(!unmarked.empty()){
		set<pair<int,int> >::iterator crit = unmarked.begin();
		int minDeg =  crit->first;
		critical.push_back(crit->second);
		unmarked.erase(crit);
		bool found = true;
		cout << " unmarked : " << unmarked.size() << " sciagnalem " << converter.sympleksToString(
			converter.inverseSympleksMap[crit->second]) << endl;    
		while(found){
			found = false;
			bool remove_last = false;
			set<pair<int,int> >::iterator last_it;
			for(set<pair<int,int> >::iterator it = unmarked.upper_bound(make_pair(minDeg+1,-1));  it!= unmarked.end()  ; ++it){
				if(remove_last){
					unmarked.erase(last_it);
					remove_last= false;
				}
				
				int licznik = 0;
				list<int>::iterator possible ;
				int deg = it->first - 1;
				for(list<int>::iterator itboundry  = converter.edge[it->second].begin() ; 
						itboundry != converter.edge[it->second].end() ; ++itboundry){
					if(unmarked.find(make_pair(deg,*itboundry))!= unmarked.end()){
							possible = itboundry;
							++licznik;
							if(licznik  > 1)
								break;
					}
				}
				if (licznik == 1){ // super mamy jedyny unmatched element
					remove_last = true;
					last_it = it;
					unmarked.erase(make_pair(deg,*possible));
					
					#ifdef DEBUG	
						cout << "Odwracam : " << it->second << " " << *possible << endl;
					#endif
					// odwracanie krawedzi:
					converter.edge[it->second].erase(possible);
					converter.edge[*possible].push_back(it->second);
					
					found = true;
					
					reversedEdges.push_back(make_pair(it->second, *possible));
				}
				
			}
		}
	}
}

bool isAcyclic(vector<list<int> > & graph , vector<int> toporder){
	vector<int> deg(graph.size());
	int n = graph.size();
	for(vector<int>::iterator it = deg.begin() ; it!= deg.end() ; ++it)
		*it = 0;
	for(vector<list<int> >::iterator outerit = graph.begin() ; outerit != graph.end() ; ++outerit){
		for(list<int>::iterator innerit = outerit->begin() ; innerit!= outerit->end() ; ++innerit){
			++deg[*innerit];
		}
	}
	
	
	int m = 0;
	queue<int> q;
	int index = 0;
	for(vector<int>::iterator it = deg.begin() ; it!= deg.end(); ++it, ++index){
		if(*it == 0)
			q.push(index);
	}
	
	while(!q.empty()){
		
		int p = q.front(); q.pop(); ++m;
		toporder.push_back(p);
		for(list<int>::iterator it = graph[p].begin() ; it!=graph[p].end(); ++it){
			--deg[*it];
			if(deg[*it] == 0)
				q.push(*it);
		}
	}
	cout << n << " " << m;
	return n == m;
}


void testIsAcyclic(){
	// test cycle
	vector<list<int> > g;
	int n = 5;
	for(int i = 0 ; i < n ; ++i){
		list<int> s;
		s.push_back((i+1) % n);
		g.push_back(s);
	}
	vector<int> toporder;
	cout << " should say is 0 " << isAcyclic(g,toporder)  << endl;
	vector<list<int> > dag;
	for(int i = 0 ; i < n -1; ++i){
			list<int> s;
		s.push_back((i+1));
		dag.push_back(s);
	}
	list<int> s;
	dag.push_back(s);
	cout << " should say is 1 " << isAcyclic(dag,toporder) << endl;
}

int main(){
	SympleksToGraphConvereter stgc;
	stgc.readFromFile("/home/maciek/Informatyka/Programy/dane/poincare.dat");
	stgc.writeGraphToFileStandard("graph.txt");
	stgc.writeLegend("legend.txt");
	vector<int> toporder;
	cout << "read graph is acyclic " << isAcyclic(stgc.edge,toporder) << endl;
	vector<int> critical;
	vector<pair<int,int> > reveresedEdges;
	computeMorseMatching(stgc,critical,reveresedEdges);
	cout << " is acyclic " << isAcyclic(stgc.edge,toporder) << endl;
	cout << " Critical cells " << endl;
	for(vector<int>::iterator it = critical.begin() ; it!= critical.end() ; ++it){
		cout << *it << "    " << (stgc.sympleksToString(stgc.inverseSympleksMap[*it]))	 << endl;
	}

	
}
