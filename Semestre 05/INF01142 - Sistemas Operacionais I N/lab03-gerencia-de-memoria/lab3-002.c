#include<stdio.h>

long long int fatorial(int n)
{
	if(1 == n)
		return n;
	else
		return fatorial(n-1) *n;
}

main()
{
	long long int lliResp;
	int iFatorial = 21;

	lliResp = fatorial(iFatorial);

	printf("O Fatorial de %d eh: %lld\n", iFatorial, lliResp);
}

