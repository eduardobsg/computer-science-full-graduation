#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main(void) {
	string a, b;

	while(getline(cin, a)) {
		getline(cin, b);
		int i = 0;

		priority_queue< char, vector<char>, greater<char> > aux;

		while(a[i] != '\0') {
			bool found = false;
			int j = 0;

			while((!found) && (b[j] != '\0')) {
				if(a[i] == b[j]){
					aux.push(a[i]);
					a[i] = '1';
					b[j] = '1';
					found = true;
				}
				else {
					j++;
				}
			}

			i++;
		}

		while( !aux.empty() ) {
			cout << aux.top();
			aux.pop();
		}

		cout << endl;

		a.erase();
		b.erase();
	}

	return 0;
}
