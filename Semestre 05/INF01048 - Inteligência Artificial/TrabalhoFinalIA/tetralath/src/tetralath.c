#include "../inc/minimax.h"
#include "../inc/interface.h"
#include "../inc/round.h"
#include "../inc/board.h"

/* Global */
extern unsigned char *boardPixels;
extern Round *globalRound;
 
int main() {

	/* inicializa a interface */	
	initInterface();
	
	/* inicializa as informaões da rodada do jogo */
	globalRound = initRound();
	
	if(firstPlayer == PLAYER_PC)
		activeMinimaxForPlayerPC();

	glutMainLoop();
	
	free(boardPixels);
	free(globalRound);
			
	return 0;
} 


