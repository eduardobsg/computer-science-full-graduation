#include "../inc/round.h"

/* 
Descrição: 
	realiza uma série de inicializações o jogo
Variáveis Globais:
	@round: contém as informações da rodada
	@currentPlayer: jogador atual (declarado na interface.h)
Retorno:
	ponteiro para as informações da rodada
*/
Round *initRound() {
	int i;
	Round *round;

	round = (Round *) malloc(sizeof(Round));

	//inicializa o jogador branco
	round->playerWhite.color = WHITE;
	round->playerWhite.player = currentPlayer;
	for(i = 0; i < MAX_PIECES_PER_PLAYER; i++)
		round->playerWhite.markedPieces[i] = -1;
	
	//inicializa o jogador preto
	round->playerBlack.color = BLACK;
	if(currentPlayer == PLAYER_PC)
		round->playerBlack.player = PLAYER_HUMAN;
	else
		round->playerBlack.player = PLAYER_PC;
	for(i = 0; i < MAX_PIECES_PER_PLAYER; i++)
		round->playerBlack.markedPieces[i] = -1;	
	
	//indica qual é o jogador atual
	round->currentPlayer = currentPlayer;
	
	//inicializa o tabuleiro	
	round->board = createBoard();
	round->board = initializeBoard(round->board);
	
	return round;
}


/* 
Descrição: 
	atualiza o estado atual de jogo
Parâmetros:
	@round: contém as informações da rodada
	@color: cor do jogador atual
	@x, y: índices da matriz board, que indicam qual posição foi marcada
*/
void updateRoundMinimax(Round *round, int color, int x, int y) {
	int i;
	
	if(round->playerWhite.color == color) {
		//printf("Posicao (%d,%d) foi marcada com jedi.\n", x, y);
		for(i = 0; i < MAX_PIECES_PER_PLAYER; i++) {		
			if(round->playerWhite.markedPieces[i] == -1) {
				round->playerWhite.markedPieces[i] = 10*x + y;			
				break;
			}
		}

		round->board[x][y].color = WHITE;
	}
	else {
		//printf("Posicao (%d,%d) foi marcada com sith.\n", x, y);
		for(i = 0; i < MAX_PIECES_PER_PLAYER; i++) {		
			if(round->playerBlack.markedPieces[i] == -1) {
				round->playerBlack.markedPieces[i] = 10*x + y;			
				break;
			}
		}

		round->board[x][y].color = BLACK;
	}
}


void updateRound(Round *round, int color, int x, int y) {
	int i;
	
	if(round->playerWhite.color == color) {
		//printf("Posicao (%d,%d) foi marcada com jedi.\n", x, y);
		for(i = 0; i < MAX_PIECES_PER_PLAYER; i++) {		
			if(round->playerWhite.markedPieces[i] == -1) {
				round->playerWhite.markedPieces[i] = 10*x + y;			
				break;
			}
		}

		round->board[x][y].color = WHITE;
	}
	else {
		//printf("Posicao (%d,%d) foi marcada com sith.\n", x, y);
		for(i = 0; i < MAX_PIECES_PER_PLAYER; i++) {		
			if(round->playerBlack.markedPieces[i] == -1) {
				round->playerBlack.markedPieces[i] = 10*x + y;			
				break;
			}
		}

		round->board[x][y].color = BLACK;
	}
}


/*
Descrição: 
	copia a rodada e todas as informações que existem nele
Parêmetros: 
	@round: rodada a ser copiado
Retorno:
  	cópia da rodada
*/
Round *copyRound(Round *round) {
	Round *copy = NULL;
	int i, j, k;
	
	copy = (Round *) malloc(sizeof(Round));
	
	//copia as informações para o outro tabuleiro
	copy->board = createBoard();
	for(i = 0; i < BOARD_ROW; i++) {
		for(j = 0; j < BOARD_COLUMN; j++) {
			copy->board[i][j].color = round->board[i][j].color;
			
			for(k = 0; k < NEIGHBORS; k++){
				copy->board[i][j].neighbors[k] = round->board[i][j].neighbors[k];
			}
		}
  	}
	
	//copia o jogador atual
	copy->currentPlayer = round->currentPlayer;
	
	//copia as informações dos jogadores
	copy->playerWhite.color = round->playerWhite.color;
	copy->playerWhite.player = round->playerWhite.player;
	for(i = 0; i < MAX_PIECES_PER_PLAYER; i++)
		copy->playerWhite.markedPieces[i] = round->playerWhite.markedPieces[i];
	
	//inicializa o jogador preto
	copy->playerBlack.color = round->playerBlack.color;
	copy->playerBlack.player = round->playerBlack.player;
	for(i = 0; i < MAX_PIECES_PER_PLAYER; i++)
		copy->playerBlack.markedPieces[i] = round->playerBlack.markedPieces[i];	
	
  	return copy;	
}
