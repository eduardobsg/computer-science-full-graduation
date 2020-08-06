#include <iostream>
#include <map>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
	int entry[5];
	char name[20];	
	
	int a;
	while((cin >> a) && a != 0) {
		
		map<string, int> combinations;
		string str;
		for(int i = 0; i < a; i++) {
			cin >> entry[0] >> entry[1] >> entry[2] >> entry[3] >> entry[4];
			
			sort(entry, entry + 5);
			sprintf(name, "%d%d%d%d%d", entry[0], entry[1], entry[2], entry[3], entry[4]);
			str = name;
			combinations[str]++;
		}
		
		int fresh_quant = 0, result = 0;
		for(map<string, int>::iterator it = combinations.begin(); it != combinations.end(); it++) {		
			if(it->second == fresh_quant) {
				result += it->second;
			}				
			else if(it->second > fresh_quant) {
				fresh_quant = it->second;
				result = it->second;
			}
			
			//printf("fresh: %d, result: %d, combinations: %d\n", fresh_quant, result, it->second);
		}
		
		cout << result << endl;
	}

	return 0;
}
