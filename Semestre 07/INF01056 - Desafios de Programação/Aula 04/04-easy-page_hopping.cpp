#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

#define INF 999

using namespace std;

int main() {

	int a, b, c = 0;
	while( (cin >> a >> b) && a != 0 && b != 0 ) {
		
		set<int> nodes;
		vector< pair<int, int> > edges;
		map<int, int> new_nodes;
		
		edges.push_back( make_pair(a, b) );
		nodes.insert(a);
		nodes.insert(b);
		while( (cin >> a >> b) && a != 0 && b != 0 ) {
			edges.push_back( make_pair(a, b) );
			nodes.insert(a);
			nodes.insert(b);
		}
		
		//novo mapeamento para os nodos
		int index = 0;
		for(set<int>::iterator it = nodes.begin(); it != nodes.end(); it++) {
			new_nodes[*it] = index;
			index++;
		}
		
		//cria, inicializa e monta matriz de adjacência
		int nodes_size = nodes.size();
		int edges_size = edges.size();
		int mat[nodes_size][nodes_size];		
		for(int i = 0; i < nodes_size; i++) {
			for(int j = 0; j < nodes_size; j++) {
				mat[i][j] = INF;
			}
			mat[i][i] = 0;
		}
			
		for(int i = 0; i < edges_size; i++) {
			mat[new_nodes[edges.at(i).first]][new_nodes[edges.at(i).second]] = 1;
		}
		
		//Floyd's algorithm
		for(int k = 0; k < nodes_size; k++)
			for(int i = 0; i < nodes_size; i++)
				for(int j = 0; j < nodes_size; j++)
             		mat[i][j] = min( mat[i][j], mat[i][k] + mat[k][j] );	
		
		
		//Preparando a saída
		double clicks = 0; 
		int paths = 0;
		for(int i = 0; i < nodes_size; i++) {
			for(int j = 0; j < nodes_size; j++) {
				if(mat[i][j] != 0) {
					clicks = clicks + (double)mat[i][j];
					paths++;
				}
			}
		}
		
		c++;
		printf("Case %d: average length between pages = %.3lf clicks\n", c, (double)clicks/paths);
		
	}
	return 0;
}
