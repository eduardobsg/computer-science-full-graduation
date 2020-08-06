#ifndef ROUND_H
#define ROUND_H

#include "board.h"
#include "interface.h"

#define MAX_PIECES_PER_PLAYER 31

//--------------------------------------------------------------------------
// Estruturas de dados
//--------------------------------------------------------------------------

typedef struct {
	int color; //diz qual a cor de peça do jogador
	int player; //diz qual jogador é, humano ou PC
	int markedPieces[MAX_PIECES_PER_PLAYER]; //possui o pid da posição marcada pela peça do jogador
} Player;


typedef struct {
	int currentPlayer;
	Player playerWhite;
	Player playerBlack;	
	Position **board;
} Round;

//Cada estrutura round ocupa 4 + (2 * (4 + 4 + (31 * 4))) + (81 * (4 + (6 * 4))) = 2 536 bytes

//--------------------------------------------------------------------------
// Variáveis Globais
//--------------------------------------------------------------------------
Round *globalRound;

//--------------------------------------------------------------------------
// Funções
//--------------------------------------------------------------------------

/* Inicializa a rodada global do jogo */
Round *initRound();

/* Atualiza o tabuleiro global e o vetor de peças do jogador */
void updateRoundMinimax(Round *, int, int, int);

/*  */
void updateRound(Round *, int, int, int);

/* Copia a rodada e todas as informações que existem nele */
Round *copyRound(Round *);

#endif
