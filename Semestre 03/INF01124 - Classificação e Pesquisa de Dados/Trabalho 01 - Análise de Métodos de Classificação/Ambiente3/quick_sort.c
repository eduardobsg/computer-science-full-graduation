/*
Algoritmo: quick_sort.c
Data: 03/05/2010

Rodar no terminal: 

$ ./quick_sort -i -t 5 //roda o binário insertion_sort, gerando um vetor de chaves inteiras de tamanho 5
$ ./quick_sort -s -t 5 //roda o binário insertion_sort, gerando um vetor de structs com 5 structs

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

void quickSort(int *vetor, int esq, int dir)
{
   int i, j, k;
   int pivo, troca;
  
   i=esq; j=dir;
   pivo=vetor[(esq+dir)/2];
   do 
   {
        while(vetor[i]<pivo && i<dir) i++;
        while(pivo<vetor[j] && j>esq) j--;
        if(i<=j) 
        {
          troca = vetor[i];
          vetor[i] = vetor[j];
          vetor[j] = troca;
          i++; j--;
        }
   }while(i<=j);
    
   if(esq<j) quickSort(vetor, esq, j);
   if(i<dir) quickSort(vetor, i, dir);
}

void quickSort2(struct s_elemento *vetor2, int esq, int dir)
{
   int i, j, k;
   struct s_elemento s_pivo, s_troca;
  
   i=esq; j=dir;
   s_pivo=vetor2[(esq+dir)/2];

   do 
   {
        while(vetor2[i].chave<s_pivo.chave && i<dir) i++;
        while(s_pivo.chave<vetor2[j].chave && j>esq) j--;
        if(i<=j) 
        {
          s_troca = vetor2[i];
          vetor2[i] = vetor2[j];
          vetor2[j] = s_troca;
          i++; j--;
        }
   }while(i<=j);
    
   if(esq<j) quickSort2(vetor2, esq, j);
   if(i<dir) quickSort2(vetor2, i, dir);
}

int main(int argc, char *argv[])
{    int *vetor;
    struct s_elemento *vetor2; //declarado ponteiro para struct
    struct timeval tinicio, tfim;
    double tdecorrido;
    int i, j, tamanho, k, tipo_dado;
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
    	    vetor[i] = tamanho - i;
        quickSort(vetor, 0, tamanho-1);
    }
	
    if (tipo_dado == 1)
    {
        vetor2 = malloc(tamanho*sizeof(struct s_elemento));
	for (i=0; i<tamanho; i++)	
        {
    	    vetor2[i].chave = tamanho - i;
	    for (j=0; j<11; j++) 	 
    	        vetor2[i].v[j] = rand() % (tamanho+1); //gera vetor de 11 posições 
        }
        quickSort2(vetor2, 0, tamanho-1);
    }

   
    gettimeofday (&tfim, NULL);
    tdecorrido = (double) ((tfim.tv_sec*1000000+tfim.tv_usec)-(tinicio.tv_sec*1000000+tinicio.tv_usec));
    printf ("%.lf\n", tdecorrido);    

    return 0; 
    
}
