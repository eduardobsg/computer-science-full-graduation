#include <iostream>
#include <queue>
#include <vector>

using namespace std;


int main() {
	int nodes, n;

	while( (cin >> nodes >> n) && nodes != 0 && n != 0 ) {
		
		vector< vector< pair<int,int> > > g;
		
		for(int i = 0; i < nodes; i++)
			g.push_back( vector< pair<int, int> > () );
		
		//captura adjacência e calcula custo total (todas as ruas com luzes acesas)
		int x, y, in, total_cost = 0;		
		for(int i = 0; i < n; i++) {
			cin >> x >> y >> in;
			g[x].push_back( make_pair(in, y) );
			g[y].push_back( make_pair(in, x) );
			
			total_cost = total_cost + in;
		}
		
		//prim
		priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > > q;
		bool vis[nodes];
		pair<int,int> p; 
		int v, w, ret = 0;
	
		for(int i = 0; i < nodes; i++)
	  		vis[i] = 0;
	
		q.push( make_pair(0,0) );
		while(!q.empty()) {
			p = q.top(); q.pop();
		
			w = p.first;
			v = p.second;

			if(vis[v] != 0) 
				continue;
			vis[v] = 1;
			ret += w;
		
			//cout << "g[" << v << "].size(): " << g[v].size() << endl;
			for(int i = 0; i < g[v].size(); ++i) {
				//cout << "i: " << i << ", node: " << g[v][i].second << ", weight: " << g[v][i].first;
				if( !vis[ g[v][i].second ] ) {
					//cout << " ok.";
					q.push( make_pair( g[v][i].first, g[v][i].second ) );
				}
				//cout << endl;
			}
			//cout << endl;
		}
		
		//cout << "totalCost: " << total_cost << ", ret: " << ret << endl;
		cout << total_cost - ret << endl;
	}

	return(0);
}
