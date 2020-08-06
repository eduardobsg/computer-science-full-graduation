/* http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1895

Input
3
1 2 3
4
1 2 3 4
10
100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 
5 
2 2 2 2 3
0

Output
9
19
3400000
26

Ideia: fazer com set e utilizar um vetor pra saber quantas repetições de cada número existem

*/


#include <iostream>
#include <list>

using namespace std;

int main() { 
	
	int quant;
	cin >> quant;

	while(quant != 0) {

		list<int> values;
  		list<int>::iterator it;
		int cost = 0;

		int var;
		for(int i = 0; i < quant; i++) {
			cin >> var;
			values.push_back(var);
		}		

		int a, b, c;
		while(values.size() != 1) {
			values.sort();		
			
			a = values.front();
			values.pop_front();
			b = values.front();
			values.pop_front();
			c = a + b;
			cost = cost + c;
			
			values.push_front(c);
		}

		cout << cost << endl;

		cin >> quant;
	}

	return 0; 

} 
