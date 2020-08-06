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

void siftDown(int numbers[], int root, int bottom)
{
  int done, maxChild, temp;
 
  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    if (root*2 == bottom)
      maxChild = root * 2;
    else if (numbers[root * 2] > numbers[root * 2 + 1])
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
 
    if (numbers[root] < numbers[maxChild])
    {
      temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}

void heapSort(int numbers[], int array_size)
{
  int i, temp;
 
  for (i = array_size - 1; i >= 0; i--)
    siftDown(numbers, i, array_size - 1);
 
  for (i = array_size-1; i >= 1; i--)
  {
    temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    siftDown(numbers, 0, i-1);
  }
}
 
void siftDown2(struct s_elemento numbers2[], int root, int bottom)
{
  int done, maxChild;
  struct s_elemento s_temp;
 
  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    if (root*2 == bottom)
      maxChild = root * 2;
    else if (numbers2[root * 2].chave > numbers2[root * 2 + 1].chave)
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;
 
    if (numbers2[root].chave < numbers2[maxChild].chave)
    {
      s_temp = numbers2[root];
      numbers2[root] = numbers2[maxChild];
      numbers2[maxChild] = s_temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}


void heapSort2(struct s_elemento numbers2[], int array_size)
{
  int i;
  struct s_elemento s_temp;
 
  for (i = array_size - 1; i >= 0; i--)
    siftDown2(numbers2, i, array_size - 1);
 
  for (i = array_size-1; i >= 1; i--)
  {
    s_temp = numbers2[0];
    numbers2[0] = numbers2[i];
    numbers2[i] = s_temp;
    siftDown2(numbers2, 0, i-1);
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

    //para geração randômica	
    long int ultime;
    time (&ultime); //Captura o valor atual de tempo. O tipo do retorno é um objeto do tipo time_t. Salva o valor na variável ultimate
    srand ((unsigned)ultime); //Inicializa o gerador randômico de números, parâmetro da função deve ser um inteiro positivo, por isso unsigned

    gettimeofday (&tinicio, NULL);
    //Parâmetro: -t -> tamanho no vetor (500, 5.000, 10.000, 30.000); -s -> é 0 ou 1, se for 0, é o vetor normal, se for 1 é com um struct em cada posição do vetor
    while ((opt = getopt (argc, argv, "sit:")) != -1) //se for -1 todos os argumentos já terão sido capturados
    { 
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
	vetor = malloc(tamanho*sizeof(int));
	for (i=0; i<tamanho; i++)	
    	    vetor[i] = i + 1;
        heapSort (vetor, tamanho);
    }
    
    if (tipo_dado == 1)	
    {
  	vetor2 = malloc(tamanho*sizeof(struct s_elemento));
	for (i=0; i<tamanho; i++)	
        {
    	    vetor2[i].chave = i + 1;
	    for (j=0; j<11; j++) 	 
    	        vetor2[i].v[j] = rand() % (tamanho+1); //gera vetor de 11 posições 
        }
        heapSort2 (vetor2, tamanho);
    }

    gettimeofday (&tfim, NULL);
    tdecorrido = (double) ((tfim.tv_sec*1000000+tfim.tv_usec)-(tinicio.tv_sec*1000000+tinicio.tv_usec));
    printf ("%.lf\n", tdecorrido);    

    return 0; 

}


