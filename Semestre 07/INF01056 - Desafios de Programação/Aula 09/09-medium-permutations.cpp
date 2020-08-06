#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

vector<long long> factorial;

void perm(string cad1, int len, long long id) {
    long long i, j = 0, k, r;

    for(i = len; i > 0; i--) {
        sort(cad1.begin() + j, cad1.end());

        for(k = 0; k < i && factorial[i-1] * k <= id; k++)
            r = factorial[i-1] * k;

        swap(cad1[j], cad1[k+j-1]);
        j++;
        id -= r;
    }
	
    printf("%s\n", cad1.c_str());
}


int main() {
    long long test, id;
    factorial.push_back(1);
    
	for(int i = 1; i < 22; i++)
        factorial.push_back(factorial[i-1] * i);

    cin >> test;
    while(test--) {
        string cad1;
        cin >> cad1 >> id;
        perm(cad1, cad1.length(), id);
    }

	return 0;
}
