#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <string>
#include <map>

using namespace std;


set< list< pair< pair<int,int>,int > > > mySet;
vector< vector< pair< pair<int, int>, int> > > g;


void updateSetOfLists( list< pair< pair<int,int>,int > > newElements ) {
	
	set< list< pair< pair<int,int>,int > > > auxSet;
	list< pair< pair<int,int>,int > > auxList;
	
	if(newElements.size() > 0) {
		auxSet = mySet;
		mySet.clear();

		for(set< list< pair< pair<int,int>,int > > >::iterator it = auxSet.begin(); it != auxSet.end(); it++) {
			auxList = *it; 
			
			if(auxList.back().second == 1) {
				mySet.insert(auxList);
				continue;
			}
		
			for(list< pair< pair<int,int>,int > >::iterator it2 = newElements.begin(); it2 != newElements.end(); it2++) {
				int aux = auxList.back().second;
				for(int i = 0; i < g[aux].size(); i++) {
					if(g[aux][i].second == (*it2).second) {
						if(auxList.back().first.second != (*it2).first.second) {
							auxList.push_back(*it2);
							mySet.insert(auxList);
							auxList.pop_back();
						}
					}			
				}				
			}
		}	
	}		
	return;
}


int getMinW() {
	priority_queue< int, vector<int>, greater<int> > aux;
	list< pair< pair<int,int>,int > > auxList;
	int sum = 0;
	
	for(set< list< pair< pair<int,int>,int > > >::iterator it = mySet.begin(); it != mySet.end(); it++) {
		auxList = *it; sum = 0;
		if(auxList.back().second != 1)
			continue;
		for(list< pair< pair<int,int>,int > >::iterator it2 = auxList.begin(); it2 != auxList.end(); it2++)
			sum = sum + (*it2).first.first;
		aux.push(sum);
	}
	
	return aux.top();
}


int main() {

	int in;
	while( (cin >> in) && in != 0 ) {
		
		map<string, int> association;
		
		string start, end;
		cin >> start >> end;
		
		int index = 0;
		association[start] 	= index; index++;
		association[end] 	= index; index++;
		g.push_back( vector< pair< pair<int, int>, int> > () );			
		g.push_back( vector< pair< pair<int, int>, int> > () );
		
		string a, b, c;
		for(int i = 0; i < in; i++) {
			cin >> a >> b >> c;

			if(!association[a] && a != start) {	
				association[a] = index;
				index++;
				g.push_back( vector< pair< pair<int, int>, int> > () );							
			}
			if(!association[b] && b != start) {			
				association[b] = index;
				index++;
				g.push_back( vector< pair< pair<int, int>, int> > () );				
			}
			
			g[association[a]].push_back( make_pair( make_pair(c.size(), (int)c[0]), association[b]) );
			g[association[b]].push_back( make_pair( make_pair(c.size(), (int)c[0]), association[a]) );
		}

		//dijkstra	
		priority_queue< 		  pair< pair<int,int>,int >, 
						vector	< pair< pair<int,int>,int > >, 
						greater < pair< pair<int,int>,int > > 
					  > q;
					  
		vector<int> vis(association.size(), -1);
		pair< pair<int,int>, int> p;
		pair<int, int> w;
		int v;
		int end_node = association[end];

		q.push( make_pair( make_pair(0, -1), association[start]) );
		
		list< pair< pair<int,int>,int > > newElements;
		newElements.push_back( make_pair( make_pair(0, -1), association[start]) );
		mySet.insert( newElements ); newElements.clear();
		

		while(!q.empty()) {
			p = q.top(); 
			q.pop();

			v = p.second;
			w = p.first;

			if(vis[v] != -1) { 
				w.first = -1;
				continue;
			}
			if(v == end_node)
				break; 
			vis[v] = w.first;			
			
			int aa = g[v].size();
			for(int i = 0; i < aa; i++) {
				if( vis[ g[v][i].second ] == -1 ) {
					newElements.push_back( make_pair( make_pair(g[v][i].first.first, g[v][i].first.second), g[v][i].second) );
					q.push( make_pair( make_pair(w.first + g[v][i].first.first, g[v][i].first.second), g[v][i].second) );
				}
			}
			
			updateSetOfLists( newElements ); newElements.clear();
			w.first = -1;
		}	

		if(w.first != -1)
			cout << getMinW() << endl;
		else
			cout << "impossivel" << endl;
		
		mySet.clear();
		g.clear();
	}
	
	return 0;
}




