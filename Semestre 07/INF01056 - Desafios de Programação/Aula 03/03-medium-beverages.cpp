#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <queue>

#define MAX 200

using namespace std;

int main() {
	
	int a, c = 0;
	while( (cin >> a) && a != EOF ) {
			
		map<string, int> beverages;
		map<int, string> beverages2;
		vector<int> relation[MAX];
		queue<string> output;
		int values[a], index = 0;
		
		string beverage;	
		while(a--) {
			cin >> beverage;
			beverages[beverage] = index;
			beverages2[index] = beverage;
			values[index] = 0;
			index++;
		}
		
		string b1, b2;
		int b;
		cin >> b; 
		while(b--) {
			cin >> b1 >> b2;
			relation[beverages[b1]].push_back(beverages[b2]); //monta as relações de uma bebida fraca (b1) com uma bebida mais forte (b2)
			values[beverages[b2]]++; //values conta a quantidade de vezes que cada bebida está à direita
		}
			
		while(beverages.size() != output.size()) { //itera até a quantidade de elementos de saída ser igual a quantidade de bebidas
			for(int i = 0; i < beverages.size(); i++) {
				if(values[i] == 0) { //se o 'values' de uma bebida estiver em zero, isso quer dizer que a bebida é a mais fraca no momento, logo deve entrar na fila de bedidas para impressão
					output.push(beverages2[i]);

					for(int j = 0; j < relation[i].size(); j++) {
						values[relation[i][j]] = values[relation[i][j]] - 1; //cada bebida mais forte associada a bebida i terá o value decrescido de uma unidade 	
					}

					values[i] = -1; //a bebida i sai fora do ciclo de análise de bebidas
					break; //começa a varrer as bebidas do início
				}
			}
		}
			
		c++; //contador de casos
		cout << "Case #" << c << ": Dilbert should drink beverages in this order:";
		while(!output.empty()) {
			cout << " " << output.front();
			output.pop();
		}
		cout << "." << endl << endl;
	}

	return 0;
}
