#include "../include/fifo.h"

//inicializa Fila
TipoFila NovaFila()
{
	return NULL;
}

//insere
void InsereFila(TipoFila* Fila, TipoInfo dado)
{
	//Cria o novo no (ou "nodo")
	TipoFila Nova = (TipoFila) malloc(sizeof(TipoNo));

	Nova->info = dado;
	Nova->prox = NULL;
	
	if(*Fila != NULL) {
		TipoFila fimDaFila = FimDaFila(*Fila);
//		printf("Fim da fila - PID: %d\n", fimDaFila->info.PID);

		fimDaFila->prox = Nova; //Encadeia o novo nó no fim Fila
	} else {
		*Fila = Nova; //A Fila passa a apontar para o novo item
//		printf("Primeiro elemento - PID: %d\n", (*Fila)->info.PID);
	}
}

TipoFila FimDaFila(TipoFila Fila)
{
	if(Fila == NULL) return NULL;
	
	while(Fila->prox != NULL) {
		Fila = Fila->prox;
	}
	return Fila;
}

//remove
TipoInfo* RetiraFila(TipoFila* Fila)
{
	if(*Fila == NULL) return NULL;

	TipoFila Primeiro = *Fila;
	*Fila = (*Fila)->prox;

	return &(Primeiro->info);
}

//destroi
void DestroiFila(TipoFila* Fila)
{
	TipoFila Excluido;

	while(*Fila != NULL) {
		Excluido = *Fila; //Guarda o elemento a ser excluído 
		*Fila = Excluido->prox;
		free(Excluido);                     
	}
}
