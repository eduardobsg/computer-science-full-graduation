/*
Algoritmo: merge_sort_re.c
Data: 03/05/2010

Rodar no terminal: 

$ ./merge_sort_re -i -t 5 //roda o binário insertion_sort, gerando um vetor de chaves inteiras de tamanho 5
$ ./merge_sort_re -s -t 5 //roda o binário insertion_sort, gerando um vetor de structs com 5 structs

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
 
void intercala(int p, int q, int r, int v[])
{
     int i, j, k, *w;
     w = malloc( (r - p) * sizeof (int) );
     i = p;
     j = q;
     k = 0;
 
     while (i < q && j < r)
     {
           if (v[i] <= v[j])
              w[k++] = v[i++];
           else
               w[k++] = v[j++];
     }
 
     while (i < q) w[k++] = v[i++];
     while (j < r) w[k++] = v[j++];
 
     for (i = p; i < r; i++)
         v[i] = w[i - p];
 
     free(w);
}

void intercala2(int p, int q, int r, struct s_elemento v2[])
{
     int i, j, k;
     struct s_elemento *w;
     w = malloc( (r - p) * sizeof (struct s_elemento) );
     i = p;
     j = q;
     k = 0;
 
     while (i < q && j < r)
     {
           if (v2[i].chave <= v2[j].chave)
              w[k++] = v2[i++];
           else
               w[k++] = v2[j++];
     }
 
     while (i < q) w[k++] = v2[i++];
     while (j < r) w[k++] = v2[j++];
 
     for (i = p; i < r; i++)
         v2[i] = w[i - p];
 
     free(w);
}
 
void ordenarMergeSort(int p, int r, int v[])
{
     if (p < r - 1)
     {
        int q = (p + r) / 2;   
        ordenarMergeSort(p, q, v); //o e 2 //
        ordenarMergeSort(q, r, v); //2 e 4 //3 4
        intercala(p, q, r, v);
     }
}

void ordenarMergeSort2(int p, int r, struct s_elemento v2[])
{
     if (p < r - 1)
     {
        int q = (p + r) / 2;   
        ordenarMergeSort2(p, q, v2); //o e 2 //
        ordenarMergeSort2(q, r, v2); //2 e 4 //3 4
        intercala2(p, q, r, v2);
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
    	    vetor[i] = rand() % (tamanho+1); //gera chaves de 0 a 500  
        ordenarMergeSort(0, tamanho, vetor);
    }

    if (tipo_dado == 1)
    {
        vetor2 = malloc(tamanho*sizeof(struct s_elemento));
	for (i=0; i<tamanho; i++)	
        {
    	    vetor2[i].chave = rand() % (tamanho+1); //gera chave
	    for (j=0; j<11; j++) 	 
    	        vetor2[i].v[j] = rand() % (tamanho+1); //gera vetor de 11 posições 
        }
        ordenarMergeSort2(0, tamanho, vetor2);
    }
	
    gettimeofday (&tfim, NULL);
    tdecorrido = (double) ((tfim.tv_sec*1000000+tfim.tv_usec)-(tinicio.tv_sec*1000000+tinicio.tv_usec));
    printf ("%.lf\n", tdecorrido);  
    return 0;
}
