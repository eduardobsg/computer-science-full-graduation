#include <iostream>
#include <cstdio>
#include <climits>

#define MAX 101	

using namespace std;


int main() {

	long sum[MAX][MAX], a[MAX][MAX];

	int n;
	while( cin >> n ) {
	
		//armazena a entrada na matriz
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				scanf("%ld", &a[i][j]);

		for(int k = 1; k <= n; k++)
			for(int l = 1; l <= n; l++)
		  		for(int i = k; i <= n; i++)
		  			for(int j = l; j <= n; j++) {
						sum[0][j] = sum[i][0] = sum[0][0] = 0;
		   				sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j];
		   				printf("sum[%d][%d] = sum[%d][%d] + sum[%d][%d] - sum[%d][%d] + a[%d][%d]\n", i, j, i-1, j, i, j-1, i-1, j-1, i, j);
		   				printf("sum[%d][%d] = %ld + %ld - %ld + %ld\n", i, j, sum[i-1][j], sum[i][j-1], sum[i-1][j-1], a[i][j]);
		   				printf("sum[%d][%d] = %ld\n\n", i, j, sum[i][j]);
		   			}

		
		long max = -99999999;
		int temp;
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
		  		for(int k = i; k <= n; k++)
		   			for(int l = j; l <= n; l++) {
			   			temp = sum[k][l] - sum[i-1][l] - sum[k][j-1] + sum[i-1][j-1];
			   			if(temp > max)
			   				max = temp;
					}
					
		printf("%ld\n", max);

	}

	return 0;
}
