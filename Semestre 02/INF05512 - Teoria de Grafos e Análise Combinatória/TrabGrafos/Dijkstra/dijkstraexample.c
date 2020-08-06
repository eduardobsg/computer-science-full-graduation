#include <stdio.h>
#include <stdlib.h>       
#include <string.h>      
#include <time.h> 
 
#define MALLOC(t,n)    (t *) malloc( n*sizeof(t) ) 
#define MALLOC2D(t,n)  (t **) malloc(n*sizeof(t) )
#define CHECKPTR(p)    if (!p) Error("Out of memory")

#define MAX_INT 999999999


int vertexNum;
int  **PATHS     = (int**)  NULL;  //edgelerin uzunluklari
int **ROUTE2     = (int**) NULL;   //ROUTE mizi belirleriz
int  *SHORTEST_PATH       = (int*)   NULL;  //o vertex in baslangica en kisa yolu
int  *VISITED = (int*)   NULL;      //Y a dahil olanlarý isaretlenmis gibi gosterecegiz


//////////////////////////////////////
//
//  if any error occurs we can write it
//
//////////////////////////////////////
void Error (char *str)
{ 
	printf("\nERROR: %s\n", str);
	return;
}

//////////////////////////////////////
//
//  rmy_vertexs the file and built the synamic structure 
//
//////////////////////////////////////
void readFileBuiltStruct( char *str)
{
	FILE *fpRead;
	int i,j;
	int num;

	fpRead = fopen(str,"r");

	//start to rmy_vertex the input.txt

	rewind ( fpRead );

	fscanf ( fpRead, "%d", &vertexNum);

	//mallocations dynamicly and check for errors 

	SHORTEST_PATH = MALLOC( int , vertexNum );
	CHECKPTR( SHORTEST_PATH );

	VISITED = MALLOC( int , vertexNum );
	CHECKPTR( VISITED );

	PATHS = MALLOC2D( int , vertexNum );
	CHECKPTR( PATHS );

	ROUTE2 = MALLOC2D( int , vertexNum );
	CHECKPTR( ROUTE2 );

	for(i=0; i<vertexNum; i++)
	{
		PATHS[i] =  MALLOC( int , vertexNum );
		CHECKPTR( PATHS[i] );

		ROUTE2[i] = MALLOC( int , vertexNum );
		CHECKPTR( ROUTE2[i] );


		//say that Y is empty
		VISITED[i] = 0; 
		
		//set the paths as vrey long 
		SHORTEST_PATH[i] = MAX_INT;

	}

	//rmy_vertex the distances
	for(i=0; i<vertexNum; i++)
	{
		for(j=0; j<vertexNum; j++)
		{
			fscanf ( fpRead, "%d", &num);

			PATHS[i][j] = num;
			ROUTE2[i][j] = -1;
		}
	}

	/*
	//write the distances to stdout to control
	for(i=0; i<vertexNum; i++)
	{
		for(j=0; j<vertexNum; j++)
		{
			printf("%3d ",PATHS[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	*/
	
	fclose( fpRead );

}


//////////////////////////////////////
//
//  returns the beginning vertex 
//
//////////////////////////////////////
int getSourceVertex( int size )
{

	srand(23058);  //230702058
	return rand()%size;
}



//////////////////////////////////////
//
//  find the shortest paths for the beginnig vertex
//  and store the routines that on which vertex can we go..
//
//////////////////////////////////////
void findTheRotutines(int source)
{
	int i, j, k;
	int my_vertex;
	int ek;

	SHORTEST_PATH[source ] = 0;
	my_vertex              = source; //o anda uzerinde islem yaptigimiz dugum..


	i=0;
	while( i++ < vertexNum )
	{
		//we will decide to which vertex is closer that is not in Y (not visited)
		for(j=0; j<vertexNum; j++)
		{
			//if we find a vertex that is not Y, lets work on it
			if( VISITED[j] == 0 )
			{
				//if there is a connection with the vertexes
				if( PATHS[my_vertex][j] != -1 )
				{
					//decide the shortest paths
					if( SHORTEST_PATH[j] > PATHS[my_vertex][j] + SHORTEST_PATH[my_vertex] )
					{
						//we found more shortest way.. change the old one
						SHORTEST_PATH[j] = PATHS[my_vertex][j] + SHORTEST_PATH[my_vertex];

						for(k=0; k<vertexNum; k++ )
						{
							ROUTE2[j][k] = ROUTE2[my_vertex][k];
						}

						k=0;
						while(ROUTE2[j][k] != -1 )
						{
							k++;
						}
	
						ROUTE2[j][k] = my_vertex;	
					}
					
				}
			}
			
		}
		

		ek = MAX_INT;

		for( j=1; j<vertexNum; j++)
		{
			if( VISITED[j] == 0 )
			{
				if( SHORTEST_PATH[j] < ek )
				{
					ek = SHORTEST_PATH[j];
					my_vertex = j;
				}
			}
		}

		VISITED[ my_vertex ] = 1;
	}


	
	for( i=0; i<vertexNum; i++)
	{
		
		if( ROUTE2[i][0] != -1 || source == i)
		{
			k=0;
			while(ROUTE2[i][k] != -1 )
			{
				k++;
			}

			ROUTE2[i][k] = i;
		}
	}

	/*
	printf("\n\n");
	for(i=0; i<vertexNum; i++)
	{
		for(j=0; j<vertexNum; j++)
		{
			printf("%2d,",ROUTE2[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	*/
}



//////////////////////////////////////
//
//  writes the results to output file
//
//////////////////////////////////////
void writeToOutput(char *outputName, int source)
{
	FILE *fpOut;
	int j,k;
	int len;
	int emptySpace = 12;

	fpOut = fopen( outputName , "w" );

	rewind ( fpOut );

	fprintf(fpOut, "Beginning Vertex : %d\n\n", source );

	fprintf(fpOut, "Nodes     Path      Distance  \n");
	fprintf(fpOut, "------------------------------\n");

	for( j=0; j<vertexNum; j++)
	{
		if( j != source)
		{
			fprintf(fpOut, "%d - %d     ",source, j); //write the nodes


			len =0;
			k   =0;
			while( ROUTE2[j][k] != -1 )
			{
				if(ROUTE2[j][k+1] == -1 )
				{
					fprintf(fpOut, "%d", ROUTE2[j][k] );
					len += 1;
				}
				else
				{
					fprintf(fpOut, "%d-", ROUTE2[j][k] );
					len += 2;
				}
				k++;
			}
			
			for(k=0; k<emptySpace - len; k++)
				fprintf(fpOut," ");

			fprintf(fpOut, "%d\n", SHORTEST_PATH[j] );
		}
	}

	fclose( fpOut );
}


//////////////////////////////////////
//
//  the main part of the program
//
//////////////////////////////////////
int main()
{
	
	int beginningV;

	readFileBuiltStruct("input.txt");

	beginningV = getSourceVertex( vertexNum );
	//printf("%d\n",beginningV);

	findTheRotutines( beginningV );

	writeToOutput("output.txt", beginningV);
    system("pause");
/*
	free( SHORTEST_PATH );
	free( PATHS );
	free( ROUTE );
	free( VISITED );
	free( ROUTE2 );
*/
		
	return 0;
}
