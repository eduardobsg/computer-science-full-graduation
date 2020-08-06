#include "../inc/board.h"
 
/* 	
Definiçao: 
	cria o tabuleiro
Retorno: 
	retorna um ponteiro para uma matriz bidimensional
*/
Position **createBoard() {
	Position **board = NULL;
	int i;
	
	board = (Position **) malloc(BOARD_ROW * sizeof(Position));
	for(i = 0; i < BOARD_ROW; i++)
		board[i] = (Position *) malloc(BOARD_COLUMN * sizeof(Position));
		
	return board;	
}
 
 
/*	
Definição: 
	inicializa todas as posições da matriz (tabuleiro)
Parâmetros: 
	@board: ponteiro para a matriz bidimensional do tabuleiro
Retorno: 
	retorna o tabuleiro inicializado
*/
Position **initializeBoard(Position **board) {
	int i, j, k;
	int id;
	
	for(i = 0; i < BOARD_ROW; i++) {
		for(j = 0; j < BOARD_COLUMN; j++) {
			id = i * 10 + j;

			board[i][j].color = NO_COLOR;
			for(k = 0; k < NEIGHBORS; k++) 
				board[i][j].neighbors[k] = INVALID;
			
			if(id == 0) {
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
			}
			else if(id == 1 || id == 2 || id == 3) {
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
			}
			else if(id == 4) {
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
			}
			else if( id == 10 || id == 20 || id == 30 ) { 
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
				board[i][j].neighbors[3] = idNeighbor( id, 3 );
			}
			else if( id == 40 ) {
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[3] = idNeighbor( id, 3 );
			}
			else if( id == 51 || id == 62 || id == 73 ) { 
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[3] = idNeighbor( id, 3 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );
			}
			else if( (id >= 11 && id <= 14) ||
				(id >= 21 && id <= 25) || 
				(id >= 31 && id <= 36) || 
				(id >= 41 && id <= 47) ||
				(id >= 52 && id <= 57) ||
				(id >= 63 && id <= 67) ||
				(id >= 74 && id <= 77) ) {
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
				board[i][j].neighbors[3] = idNeighbor( id, 3 );	
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );	
			}
			else if( id == 15 || id == 26 || id == 37 ) {
				board[i][j].neighbors[0] = idNeighbor( id, 0 );
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );
			}
			else if( id == 48 ) {
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );
			}
			else if( id == 58 || id == 68 || id == 78 ) {
				board[i][j].neighbors[2] = idNeighbor( id, 2 );
				board[i][j].neighbors[3] = idNeighbor( id, 3 );
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );
			}
			else if( id == 84 ) {
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[3] = idNeighbor( id, 3 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );
			}
			else if( id == 85 || id == 86 || id == 87 ) {
				board[i][j].neighbors[1] = idNeighbor( id, 1 );
				board[i][j].neighbors[3] = idNeighbor( id, 3 );
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );
			}
			else if( id == 88 ) {
				board[i][j].neighbors[3] = idNeighbor( id, 3 );
				board[i][j].neighbors[4] = idNeighbor( id, 4 );
				board[i][j].neighbors[5] = idNeighbor( id, 5 );
			}
			else {
				board[i][j].color = INVALID;
			}
			
		}
	}
	
	return board;
}


/*	
Definição: 
	Dado o id de uma posição do board e o id da 
	posição de um vizinho dentro do vetor de vizinhos desta posição, 
	retorna o id corresponde ao vizinhos no board.
Parâmetros: 
	@idPosition: id da posicao do board 
	@idVectorNeighbors: id dentro do vetor de vizinhos desta posicao
Retorno: 
	id do vizinho
*/
int idNeighbor(int idPosition, int idVectorNeighbors) {
	
	if(idVectorNeighbors == 0) {
		return idPosition + 11; //i++, j++
	} else if(idVectorNeighbors == 1) {
		return idPosition + 1; //j++
	} else if(idVectorNeighbors == 2) {
		return idPosition + 10; //i++
	} else if(idVectorNeighbors == 3) {
		return idPosition - 10; //i--
	} else if(idVectorNeighbors == 4) {
		return idPosition - 1; //j--
	} else if(idVectorNeighbors == 5) {
		return idPosition - 11; //i--, j--
	}
	
	return -1;
}
 
 
/* 	
Definição: 
	imprime o board criado, variáveis marcado, cor 
	e o id dos vizinhoss
Parâmetros: 
	@board: ponteiro para a matriz bidimensional do board
*/
void printBoard(Position **board) {
	int i, j, k, id;
	
	printf("\n>> Tabuleiro <<\n");
	for(i = 0; i < BOARD_ROW; i++) {
		for(j = 0; j < BOARD_COLUMN; j++) {
			if(board[i][j].color == INVALID) {
				printf("Posicao (%d,%d) eh INVALIDA.\n", i, j);			
			}
			else {
				printf("Posicao (%d,%d) eh VALIDA.\n", i, j);				
				if(board[i][j].color == BLACK) 
					printf("\tcor: preto.\n");	
				else if(board[i][j].color == WHITE) 	
					printf("\tcor: branco.\n");
				else
					printf("\tcor: sem cor.\n");

				printf("\tvizinhos: ");	
				for(k = 0; k < NEIGHBORS; k++) {
					id = board[i][j].neighbors[k];
					if(id != -1)
						printf("%d:(%d,%d); ", k, (int)id/10, id%10);
				}		
				printf("\b\n");
			}
				
		}
	}
	
}








