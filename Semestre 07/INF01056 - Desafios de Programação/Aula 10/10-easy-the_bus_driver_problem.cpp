#include <iostream>
#include <list>

using namespace std;

int main() {

	int n, d, r;

	cin >> n >> d >> r;
	while( n != 0 && d != 0 && r != 0 ) {
		
		list<int> morning, afternoon;
		
		//captura trechos percorridos pela manhã
		for(int a, i = 0; i < n; i++) {
			cin >> a;
			morning.push_back(a);		
		}
		
		//captura trechos percorridos pela tarde
		for(int a, i = 0; i < n; i++) {
			cin >> a;
			afternoon.push_back(a);		
		}

		//ordena
		morning.sort();
		afternoon.sort();

		//calcula gasto com horas extras
		int extra = 0;
		list<int>::iterator it = morning.begin();
		list<int>::reverse_iterator rit = afternoon.rbegin();

		for(; it != morning.end() && rit != afternoon.rend();
			it++, rit++) {
			
			if( (*it + *rit) > d) {
				extra += (*it + *rit - d) * r;
			}
		}

		cout << extra << endl;
		cin >> n >> d >> r;
	}
	
	return 0;
}
