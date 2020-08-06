/*
Algoritmo: heap_sort.c
Data: 03/05/2010

Rodar no terminal: 

$ ./heap_sort -i -t 5 //roda o binário insertion_sort, gerando um vetor de chaves inteiras de tamanho 5
$ ./heap_sort -s -t 5 //roda o binário insertion_sort, gerando um vetor de structs com 5 structs

*/

#include <stdio.h>
#include <stdlib.h> //rand(), srand(), atoi()
#include <unistd.h> //getopt()
#include <sys/time.h>

struct s_elemento
{
    int chave;
    int v[11];
};

void siftDown(int numbers[], int root, int bottom, long int *comp, long int *trocas)
{
  int done, maxChild, temp;
 
  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    *comp = *comp + 1;	
    if (root*2 == bottom)
    {
      	*comp = *comp + 1;	
      	maxChild = root * 2;
    }
    else
    {
	*comp = *comp + 1;	
	if (numbers[root * 2] > numbers[root * 2 + 1])
      		maxChild = root * 2;
	else
     	 	maxChild = root * 2 + 1; 
	*comp = *comp + 1;	
    }
 
    if (numbers[root] < numbers[maxChild])
    {
      temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      *trocas = *trocas + 3;
      root = maxChild;
    }
    else
      done = 1;
    *comp = *comp + 1;	
  }
}

void heapSort(int numbers[], int array_size, long int *comp, long int *trocas)
{
  int i, temp;
 
  for (i = array_size - 1; i >= 0; i--)
  {
    *comp = *comp + 1;	
    siftDown(numbers, i, array_size - 1, comp, trocas);
  }
 
  for (i = array_size-1; i >= 1; i--)
  {
    *comp = *comp + 1;	
    temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    *trocas = *trocas + 3;
    siftDown(numbers, 0, i-1, comp, trocas);
  }
}
 
void siftDown2(struct s_elemento numbers2[], int root, int bottom, long int *comp, long int *trocas)
{
  int done, maxChild;
  struct s_elemento s_temp;
 
  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    *comp = *comp + 1;	
    if (root*2 == bottom)
    {
      maxChild = root * 2;
      *comp = *comp + 1;	
    }
    else 
    {
    	*comp = *comp + 1;	
	if (numbers2[root * 2].chave > numbers2[root * 2 + 1].chave)
      		maxChild = root * 2;
    	else
      		maxChild = root * 2 + 1;
	*comp = *comp + 1;	
    }
 
    if (numbers2[root].chave < numbers2[maxChild].chave)
    {
      s_temp = numbers2[root];
      numbers2[root] = numbers2[maxChild];
      numbers2[maxChild] = s_temp;
      *trocas = *trocas + 3;	
      root = maxChild;
    }
    else
      done = 1;
    *comp = *comp + 1;
  }
}


void heapSort2(struct s_elemento numbers2[], int array_size, long int *comp, long int *trocas)
{
  int i;
  struct s_elemento s_temp;
 
  for (i = array_size - 1; i >= 0; i--)
  {
    *comp = *comp + 1;    	
    siftDown2(numbers2, i, array_size - 1, comp, trocas);
  }
 
  for (i = array_size-1; i >= 1; i--)
  {
    *comp = *comp + 1;	  
    s_temp = numbers2[0];
    numbers2[0] = numbers2[i];
    numbers2[i] = s_temp;
    *trocas = *trocas + 3;
    siftDown2(numbers2, 0, i-1, comp, trocas);
  }
}

 
int main(int argc, char *argv[])
{    int *vetor;
    struct s_elemento *vetor2; //declarado ponteiro para struct
    struct s_elemento s_chave;	
    struct timeval tinicio, tfim;
    double tdecorrido;
    int i, j, tamanho, k, chave, tipo_dado;
    char opt;
    long int comp=0, trocas=0;	

    //para geração randômica	
    long int ultime;
    time (&ultime); //Captura o valor atual de tempo. O tipo do retorno é um objeto do tipo time_t. Salva o valor na variável ultimate
    srand ((unsigned)ultime); //Inicializa o gerador randômico de números, parâmetro da função deve ser um inteiro positivo, por isso unsigned

    gettimeofday (&tinicio, NULL);
    //Parâmetro: -t -> tamanho no vetor (500, 5.000, 10.000, 30.000); -s -> é 0 ou 1, se for 0, é o vetor normal, se for 1 é com um struct em cada posição do vetor
    while ((opt = getopt (argc, argv, "sit:")) != -1) //se for -1 todos os argumentos já terão sido capturados
    { 
	comp++;
    	switch (opt) 
    	{ 
               case 't': 
		   tamanho = atoi (optarg); 	//optarg pega o valor que foi colocado no terminal para o parâmetro t, de tamanho do vetor	 
                   break; //sai do switch
               case 's': 
		   tipo_dado = 1; 		//1: vetor de structs com "tamanho elementos"; a variável chave das structs é um inteiro gerado randomicamente e os vetor de 11 posições das structs também				
   		   break;
               case 'i': 
		   tipo_dado = 0; 		//0: vetor de inteiros com "tamanho" elementos; todos os elementos são números gerados randomicamente
                   break; //sai do switch
		case '?':  //cai aqui se o paramâtro digitado for diferente de 'p'  
               	   printf ("Parâmetro digitado é inválido.\n");
		   exit(EXIT_FAILURE);
		   break; //sai do switch
               default:
               	   exit(EXIT_FAILURE); //o parâmetro inserido não é "p"
                   		       //EXIT_FAILURE: Failure termination code -> contido na biblioteca stdlib.h	
        } 
    }

    if (tipo_dado == 0)
    {	
	comp++;	
	vetor = malloc(tamanho*sizeof(int));
	for (i=0; i<tamanho; i++)	
	{
    	    vetor[i] = rand() % (tamanho+1); //gera chaves de 0 a 500  
	    comp++;
	}
        heapSort (vetor, tamanho, &comp, &trocas);
    }
    
    if (tipo_dado == 1)	
    {
	comp++;
  	vetor2 = malloc(tamanho*sizeof(struct s_elemento));
	for (i=0; i<tamanho; i++)	
        {
    	    comp++;	
    	    vetor2[i].chave = rand() % (tamanho+1); //gera chave
	    for (j=0; j<11; j++) 	 
      	    {
		comp++;	
    	        vetor2[i].v[j] = rand() % (tamanho+1); //gera vetor de 11 posições 
	    }
        }
        heapSort2 (vetor2, tamanho, &comp, &trocas);
    }

    gettimeofday (&tfim, NULL);
    tdecorrido = (double) ((tfim.tv_sec*1000000+tfim.tv_usec)-(tinicio.tv_sec*1000000+tinicio.tv_usec));
    printf ("%.lf\n", tdecorrido);    
    printf ("comp: %ld, trocas: %ld\n", comp, trocas);
    return 0; 

}


