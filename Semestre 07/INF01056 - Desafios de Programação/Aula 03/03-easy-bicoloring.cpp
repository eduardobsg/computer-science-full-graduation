#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

#define MAX 200
#define BLACK 0
#define	WHITE 1

using namespace std;

int main() {

	int nodes;
    while( (cin >> nodes) && nodes != 0) {
		int edges, x, y, num[MAX];
        queue<int> q;
	    vector<int> v[MAX];
		
        cin >> edges;
		for(int i = 0; i < edges; i++) {
            cin >> x >> y;
            v[x].push_back(y);
            v[y].push_back(x);
		}
	
		/* v[0].size() = quantidade de nodos ligados ao nodo 0
		for(int i = 0; i < v[0].size(); i++) {
			cout << v[0][i] << " ";
		}
		cout << endl;		
		for(int i = 0; i < v[1].size(); i++) {
			cout << v[1][i] << " ";
		}
		cout << endl;
		*/

        memset(num, -1, sizeof(num));
        num[0] = BLACK; //o nodo 0 é colorido com a cor 0       
        q.push(num[0]);
        
        int val;
        bool b = true;
        while(!q.empty() && b != false) { //vai testando todos os nodos presentes na fila, até que a fila esteja vazia
			x = q.front();
			q.pop();
			val = v[x].size();
			
			//cout << "x:" << x << ", val:" << val << endl;
			
			for(int i = 0; i < val; i++) {
				if(num[v[x][i]] == -1) { //testa se um nodo ligado a x já foi colorido
					if(num[x] == BLACK) //se o nodo x possuir cor BLACK, então o nodo vizinho a ele deve possuir cor WHITE
						num[v[x][i]] = WHITE;
					else //se o nodo x possuir cor WHITE, então o nodo vizinho a ele deve possuir cor BLACK
						num[v[x][i]] = BLACK;
					q.push(v[x][i]); //colocar o nodo vizinho ao nodo x na fila
				}
                else {
					if(num[v[x][i]] == num[x]) { //o nodo ligado ao nodo x está colorido, logo precisamos saber se eles tem cores diferentes
						b = false; //os nodos são vizinhos e possuem cores iguais, logo o grafo não é bicolorível
						break;
					}
				}
			}
		}
		
        if(b == true)
        	cout << "BICOLORABLE." << endl;
        else
        	cout << "NOT BICOLORABLE." << endl;
    }

	return 0;
}
