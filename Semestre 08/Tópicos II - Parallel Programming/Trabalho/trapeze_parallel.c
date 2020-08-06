/*
Group: Henrique Weber
	   João Luiz Grave Gross
Parallel Programming - Professor Nicolas Maillard

Parallel Version

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

Compiling: mpicc trapeze_parallel.c -o trapeze_parallel
Run: mpirun -np 3 ./trapeze_parallel

cd /home/jlggross/Dropbox/UFRGS/2010-02\ -\ Quarto\ Semestre/Tópicos\ II\ -\ Parallel\ Programming

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>

double * CaptureEntries( double *, long int *, long int * );
void CalculateInteger( int , int , double, double *, double *, long int *, double *, long int *, long int, long int );
double CalculatePolynomial( double *, double *, long int * );
void PrintResult( double *, double *, long int *, double *, double *, long int * );

int main (int argc, char **argv)
{
	/* Variable Declaration */	
	double interval[2], interval_h, *polynomial, integer = 0, parcial_integer = 0;
	long int subintervals, polynomial_grade, init_subint = 0, end_subint = 0, aux_subint = 0;
	int i;	

	/* For time counting */
	struct timeval tv_begin, tv_end;
	double t_begin, t_end, t_total;

	/* MPI variables */	
	int numtasks, rank, root = 0, dest = 0, tag = 666; 
	int resultlength;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &resultlength);
	
	if(numtasks < 2)
	{
		printf("You must run the application with at least 3 processes.\n");
		exit(1);
	}

	if(rank == 0)
	{
		//printf("Process rank: %d\n", rank);
		
		polynomial = CaptureEntries( interval, &subintervals, &polynomial_grade );			
/*
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
*/
		interval_h = (interval[1] - interval[0]) / subintervals;

		/* Initiating data send to ranks != 0 */
		gettimeofday(&tv_begin, NULL); 	
		t_begin = (tv_begin.tv_sec)*1000000 + tv_begin.tv_usec;

		MPI_Bcast( &polynomial_grade, 1, MPI_LONG, root, MPI_COMM_WORLD ); //send the polynomial grade
		MPI_Bcast( polynomial, polynomial_grade+1, MPI_DOUBLE, root, MPI_COMM_WORLD ); //send the polynomial
		MPI_Bcast( &interval_h, 1, MPI_DOUBLE, root, MPI_COMM_WORLD ); //send the interval h = (b - a) / n
		MPI_Bcast( interval, 2, MPI_DOUBLE, root, MPI_COMM_WORLD ); //send the interval [a,b]
		MPI_Bcast( &subintervals, 1, MPI_LONG, root, MPI_COMM_WORLD ); //send subintervals

		integer = integer + CalculatePolynomial( polynomial, &interval[0], &polynomial_grade ); //begin of interval
		integer = integer + CalculatePolynomial( polynomial, &interval[1], &polynomial_grade ); //end of interval

		/* Distributes the subintervals between the processes */
		aux_subint = subintervals / (numtasks - 1);
		init_subint = 1;
		end_subint = end_subint + aux_subint;
		for(i = 1; i < numtasks; i++)
		{
			MPI_Send(&init_subint, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);		
			MPI_Send(&end_subint, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);		
			init_subint = end_subint;
			if(i == numtasks-2)
				end_subint = end_subint + aux_subint + subintervals % (numtasks - 1);
			else
				end_subint = end_subint + aux_subint;
		}

		/* Waits for the parcial integers, calculated by the processes */
		for(i = 1; i < numtasks; i++)
		{
			parcial_integer = 0;
			MPI_Recv(&parcial_integer, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &Stat);		
			//printf("Rank 0 received for parcial_integer %lf\n", parcial_integer);
			integer += parcial_integer;
		}
		integer *= interval_h / 2;
		//printf("Rank 0, Integer = %lf\n", integer);

		//printf("Integer: %.10lf, ", integer);
		
		gettimeofday(&tv_end, NULL); 
		t_end = (tv_end.tv_sec)*1000000 + tv_end.tv_usec;
	
		t_total = t_end - t_begin; //The value is in micro seconds

		PrintResult( interval, polynomial, &subintervals, &integer, &t_total, &polynomial_grade );

	}
	else
	{
		//printf("Process rank: %d\n", rank);

		/* Processes with rank != from 0 receive information from the root */		
		MPI_Bcast( &polynomial_grade, 1, MPI_LONG, root, MPI_COMM_WORLD );

		/* Allocing memory for the polynomial */
		polynomial = (double *)malloc( (polynomial_grade + 1) * sizeof(double) );		

		MPI_Bcast( polynomial, polynomial_grade+1, MPI_DOUBLE, root, MPI_COMM_WORLD );
		MPI_Bcast( &interval_h, 1, MPI_DOUBLE, root, MPI_COMM_WORLD );
		MPI_Bcast( interval, 2, MPI_DOUBLE, root, MPI_COMM_WORLD );
		MPI_Bcast( &subintervals, 1, MPI_LONG, root, MPI_COMM_WORLD );

		MPI_Recv(&init_subint, 1, MPI_DOUBLE, root, tag, MPI_COMM_WORLD, &Stat);		
		MPI_Recv(&end_subint, 1, MPI_DOUBLE, root, tag, MPI_COMM_WORLD, &Stat);

		CalculateInteger( rank, numtasks, interval_h, interval, polynomial, &subintervals, &parcial_integer, &polynomial_grade, init_subint, end_subint );	

		//printf("Rank %d sent Parcial Integer: %lf\n", rank, parcial_integer);

		MPI_Send(&parcial_integer, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);	
	}
	
	MPI_Finalize();

	return 0;
}

double * CaptureEntries( double *interval, long int *subintervals, long int *polynomial_grade )
{
	int i, ret;
	double *polynomial;
	
	printf("Welcome to the polynomial integer calculator!!\n\n");
	
	/* Capture polynomial maximum grade. Then we know how many coeficients we have to ark for */	
	do
	{
		printf("Highest polynomial grade: ");
		ret = scanf("%ld", polynomial_grade);
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
		ret = scanf("%lf", &polynomial[i]);
	}	

	do
	{
		printf("\nInterval:\n");
		printf("Begin: ");
		ret = scanf("%lf", &interval[0]);
		printf("End: ");
		ret = scanf("%lf", &interval[1]);
		if(interval[0] >= interval[1])
			printf("\tError: Invalid interval. Begin point must be lower then end point!\n\n");
	} while(interval[0] >= interval[1]);
	
	do
	{
		printf("\nNumber of subintervals: ");
		ret = scanf("%ld", subintervals);
		if(*subintervals < 1)
			printf("\tError: Invalid number. It must be higher then zero!\n\n");	
	} while(*subintervals < 1);
	
	return polynomial;
}

double CalculatePolynomial( double *polynomial, double *xi, long int *polynomial_grade )
{
	double trapeze = 0;
	int i;
	
	for(i = 0; i <= *polynomial_grade; i++) //printf ( "4.73 ^ 12 = %lf\n" , pow (4.73,12)
		trapeze = trapeze + polynomial[i]*pow(*xi,i);
	//printf("Trapeze: %lf\n", trapeze);
	//getchar();
	return trapeze;
}

void CalculateInteger( int rank, int numtasks, double interval_h, double *interval, double *polynomial, long int *subintervals, double *parcial_integer, long int *polynomial_grade, long int init_subint, long int end_subint )
{
	double interval_aux;
	long int i;	
	*parcial_integer = 0;
	
	for(i = init_subint; i < end_subint; i++)
	{
		interval_aux = interval[0] + i*interval_h;
		*parcial_integer = *parcial_integer + 2*CalculatePolynomial( polynomial, &interval_aux, polynomial_grade );	
	}

	return;
}

void PrintResult( double *interval, double *polynomial, long int *subintervals, double *integer, double *t_total, long int *polynomial_grade )
{
	int i;

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
	printf("Integer: %.10lf\n", *integer);

/*
	if(*t_total < 1000000)	
		printf("Total time: %lf us\n\n", *t_total);
	else
		printf("Total time: %lf s\n\n", *t_total/1000000);
*/

	printf("Time: %.10lf s\n\n", *t_total/1000000);

	return;
}

