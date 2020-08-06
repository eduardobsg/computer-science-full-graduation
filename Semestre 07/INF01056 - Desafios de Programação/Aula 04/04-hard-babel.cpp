#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <string>
#include <map>

using namespace std;

/* Esta variável guarda um conjunto de listas, onde cada lista é um caminho solução.
Após ter chegado de 'start' a 'end' esse set é analisado para vermos qual o menor dos caminhos.
Observação: o último elementos de cada lista dentro do set é da forma ((w total, letra), nodo),
logo basta acessar cada lista do set, pegando o último elemento de cada lista:

list.back.first.first => w total

É só ir testando os W total, pegando o menor de todos.

 */
set< list< pair< pair<int,int>,int > > > mySet;	// ((distância até o momento, primeira letra), nodo) 		  	
vector< vector< pair< pair<int, int>, int> > > g;


void updateSetOfLists( list< pair< pair<int,int>,int > > newElements ) {
	
	set< list< pair< pair<int,int>,int > > > auxSet;
	list< pair< pair<int,int>,int > > auxList;
	
	if(newElements.size() > 0) {
		auxSet = mySet;
		mySet.clear();

		for(set< list< pair< pair<int,int>,int > > >::iterator it = auxSet.begin(); it != auxSet.end(); it++) {
			auxList = *it; 
			
			//cout << "value: " << g[auxList.back().second][0].second << endl;
			
			if(auxList.back().second == 1) {
				mySet.insert(auxList);
				continue;
			}
		
			for(list< pair< pair<int,int>,int > >::iterator it2 = newElements.begin(); it2 != newElements.end(); it2++) {
				//cout << "	.((" << (*it2).first.first << "," << (*it2).first.second << "), " << (*it2).second << ")" << endl;
				
				/*
				if(auxList.back().first.second != (*it2).first.second && auxList.back().second != 1) { //1 => nodo de destino (end)
					cout << "	..((" << (*it2).first.first << "," << (*it2).first.second << "), " << (*it2).second << ")" << endl;
					auxList.push_back(*it2);
					mySet.insert(auxList);
					auxList.pop_back();			
				}
				*/
				
				int aux = auxList.back().second;
				for(int i = 0; i < g[aux].size(); i++) {
					if(g[aux][i].second == (*it2).second) {
						if(auxList.back().first.second != (*it2).first.second) {
							//cout << "	..((" << (*it2).first.first << "," << (*it2).first.second << "), " << (*it2).second << ")" << endl;
							auxList.push_back(*it2); //cout << "ok2" << endl;
							mySet.insert(auxList); //cout << "ok3" << endl;
							auxList.pop_back();	//cout << "ok4" << endl;			
						}
					}			
				}	
							
			}
		}	
	}	

	//cout << "Set size: " << mySet.size() << endl;
	
	/*
	cout << endl;
	list< pair< pair<int,int>,int > > aux;
	for(set< list< pair< pair<int,int>,int > > >::iterator it = mySet.begin(); it != mySet.end(); it++) {	
		aux = *it;
		for(list< pair< pair<int,int>,int > >::iterator it2 = aux.begin(); it2 != aux.end(); it2++)
			cout << "(" << (*it2).first.first << "," << (*it2).first.second << "," << (*it2).second << ") ";
		cout << endl;
	}
	//cout << "ok6" << endl;
	*/
	
	return;
}


int getMinW() {
	priority_queue< int, vector<int>, greater<int> > aux;
	list< pair< pair<int,int>,int > > auxList;
	int sum = 0;
	
	//cout << "Vamos calcular!" << endl;

	//cout << "Set size: " << mySet.size() << endl;
	for(set< list< pair< pair<int,int>,int > > >::iterator it = mySet.begin(); it != mySet.end(); it++) {
		auxList = *it; sum = 0;
		if(auxList.back().second != 1)
			continue;
		
		for(list< pair< pair<int,int>,int > >::iterator it2 = auxList.begin(); it2 != auxList.end(); it2++) {
			sum = sum + (*it2).first.first;
			//cout << "(" << (*it2).first.first << "," << (*it2).first.second << "," << (*it2).second << ") ";
		}
		aux.push(sum);
		//cout << sum << endl;
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

			//cout << i+1 << " " << a << "," << b << "=>" << c << endl;
		}

		/*
		int z = 0;
		for(map<string, int>::iterator it = association.begin(); it != association.end(); it++) {
			cout << "association[" << (*it).first << "]:" << (*it).second << endl;
			cout << "g[" << z << "].size():" << g[z].size() << endl;
			z++;
		}
		
		int aa = association.size();
		for(int i = 0; i < aa; i++) {
			for(int j = 0; j < g[i].size(); j++)
				cout << "g[" << i << "][" << j << "]: " << g[i][j].second << ", ";
			cout << endl;
		}
		*/
		
		//dijkstra
		//pair< pair<int,int> ,int> => ( (word_lenght, first_letter), node )
		
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

			//cout << endl << "v: " << v << ", w: (" << w.first << "," << w.second << ")" << endl;
			//cout << "g[" << v << "].size(): " << g[v].size() << endl;			
			//cout << "end_node: " << end_node << " v: " << v << endl;

			if(v == end_node)
				break; //w tem o tamanho do caminho

			vis[v] = w.first;			
			
			int aa = g[v].size();
			for(int i = 0; i < aa; i++) {
				//cout << "vis[" << g[v][i].second << "]: " << vis[ g[v][i].second ] << endl;
				//cout << "g[" << v << "]:((" << g[v][i].first.first << "," << g[v][i].first.second << ")," << g[v][i].second << ")" << endl;
				if( vis[ g[v][i].second ] == -1 ) {
					//cout << "	" << "g[" << v << "]:((" << g[v][i].first.first << "," << g[v][i].first.second << ")," << g[v][i].second << ") in newElements" << endl;
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




