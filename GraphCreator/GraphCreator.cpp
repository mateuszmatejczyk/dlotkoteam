
#include "GraphCreator.h"


void SympleksToGraphConvereter::generateFacesAndConnect(list<int> & sympleks){
			if(sympleks.size() == 1)
				return;
			int cnumber = sympleksMap[sympleks];
			for(list<int>::iterator it = sympleks.begin() ; it!=sympleks.end() ; ++it){
				list<int> templist(sympleks); 
				templist.remove(*it);
				int tag = addSympleks(templist);
				if( edge.size() <= cnumber)
					edge.resize(cnumber + 1);
				edge[cnumber].push_back(tag);
				++E;
				
				
			}
}
void SympleksToGraphConvereter::writeSympleks(list<int> & sympleks){
		 cout << sympleks.size() << " : " ;
		for(list<int>::iterator it = sympleks.begin() ; it!= sympleks.end() ; ++it)
			cout << *it << " " ;
}
	
SympleksToGraphConvereter::SympleksToGraphConvereter() :V(0), E(0), max_deg(-1){}
	 
string SympleksToGraphConvereter::sympleksToString(list<int> & sympleks){
		
		stringstream ss(stringstream::in | stringstream::out);
		ss << sympleks.size() ;
		ss << " :";
		for(list<int>::iterator it = sympleks.begin() ; it!=sympleks.end() ; ++it){
			ss << " ";
			ss << *it;
		}
		return ss.str();
		
		
	 }
int SympleksToGraphConvereter::addSympleks(list<int> & sympleks){
		if (sympleksMap.find(sympleks) == sympleksMap.end()){
			int tag = sympleksMap[sympleks] = V;
			
			if( inverseSympleksMap.size() < (V +1) )
				inverseSympleksMap.resize(V+1);
			
			inverseSympleksMap[V] = sympleks;
			++V;
			if(V >= edge.size());
				edge.resize(V);
			 int t = (int) sympleks.size();
			 if(t > (int) vert.size())
				vert.resize(t);
			
			 vert[t-1].push_back(V-1);
			 if (max_deg < (t-1))
				max_deg = (t-1);
			generateFacesAndConnect(sympleks);
			
			return tag;

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
		int index = sympleksMap[sympleks];
		for(list<int>::iterator it = edge[index].begin() ; it!= edge[index].end() ; ++it){
			writeSympleks(inverseSympleksMap[*it]) ;
		cout << endl;
		}
	}
	/*
	* opis grafu V,E
	* a potem V linijek postaci (i-ta linijka od 0 ... V-1
	* n a1 a2 ... an takich ze isntieje krawedz z i -> ak , 1<=k <=n
	*
	*/
void SympleksToGraphConvereter::writeGraphToFileVertexNode(string path){
		
		ofstream myfile;
		myfile.open(path.c_str());
		myfile << V << " " << E << endl;
		for(int i = 0 ; i < V ; ++i){
			myfile << edge[i].size();
			for(list<int>::iterator it = edge[i].begin() ; it!= edge[i].end() ; ++it)
				myfile << " " << *it ;
			myfile << endl;
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
		for(int i = 0 ; i < V ; ++i){
			for(list<int>::iterator it = edge[i].begin() ; it!= edge[i].end() ; ++it)
				myfile << i <<" " << *it << endl;
		}
		myfile.close();
	}
	
void SympleksToGraphConvereter::writeLegend(string path){
		ofstream myfile;
		
		
		myfile.open(path.c_str());
		int i = 0;
		for(vector<list<int> >::iterator it = inverseSympleksMap.begin() ; it!= inverseSympleksMap.end() ; ++it, ++i){
			myfile << i << " ";
			//writeSympleks(*it);
			myfile << sympleksToString(*it);
			myfile << endl;
		}
		myfile.close();
}

void SympleksToGraphConvereter::copyGraph(vector<list<int> > & ngraph){
	ngraph = edge;
}



