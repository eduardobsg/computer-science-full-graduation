/*
Group: Henrique Weber
	   João Luiz Grave Gross
Parallel Programming - Professor Nicolas Maillard

Sequencial Version

Trapeze Method
Computer can evaluate integrals approximately, an one of the most frequently used methods is the 
trapeze method. The interval [a; b] is separated into N equal subintervals. There is no need to 
take very big values of N: the appropriate N for most cases is 8. The width of each subinterval
W = (b - a)/N. The kth subinterval (k = [1; N]) begins at point xk-1 = a + W*(k-1) and ends at 
point xk = a + W*k. The values of function in this points are yk-1 = f(xk-1) and yk = f(xk). The 
square under the function on the kth subinterval is approximately calculated using the square of 
trapeze formula: Sk = (yk-1 + yk)/2 * W. Then all the squares are summed. This sum is the value 
of integral: S = S1 + S2 + ... + SN.

Equation: integer from a to b of f(x)dx = W/2 * ( f0 + fn + sum from j=1 to n-1 of fj )
	- in this equation f0 == f(a) and fn == f(b)

	Software Entries:
		Interval: [a;b] 
			- a must be lower then b
		Polynomial: coeficients of the polynomial
		Number of subintervals: must be 1 or higher	 
		
	Functions:
		Capture the entries
		Calculates the integral		


*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

double * CaptureEntries( double *, long int *, long int * );
void CalculateInteger( double *, double *, long int *, double *, long int * );
double CalculatePolynomial( double *, double *, long int * );
void PrintResult( double *, double *, long int *, double *, double *, long int * );

int main ()
{
	/* Variable Declaration */	
	double interval[2], *polynomial, integer;
	long int subintervals, polynomial_grade;
	
	/* For time counting */
	struct timeval tv_begin, tv_end;
	double t_begin, t_end, t_total;
	
	//polynomial = CaptureEntries( interval, &subintervals, &polynomial_grade );
	polynomial_grade = 4;
	polynomial = (double *)malloc( (polynomial_grade + 1) * sizeof(double) );						
	polynomial[4] = 0.625;
	polynomial[3] = -4;
	polynomial[2] = 0;
	polynomial[1] = 2;
	polynomial[0] = 1;
	interval[0] = 0;
	interval[1] = 8;
	subintervals = pow(10,7);

	gettimeofday(&tv_begin, NULL); 	
	t_begin = (tv_begin.tv_sec)*1000000 + tv_begin.tv_usec;
	CalculateInteger( interval, polynomial, &subintervals, &integer, &polynomial_grade );
	gettimeofday(&tv_end, NULL); 
	t_end = (tv_end.tv_sec)*1000000 + tv_end.tv_usec;
	
	t_total = t_end - t_begin; //The value is in micro seconds

	PrintResult( interval, polynomial, &subintervals, &integer, &t_total, &polynomial_grade );
	
	return 0;
}

double * CaptureEntries( double *interval, long int *subintervals, long int *polynomial_grade )
{
	int i;
	double *polynomial;
	
	printf("Welcome to the polynomial integer calculator!!\n\n");
	
	/* Capture polynomial maximum grade. Then we know how many coeficients we have to ark for */	
	do
	{
		printf("Highest polynomial grade: ");
		scanf("%ld", polynomial_grade);
		if(*polynomial_grade <= 0)
			printf("\tError: Invalid number. Try again!\n\n");		
	} while(*polynomial_grade <= 0);
	
	/* Allocing memory for the polynomial */
	polynomial = (double *)malloc( (*polynomial_grade + 1) * sizeof(double) );

	/* Capturing the polynomial coeficients */
	printf("\nPolynomial coeficients:\n");
	for(i = *polynomial_grade; i >= 0; i--)
	{
		printf("\tCoeficient for grade %d: ", i);
		scanf("%lf", &polynomial[i]);
	}	

	do
	{
		printf("\nInterval:\n");
		printf("Begin: ");
		scanf("%lf", &interval[0]);
		printf("End: ");
		scanf("%lf", &interval[1]);
		if(interval[0] >= interval[1])
			printf("\tError: Invalid interval. Begin point must be lower then end point!\n\n");
	} while(interval[0] >= interval[1]);
	
	do
	{
		printf("\nNumber of subintervals: ");
		scanf("%ld", subintervals);
		if(*subintervals < 1)
			printf("\tError: Invalid number. It must be higher then zero!\n\n");	
	} while(*subintervals < 1);
	
	return polynomial;
}

double CalculatePolynomial( double *polynomial, double *xi, long int *polynomial_grade )
{
	double trapeze = 0;
	int i;
	
	//printf("Trapeze\n");
	for(i = 0; i <= *polynomial_grade; i++) //printf ( "4.73 ^ 12 = %lf\n" , pow (4.73,12)
	{
		trapeze = trapeze + polynomial[i]*pow(*xi,i);
		//printf("(%.4lf)*(%.4lf)^%d = %.4lf\n", polynomial[i], *xi, i, polynomial[i]*pow(*xi,i));
	}
	//printf("Trapeze: %.4lf\n\n", trapeze);
	//getchar();
	return trapeze;
}

void CalculateInteger( double *interval, double *polynomial, long int *subintervals, double *integer, long int *polynomial_grade )
{
	double interval_h, interval_aux;
	long int i;	

	interval_h = (interval[1] - interval[0]) / *subintervals;
	
	*integer = *integer + CalculatePolynomial( polynomial, &interval[0], polynomial_grade );
	//printf("Integer: %lf\n\n", *integer);
	*integer = *integer + CalculatePolynomial( polynomial, &interval[1], polynomial_grade );
	//printf("Integer: %lf\n\n", *integer);
	
	for(i = 1; i < *subintervals; i++)
	{
		interval_aux = interval[0] + i*interval_h;
		*integer = *integer + 2*CalculatePolynomial( polynomial, &interval_aux, polynomial_grade );	
		//printf("Integer: %lf\n\n", *integer);
		//getchar();
	}
	
	*integer = *integer * interval_h / 2;

	return;
}

void PrintResult( double *interval, double *polynomial, long int *subintervals, double *integer, double *t_total, long int *polynomial_grade )
{
	int i;
	
	/*
	printf("\nPolynomial: ");
	for(i = *polynomial_grade; i >= 0; i--)
	{
		if(i == 0)
			printf("%.2lf*x^%d\n", polynomial[i], i);
		else
			printf("%.2lf*x^%d +", polynomial[i], i);	
	}
	
	printf("Interval: [%.2lf,%.2lf]\n", interval[0], interval[1]);
	printf("Number of subintervals: %ld\n", *subintervals);

	printf("Integer in the given interval: %lf\n", *integer);
	if(*t_total < 1000000)	
		printf("Total time: %lf us\n\n", *t_total);
	else
		printf("Total time: %lf s\n\n", *t_total/1000000);
	*/
	printf("Integer: %.10lf, Time: %lf s\n", *integer, *t_total/1000000);
	
	return;
}

