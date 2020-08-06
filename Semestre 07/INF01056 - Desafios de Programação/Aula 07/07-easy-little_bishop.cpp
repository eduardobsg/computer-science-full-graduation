#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 70;
 
void init(int n, int c1[N], int c2[N]) {
	
	memset(c1, 0, sizeof(int) * N);
	memset(c2, 0, sizeof(int) * N);
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if((i + j) & 1)
				c2[(i+j)/2]++;
			else
				c1[(i+j)/2]++;
		}
	}
}

void bishops(int n, int dp[N][N], int c[N]) {
	
	for(int i = 0; i <= n; i++)
		dp[i][0] = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= c[i]; j++)
			dp[i][j] = dp[i-1][j] + dp[i-1][j-1] * (c[i] - j + 1);
}
 
int main() {
	int n, k, c1[N], c2[N], dp1[N][N], dp2[N][N], ans;

	while(scanf("%d %d", &n, &k) == 2) {
		if(n == 0 && k == 0)
			break;
	
		init(n, c1, c2);
		sort(c1 + 1, c1 + n + 1);
		sort(c2 + 1, c2 + n);
		memset(dp1, 0, sizeof(dp1));
		memset(dp2, 0, sizeof(dp2));
		bishops(n, dp1, c1);
		bishops(n - 1, dp2, c2);
		ans = 0;
		
		for(int i = 0; i <= k; i++)
			ans += dp1[n][i] * dp2[n-1][k-i];
		printf("%d\n", ans);
	}

	return 0;
}
