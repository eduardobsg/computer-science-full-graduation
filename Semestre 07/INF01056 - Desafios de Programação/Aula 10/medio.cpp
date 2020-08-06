#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

int main(void)
{
	int numberOfTestCases;
	cin >> numberOfTestCases;
	int n = 1;
	
	while(n <= numberOfTestCases){
		float d, v, u;
		cin >> d >> v >> u;
	
		if((u > 0) && (v > 0) && (u > v)){
			float timeFastestPath = d / u;
			
			float timeShortestPath = d / (sqrt(pow(u, 2) - pow(v, 2)));
			
			float timeToCross = timeShortestPath - timeFastestPath;
			printf("Case %d: %.3f\n", n, timeToCross);
		}
		else{
			cout << "Case " << n << ": can't determine" << endl;
		}
		n++;
	}

	return(0);
}
