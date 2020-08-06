/* Test Name: t01.c
 * Description: tests the seedMinimax function, to see its results
 * Test Method: run as 
 	$ ./t01 -> out.txt
 	and look at the out.txt file
*/

#include "../inc/minimax.h"
#include "../inc/interface.h"
#include "../inc/round.h"
#include "../inc/board.h"

/* Global */
extern unsigned char *boardPixels;
extern Round *globalRound;
 
int main() {
	int x, y;
	
	/* inicializa as informaões da rodada do jogo */
	currentPlayer = PLAYER_PC;
	globalRound = initRound();
	
	//First Player: PC - WHITE
	//Second Player: Human - BLACK

	//marca primeira jogada, do jogador PC
	globalRound->currentPlayer = PLAYER_PC;	
	updateRound(globalRound, WHITE, 4, 4);
		
	//marca segunda jogada, do jogador Human	
	globalRound->currentPlayer = PLAYER_HUMAN;	
	updateRound(globalRound, BLACK, 5, 6);	
		
	seedMinimax(globalRound, 2, WHITE, &x, &y);
	printf("Minimax: IA deve jogar em (%d,%d).\n", x, y);
			
	return 0;
} 


