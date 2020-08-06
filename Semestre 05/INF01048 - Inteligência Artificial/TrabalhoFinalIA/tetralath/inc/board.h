#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
 
//--------------------------------------------------------------------------
// Definições
//-------------------------------------------------------------------------- 
 
/* Tamanho do tabuleiro */
#define BOARD_ROW		9
#define BOARD_COLUMN	9
#define NEIGHBORS 		6 

/* Estados da variável color (estrutura Position) */
#define INVALID 		-1
#define WHITE			0
#define	BLACK			1
#define NO_COLOR 		2
 
//--------------------------------------------------------------------------
// Estruturas de dados
//--------------------------------------------------------------------------
 
/* Estrutura de dados para uma posição do tabuleiro */
typedef struct {
	int color;
	int neighbors[NEIGHBORS];
} Position;

//--------------------------------------------------------------------------
// Funções
//--------------------------------------------------------------------------
 
/* Cria tabuleiro */
Position **createBoard();
 
/* Inicializa tabuleiro */
Position **initializeBoard(Position **);

/* Retorna o id do vizinho de uma posição */
int idNeighbor(int, int);
 
/* Imprime tabuleiro */
void printfBoard(Position **);

#endif
