#include <iostream>
#include <queue>

using namespace std;

int **adj;

int prim(int nodes) {
	priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;
  	bool vis[nodes];
  	pair<int,int> p; 
  	int v, w, ret = 0;
  	
  	for(int i = 0; i < nodes; i++)
  		vis[i] = 0;
  		
  	q.push(make_pair(0,0));
  	while(!q.empty()) {
      	p = q.top(); 
      	q.pop();
      	
      	w = p.first;
      	v = p.second;      	
      	
      	if(vis[v] != 0) 
      		continue;
      	vis[v] = 1;
      	
      	ret += w;
      	for(int i = 0; i < nodes; i++)
      		if(adj[v][i] != -1) {
      			//adj[i][v] = -1;
      			if(!vis[i])
	    			q.push( make_pair(adj[v][i], i) );
	    	}
	}
	
	return ret;
}

int main() {
	int nodes, n;

	while( (cin >> nodes >> n) && nodes != 0 && n != 0 ) {

		//cria matriz de adjacência
		adj = new int*[nodes];
		for(int i = 0; i < nodes; i++) 
			adj[i] = new int[nodes];
		
		//inicializa matriz de adjacência	
		for(int i = 0; i < nodes; i++) 
			for(int j = 0; j < nodes; j++) 	
				adj[i][j] = -1;
		
		//captura adjacência e calcula custo total (todas as ruas com luzes acesas)
		int x, y, in, total_cost = 0;		
		for(int i = 0; i < n; i++) {
			cin >> x >> y >> in;
			adj[x][y] = adj[y][x] = in;
			total_cost = total_cost + adj[x][y];
		}
		
		//roda algoritmo prim
		int ret = prim(nodes);
		
		//cout << "totalCost: " << total_cost << ", ret: " << ret << endl;
		cout << total_cost - ret << endl;
	}

	return(0);
}
