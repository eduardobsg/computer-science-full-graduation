#include <cstdio>

#define N 105

unsigned int dp[N][N];

unsigned int ways(int n,int k) {
	if(n < 0 || k < 0)
		return 0;
	if(dp[n][k] != -1)
		return dp[n][k];
	else {
		unsigned int res = 0;
		
		for(int i = 0; i <= n; i++)
			res += ways(n-i,k-1) % 1000000;

		return dp[n][k] = res % 1000000;
	}
}

int main() {

	int i, j;

	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			dp[i][j] = -1;

	dp[0][0] = 1;
	while(scanf("%d %d", &i, &j) == 2 && i)
		printf("%u\n", ways(i, j));

	return 0;
}

