#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "round.h"

// -----------------------------------------------------------------------------
// Definições
// -----------------------------------------------------------------------------

#define DRAW_GAME	20
#define FOUND		9999
#define ERROR		-9999

//MAX
#define MAX_WIN		10
#define MAX_PESO1	8
#define MAX_PESO2	6
#define MAX_PESO3	4
#define MAX_PESO4	2
#define MAX_LOSS 	0
#define MINIMUM		-999

//MIN
#define MIN_WIN		0
#define MIN_PESO1	2
#define MIN_PESO2	4
#define MIN_PESO3	6
#define MIN_PESO4	8
#define MIN_LOSS 	10
#define MAXIMUM		999
 
//--------------------------------------------------------------------------
// Funções
//-------------------------------------------------------------------------- 

/* Avalia uma jogada na rodada MAX */
int evalFunctionMax(Position **, int *, int);

/* Avalia uma jogada na rodada MIN */
int evalFunctionMin(Position **, int *, int);

/* Retorna o maior valor dos dois */
int max(int, int);

/* Retorna o menor valor dos dois */
int min(int, int);

/* Analisa se a jogada é de vitória, derrota, empate ou se o jogo prossegue.
Chamada após uma peça ter sido posicionada no tabuleiro */
int evalFunction(Position **, int *, int);

/* Retorna o maior valor dos dois e atualiza as coordenadas da nova jogada */
int maxMinimax(int, int, int *, int *, int, int);

/* Vê se há ua jogada do tipo 2-vazio-1 */
int evalTwoEmptyOne(Position **, int *, int, int *, int, int *, int *);

//void firstMove(Round *);

//Dá prosseguimento ao minimax, simulando as jogadas futuras em cópias do tabuleiro.
//int expandTree(Round *, int, int, int, int, int);

//Gera a árvore do Minimax
//void seedMinimax(Round *, int, int, int, int *, int *);

#endif

