#include <iostream>
#include <cstdio>

using namespace std;

long long int ways[30005];
int coins[] = {1, 5, 10, 25, 50};

int main() {
	
	int coin;
	ways[0] = 1;
	
	for(int i = 0; i < 5; i++) {
		coin = coins[i];
		for(int j = coin; j < 30005; j++)
			ways[j] += ways[j - coin];
	}

	int in;
	while(cin >> in) {
		if(ways[in] > 1)
			printf("There are %llu ways to produce %d cents change.\n", ways[in], in);
		else
			printf("There is only 1 way to produce %d cents change.\n", in);
	}

	return 0;

}

