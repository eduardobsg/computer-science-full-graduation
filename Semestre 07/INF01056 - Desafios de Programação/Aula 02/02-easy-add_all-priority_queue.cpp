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

*/


#include <iostream>
#include <queue>

using namespace std;

int main() { 
	
	int quant;
	cin >> quant;

	while(quant != 0) {

		priority_queue < int, vector<int>, greater<int> > values;
		int cost = 0;

		int var;
		for(int i = 0; i < quant; i++) {
			cin >> var;
			values.push(var);
		}		

		int a, b;
		while(values.size() != 1) {
			a = values.top();
			values.pop();
			b = values.top();
			values.pop();
			cost += a + b;
			
			values.push(a + b);
		}

		cout << cost << endl;

		cin >> quant;
	}

	return 0; 

} 
