#include <stdio.h>
#include <omp.h>

#define iterations 20000000
int main()
{
	double pi = 0;
	int i;
#pragma omp parallel for reduction (+:pi)
	for (i = 0; i < iterations; i++)
	{
		pi += 4.0 / (4.0 * i + 1.0);
		pi -= 4.0 / (4.0 * i + 3.0);
	}
	printf("Pi is more or less: %f\n", pi);
}
