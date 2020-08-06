#include "../inc/interface.h"

// -----------------------------------------------------------------------------
// Funções
// -----------------------------------------------------------------------------


/*
Descrição: 
	realiza uma série de inicializações para o jogo. Inicializa variáveis
	globais (imagem do tabuleiro) e a glut
Parâmetros:
	@filename: nome da imagem do tabuleiro
Variáveis Globais:
	@boardPixels, @boardImg: para carregar a imagem do tabuleiro
	@piecePixels, @pieceImg: para carregar as imagens das peças
	@piecesPlayer: vetores que contém as peças que cada jogador colocou no tabuleiro
	@player: jogador atual
*/
void initInterface() {
	int i, j;
	
	//inicializa as listas globais de peças
	piecesPlayer[PLAYER_HUMAN] = NULL;
	piecesPlayer[PLAYER_PC] = NULL;
	
	//escolhe o primeiro jogador
	do {
		printf("Escolha o primeiro jogador:\n");
		printf("\t(0) Humano.\n");
		printf("\t(1) PC.\n");
		printf("Escolha: ");
		scanf("%d", &currentPlayer);
		
		if(currentPlayer < 0 || currentPlayer > 1)
			fprintf(stderr, "Entrada invalida.\n");
	} while(currentPlayer < 0 || currentPlayer > 1);
	firstPlayer = currentPlayer;

	//inicializa o ponteiro para o vetor de pixels da imagem do tabuleiro
	boardPixels = loadImage( "res/tabuleiro2.jpg", &boardImg, BOARD );
	
	//inicializa a imagem das peças de acordo com o jogador
	piecePixels[currentPlayer] = loadImage( "res/jedi.jpg", &pieceImg[currentPlayer], currentPlayer );
	if(currentPlayer == PLAYER_PC)
		piecePixels[PLAYER_HUMAN] = loadImage( "res/sith.jpg", &pieceImg[PLAYER_HUMAN], PLAYER_HUMAN );
	else
		piecePixels[PLAYER_PC] = loadImage( "res/sith.jpg", &pieceImg[PLAYER_PC], PLAYER_PC );

	//seta a glut
	setGlut();

	//espelha a imagem veticalmente, para que ela não fique de cabeça para baixo
	verticalFlip(boardPixels, BOARD);
	verticalFlip(piecePixels[PLAYER_HUMAN], PLAYER_HUMAN);
	verticalFlip(piecePixels[PLAYER_PC], PLAYER_PC);	

	//inicializa a matriz de peças marcadas (para a interface)
	for(i = 0; i < BOARD_ROW; i++)
		for(j = 0; j < BOARD_COLUMN; j++)
			markedPieces[i][j] = 0;		
			
	//inicializa o estado do jogo
	gameState = GAME_RUNNING;		
}


/* 
Descrição: 
	carrega uma imagem
Parameters:
	@filename: nome do arquivo que se quer carregar
	@img: ponteiro de ponteiros do tipo IplImage. Usado para armazenar 
	informações da imagem	
	@object: número da imagem que estamos trabalhando
Variável Globais:
	@width, @height, @channel: informações da imagem
Return0: 
	retorna o campo  imageData da estrutura IplImage, que representa as
	informações da imagem
*/
unsigned char* loadImage( char* filename, IplImage** img, int object ) {
	
	//estrutura de dados para a imagem
	*img = NULL;

	//carrega a imagem
	*img = cvLoadImage(filename, CV_LOAD_IMAGE_COLOR);

	if( *img == NULL ) {
		fprintf( stderr, "Cannot load file %s!\n", filename );
		exit(1);
	}

	//Informações da imagem
	width[object] = (*img)->width;
	height[object] = (*img)->height;
	channel[object] = (*img)->nChannels;
	
	/* o campo imageData da estrutura IplImg contem os pixels da imagem
	em um ponteiro unsigned char */
	return (unsigned char*)(*img)->imageData;
}


/*
Descrição:
	espelha a imagem no eixo y (verticalmente)
Parâmetros:
	@imagePixels: vetor de pixels da imagem
	@object: número da imagem que estamos trabalhando
variáveis Globais:
	@boardPixels: ponteiro que represeta a imagem do tabuleiro
	@width, @height, @channel: informações da imagem
*/
void verticalFlip(unsigned char *imagePixels, int object) {

	unsigned char *auxPixels;
	int i;
	
	//aloca memória para a representação auxilixar dos pixels
	auxPixels = (unsigned char *) malloc(width[object] * height[object] * channel[object] * sizeof(unsigned char));
	
	if( auxPixels ) {
		for( i = 0; i < height[object]; i++ ) 
			memcpy( auxPixels + (i * width[object] * channel[object]), 
					imagePixels + ((height[object] - 1) * width[object] * channel[object]) - (i * width[object] * channel[object]), 
					width[object] * channel[object] );
	}
	
	//copia o conteúdo de auxPixels para boardPixels
	memcpy( imagePixels, auxPixels, width[object] * height[object] * channel[object] );

	free( auxPixels );

	glutPostRedisplay();
}


// -----------------------------------------------------------------------------
// Funções da GLUT
// -----------------------------------------------------------------------------

/*
Descrição:
	rotina de tratamento de evento, altera o tamanho da janela
Parâmetros:
	@width, @height: resolução da tela
*/
void reshape(int width, int height) { 
	glViewport( 0, 0, (GLsizei) width, (GLsizei) height ); 
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	gluOrtho2D( 0.0, width, 0.0, height ); 
	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity(); 
}



/*
Descrição:
	rotina de tratamento de evento, desenha a imagem na janela
Variáveis Globais:
	@width, @height: resolução da tela
	@boardPixels: ponteiro para representar a imagem do tabuleiro
	@piecesPlayerHuman: vetor de pares ordenados das peças pretas
	@piecesPlayerPC: vetor de pares ordenados das peças brancas
*/
void display() { 
	Par *paux;
	
	glClear( GL_COLOR_BUFFER_BIT ); 
	glRasterPos2i( 0, 0 ); 
	glDrawPixels( width[BOARD], height[BOARD], GL_BGR, GL_UNSIGNED_BYTE, boardPixels ); 

	//desenha as peças do jogador humano
	if(piecesPlayer[PLAYER_HUMAN] != NULL) {
		for(paux = piecesPlayer[PLAYER_HUMAN]; paux != NULL; paux = paux->nextPar) {
			drawPiece(paux, PLAYER_HUMAN);
		}
	}
	
	//desenha as peças do jogador PC
	if(piecesPlayer[PLAYER_PC] != NULL) {
		for(paux = piecesPlayer[PLAYER_PC]; paux != NULL; paux = paux->nextPar)
			drawPiece(paux, PLAYER_PC);
	}
	
	//desenha o texto que qual jogador deve jogar
	drawPlayerText();
	glutSwapBuffers();

	//testa se o jogo terminou
	if(gameState == GAME_END) {
		printf("ENTER para terminar.\n");
		getchar(); getchar(); getchar(); exit(0);
	}
}


/*
Descrição:
	inicializa a GLUT na forma padrão
Variáveis Globais:
	@width, @height: resolução da tela
	@windows: manipulador de janelas da glut
*/
void setGlut() {
	
	/* aux and aux2 are passed to glutInit to make it initialize 
	glut in default way */
	char *aux = NULL; int aux2 = 1;
	glutInit( &aux2, &aux );

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(0, 0); 
	glutInitWindowSize(width[BOARD], height[BOARD]); 
	windows[MAIN] = glutCreateWindow("Tetralath"); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutMouseFunc(mouse);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
}


/*
Descrição:
	inicializa a GLUT na forma padrão
Parâmetros:
	@par: coordenadas para impressão da peça
	@player: diz qual o jogador (máquina/branco ou humano/preto)
*/
void drawPiece(Par *par, int player) {

	//setando posição de origem para começar a desenhar	
	glRasterPos2i(par->x, par->y);

	//desenha os pixels na tela
	glDrawPixels( width[player], height[player], GL_BGR, GL_UNSIGNED_BYTE, piecePixels[player] ); 
}


/*
Descrição:
	desenha na tela a peça do jogador atual e o nome do jogador atual
	http://stackoverflow.com/questions/538661/how-do-i-draw-text-with-glut-opengl-in-c
Variáveis Globais:
	@height, @width: dimensões da imagem da peça e do tabuleiro
	@player: jogador atual
*/
void drawPlayerText() {
	char output[100];

	//setando posição de origem para começar a desenhar	
	glRasterPos2i(10, height[BOARD] - height[currentPlayer] - 5);

	//desenha os pixels na tela
	glDrawPixels( width[currentPlayer], height[currentPlayer], GL_BGR, GL_UNSIGNED_BYTE, piecePixels[currentPlayer] ); 
	
	//desenha o texto
  	glColor3f(0.0f, 0.0f, 0.0f); 
	glRasterPos2i(20 + width[currentPlayer], height[BOARD] - height[currentPlayer]/2 - 10);

	if(currentPlayer == PLAYER_HUMAN)
	  	glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Player Human");		
	else {
		memset(output, '\0', 100);
		sprintf(output, "Player PC: jogar em (%d,%d)", x, y);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, output);	
	}
}




/*
Descrição:
	ajusta as coordenadas de centro de uma posição para imprimir a 
	peça nesta posição
Parâmetros:
	@x, @y: coordenadas do centro da posição	
Variáveis Globais:
	@height[BOARD]: tamanho vertical da janela
Retorno: 
	variável do tipo Par, como o par ordenado ajustado
	
Coordenadas de tela que a glDrawPixels vê (x,y): 
(0,4)	(1,4)	(2,4)	(3,4)	(4,4)
(0,3)	(1,3)	(2,3)	(3,3)	(4,3)
(0,2)	(1,2)	(2,2)	(3,2)	(4,2)
(0,1)	(1,1)	(2,1)	(3,1)	(4,1)
(0,0)	(1,0)	(2,0)	(3,0)	(4,0)

Coordenadas de tela que o clique do mouse vê (x,y):
(0,0)	(1,0)	(2,0)	(3,0)	(4,0)
(0,1)	(1,1)	(2,1)	(3,1)	(4,1)
(0,2)	(1,2)	(2,2)	(3,2)	(4,2)
(0,3)	(1,3)	(2,3)	(3,3)	(4,3)
(0,4)	(1,4)	(2,4)	(3,4)	(4,4)

Então, dado (x,y) em coordenadas do clique do mouse, deveos transformar
para as coordenadas da glDrawPixels:

x = x;
y = maxY - y;

Agora temos nosso par ordenado em coordenadas da glDrawPixels. Mas ainda é 
preciso fazer uma nova manipulação, pois para a glDrawPixels, esse par é o 
par de início de desenho. Não queremos começar a desenhar a peça do centro
de uma posição do tabuleiro em diante, então é preciso pegar o par (x,y)
da borda inferior esquerda da posição do tabuleiro, para que a glDrawPixels
consiga desenhar a peça sobre a posição.	
*/
Par ajustPositionCoordinates(int x, int y) {
	Par par;

	//Ajustando as coordanadas para a impressão	
	par.x = x - PIECE_OFFSET;
	par.y = height[BOARD] - y - PIECE_OFFSET;
	
	return par;
}


/*
Descrição:
	insere um novo par de coordenadas na lista de peças
Parâmetros:
	@par: coordenadas para inserir na lista
	@piecesPlayerX: lista de coordenadas de peças de um player
Retorno: 
	um ponteiro para o início da lista de coordenadas de peças
*/
Par *insertPar(Par par, Par *piecesPlayerX) {

	Par *piecesAux = piecesPlayerX;
	Par *newPiece;
	
	if(piecesPlayerX == NULL) {
		//O primeiro elemento da lista ainda é vazio
		piecesPlayerX = (Par *) malloc(sizeof(Par));
		piecesPlayerX->x = par.x;
		piecesPlayerX->y = par.y;
		piecesPlayerX->nextPar = NULL; 	
	}
	else {
		//Inicializa a nova peça
		newPiece = (Par *) malloc(sizeof(Par)); 	
		newPiece->x = par.x;
		newPiece->y = par.y;
		newPiece->nextPar = NULL;
	
		//Procura o final da lista
		while(piecesAux->nextPar != NULL) {
			piecesAux = piecesAux->nextPar;
		}			
		
		//Nova peça adicionada à lista
		piecesAux->nextPar = newPiece;
	}
	
	return piecesPlayerX;
}


/*
Descrição:
	troca o jogador. esta função é chamada dentro da função 
	ajustPositionCoordinates, pois assim garantimos o jogador irá
	trocar apenas se o clique foi válido (selecionar uma posição)
Variáveis Globais:
	@player: jogador atual
*/
void changePlayer() {

	if(currentPlayer == PLAYER_HUMAN) {
		currentPlayer = PLAYER_PC;
		//printf("currentPlayer: Player_pc\n");
	}
	else {
		currentPlayer = PLAYER_HUMAN;
		//printf("currentPlayer: Player_human\n");
	}
}


/*
Descrição:
	imprime a lista de coordenadas de peças de um jogador
Parâmetros:
	@piecesPlayerX: lista de coordenadas de peças de um player
*/
void printPieceList(Par *piecesPlayerX) {

	Par *piecesAux = piecesPlayerX;
	int i;	
		
	i = 0;	
	while(piecesAux != NULL) {
		printf("Elemento %d:\n", i);
		printf("\tx: %d\n", piecesAux->x);
		printf("\ty: %d\n", piecesAux->y);
	
		piecesAux = piecesAux->nextPar;
		i++;
	}	
}


/*
Descrição:
	rotina de tratamento de evento, captura o clique do mouse
Parâmetros:
	@button: botão do mouse que foi clicado (direito ou esquerdo)
	@state: estado do botão do mouse, se está clicado ou não
	@x, y: coordenadas do clique
Variáveis Globais:
	@player: jogador atual
*/
void mouse(int button, int state, int x, int y) {
	int iniCount, finalCount; //para contar se alguma posição foi marcada	
	int color;

	//só deixa o jogador humano ter posições marcadas pelo clique do mouse
	if(currentPlayer != PLAYER_HUMAN)
		return;

	//quantidade de peças marcadas inicial
	iniCount = countZeros(markedPieces);
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
	
		if(globalRound->playerWhite.player == currentPlayer)
			color = WHITE;
		else
			color = BLACK;
	
		//printf("(x:%d, y:%d)\n", x, y);
		if(BETWEEN(y, 30, 230)) { //up
			if(BETWEEN(x, 35, 255)) { //left
				/* Peças deste quadrante
						 (0,0) (0,1) (0,2)
					  (1,0) (1,1) (1,2)
				   (2,0) (2,1) (2,2) (2,3)	
				(3,0) (3,1) (3,2) (3,3)
				*/
				if(IN(x, y, POSITION_X_INI + 4*POSITION_X_OFFSET, POSITION_Y_INI) && !markedPieces[0][0]) { //(0,0)
					markedPieces[0][0] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 4*POSITION_X_OFFSET, 
												POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 0, 0);
				}
				else if(IN(x, y, POSITION_X_INI + 6*POSITION_X_OFFSET, POSITION_Y_INI) && !markedPieces[0][1]) { //(0,1)
					markedPieces[0][1] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 6*POSITION_X_OFFSET, 
												POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 0, 1);
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI) && !markedPieces[0][2]) { //(0,2)
					markedPieces[0][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET, 
												POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 0, 2);
				}
				else if(IN(x, y, POSITION_X_INI + 3*POSITION_X_OFFSET, POSITION_Y_INI + POSITION_Y_OFFSET) && !markedPieces[1][0]) { //(1,0)
					markedPieces[1][0] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 3*POSITION_X_OFFSET, 
												POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 1, 0);
				}
				else if(IN(x, y, POSITION_X_INI + 5*POSITION_X_OFFSET, POSITION_Y_INI + POSITION_Y_OFFSET) && !markedPieces[1][1]) { //(1,1)
					markedPieces[1][1] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 5*POSITION_X_OFFSET, 
												POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 1, 1);
				}
				else if(IN(x, y, POSITION_X_INI + 7*POSITION_X_OFFSET, POSITION_Y_INI + POSITION_Y_OFFSET) && !markedPieces[1][2]) { //(1,2)
					markedPieces[1][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 7*POSITION_X_OFFSET, 
												POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 1, 2);
				}
				else if(IN(x, y, POSITION_X_INI + 2*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][0]) { //(2,0)
					markedPieces[2][0] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 2*POSITION_X_OFFSET, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 2, 0);
				}
				else if(IN(x, y, POSITION_X_INI + 4*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][1]) { //(2,1)
					markedPieces[2][1] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 4*POSITION_X_OFFSET, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 2, 1);
				}
				else if(IN(x, y, POSITION_X_INI + 6*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][2]) { //(2,2)
					markedPieces[2][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 6*POSITION_X_OFFSET, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
					updateRound(globalRound, color, 2, 2);
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][3]) { //(2,3)
					markedPieces[2][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);						
					updateRound(globalRound, color, 2, 3);
				}
				else if(IN(x, y, POSITION_X_INI + POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][0]) { //(3,0)
					markedPieces[3][0] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + POSITION_X_OFFSET, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 3, 0);
				}
				else if(IN(x, y, POSITION_X_INI + 3*POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][1]) { //(3,1)
					markedPieces[3][1] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 3*POSITION_X_OFFSET, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 3, 1);
				}
				else if(IN(x, y, POSITION_X_INI + 5*POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][2]) { //(3,2)
					markedPieces[3][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 5*POSITION_X_OFFSET, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
					updateRound(globalRound, color, 3, 2);
				}
				else if(IN(x, y, POSITION_X_INI + 7*POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][3]) { //(3,3)
					markedPieces[3][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 7*POSITION_X_OFFSET, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);														
					updateRound(globalRound, color, 3, 3);
				}
			}
			if(BETWEEN(x, 256, 500)) { //right
				/* Peças deste quadrante
				(0,2) (0,3) (0,4)
				   (1,3) (1,4) (1,5)
				(2,3) (2,4) (2,5) (2,6) 	
				   (3,4) (3,5) (3,6) (3,7)
				*/
				if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI) && !markedPieces[0][2]) { //(0,2)
					markedPieces[0][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET, 
												POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 0, 2);
				}
				else if(IN(x, y, POSITION_X_INI + 10*POSITION_X_OFFSET, POSITION_Y_INI) && !markedPieces[0][3]) { //(0,3)
					markedPieces[0][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 10*POSITION_X_OFFSET - POSITION_X_AJUST, 
												POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 0, 3);
				}
				else if(IN(x, y, POSITION_X_INI + 12*POSITION_X_OFFSET, POSITION_Y_INI) && !markedPieces[0][4]) { //(0,4)
					markedPieces[0][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 12*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 0, 4);
				}
				else if(IN(x, y, POSITION_X_INI + 9*POSITION_X_OFFSET, POSITION_Y_INI + POSITION_Y_OFFSET) && !markedPieces[1][3]) { //(1,3)
					markedPieces[1][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 9*POSITION_X_OFFSET, 
												POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 1, 3);
				}
				else if(IN(x, y, POSITION_X_INI + 11*POSITION_X_OFFSET, POSITION_Y_INI + POSITION_Y_OFFSET) && !markedPieces[1][4]) { //(1,4)
					markedPieces[1][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 11*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 1, 4);
				}
				else if(IN(x, y, POSITION_X_INI + 13*POSITION_X_OFFSET, POSITION_Y_INI + POSITION_Y_OFFSET) && !markedPieces[1][5]) { //(1,5)
					markedPieces[1][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 13*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
					updateRound(globalRound, color, 1, 5);
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][3]) { //(2,3)
					markedPieces[2][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);						
					updateRound(globalRound, color, 2, 3);
				}
				else if(IN(x, y, POSITION_X_INI + 10*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][4]) { //(2,4)
					markedPieces[2][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 10*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 2, 4);
				}
				else if(IN(x, y, POSITION_X_INI + 12*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][5]) { //(2,5)
					markedPieces[2][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 12*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 2, 5);
				}
				else if(IN(x, y, POSITION_X_INI + 14*POSITION_X_OFFSET, POSITION_Y_INI + 2*POSITION_Y_OFFSET) && !markedPieces[2][6]) { //(2,6)
					markedPieces[2][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 14*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
					updateRound(globalRound, color, 2, 6);
				}
				else if(IN(x, y, POSITION_X_INI + 9*POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][4]) { //(3,4)
					markedPieces[3][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 9*POSITION_X_OFFSET - POSITION_X_AJUST, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 3, 4);
				}
				else if(IN(x, y, POSITION_X_INI + 11*POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][5]) { //(3,5)
					markedPieces[3][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 11*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 3, 5);
				}
				else if(IN(x, y, POSITION_X_INI + 13*POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][6]) { //(3,6)
					markedPieces[3][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 13*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 3, 6);
				}
				else if(IN(x, y, POSITION_X_INI + 15*POSITION_X_OFFSET, POSITION_Y_INI + 3*POSITION_Y_OFFSET) && !markedPieces[3][7]) { //(3,7)
					markedPieces[3][7] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 15*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	


					updateRound(globalRound, color, 3, 7);	
				}
			}
		}
		else if(BETWEEN(y, 235, 480)) { //down
			if(BETWEEN(x, 35, 255)) { //left
				/* Peças deste quadrante
				(4,0) (4,1) (4,2) (4,3) (4,4)
				   (5,1) (5,2) (5,3) (5,4)	

					  (6,2) (6,3) (6,4) (6,5)
						 (7,3) (7,4) (7,5)
							(8,4) (8,5) (8,6)
				*/
				if(IN(x, y, POSITION_X_INI, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][0]) { //(4,0)
					markedPieces[4][0] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 0);	
				}
				else if(IN(x, y, POSITION_X_INI + 2*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][1]) { //(4,1)
					markedPieces[4][1] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 2*POSITION_X_OFFSET, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 1);	
				}
				else if(IN(x, y, POSITION_X_INI + 4*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][2]) { //(4,2)
					markedPieces[4][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 4*POSITION_X_OFFSET, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 2);	
				}
				else if(IN(x, y, POSITION_X_INI + 6*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][3]) { //(4,3)
					markedPieces[4][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 6*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 3);	
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][4]) { //(4,4)
					markedPieces[4][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 4);	
				}
				else if(IN(x, y, POSITION_X_INI + POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][1]) { //(5,1)
					markedPieces[5][1] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + POSITION_X_OFFSET, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 5, 1);	
				}
				else if(IN(x, y, POSITION_X_INI + 3*POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][2]) { //(5,2)
					markedPieces[5][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 3*POSITION_X_OFFSET, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 5, 2);	
				}
				else if(IN(x, y, POSITION_X_INI + 5*POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][3]) { //(5,3)
					markedPieces[5][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 5*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 5, 3);	
				}
				else if(IN(x, y, POSITION_X_INI + 7*POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][4]) { //(5,4)
					markedPieces[5][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 7*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);											
					updateRound(globalRound, color, 5, 4);	
				}
				else if(IN(x, y, POSITION_X_INI + 2*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][2]) { //(6,2)
					markedPieces[6][2] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 2*POSITION_X_OFFSET - POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 6, 2);	
				}
				else if(IN(x, y, POSITION_X_INI + 4*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][3]) { //(6,3)
					markedPieces[6][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 4*POSITION_X_OFFSET - POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 6, 3);	
				}
				else if(IN(x, y, POSITION_X_INI + 6*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][4]) { //(6,4)
					markedPieces[6][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 6*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);		
					updateRound(globalRound, color, 6, 4);	
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][5]) { //(6,5)
					markedPieces[6][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 6, 5);	
				}
				else if(IN(x, y, POSITION_X_INI + 3*POSITION_X_OFFSET, POSITION_Y_INI + 7*POSITION_Y_OFFSET) && !markedPieces[7][3]) { //(7,3)
					markedPieces[7][3] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 3*POSITION_X_OFFSET - POSITION_X_AJUST, 
												POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);			
					updateRound(globalRound, color, 7, 3);	
				}								
				else if(IN(x, y, POSITION_X_INI + 5*POSITION_X_OFFSET, POSITION_Y_INI + 7*POSITION_Y_OFFSET) && !markedPieces[7][4]) { //(7,4)
					markedPieces[7][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 5*POSITION_X_OFFSET - POSITION_X_AJUST, 
												POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 7, 4);	
				}
				else if(IN(x, y, POSITION_X_INI + 7*POSITION_X_OFFSET, POSITION_Y_INI + 7*POSITION_Y_OFFSET) && !markedPieces[7][5]) { //(7,5)
					markedPieces[7][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 7*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 7, 5);	
				}
				else if(IN(x, y, POSITION_X_INI + 4*POSITION_X_OFFSET, POSITION_Y_INI + 8*POSITION_Y_OFFSET) && !markedPieces[8][4]) { //(8,4)
					markedPieces[8][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 4*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 8, 4);	
				}
				else if(IN(x, y, POSITION_X_INI + 6*POSITION_X_OFFSET, POSITION_Y_INI + 8*POSITION_Y_OFFSET) && !markedPieces[8][5]) { //(8,5)
					markedPieces[8][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 6*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);	
					updateRound(globalRound, color, 8, 5);	
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 8*POSITION_Y_OFFSET) && !markedPieces[8][6]) { //(8,6)
					markedPieces[8][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);																			
					updateRound(globalRound, color, 8, 6);	
				}
			}
			if(BETWEEN(x, 256, 500)) { //right
				/* Peças deste quadrante
				(4,4) (4,5) (4,6) (4,7) (4,8)
				   (5,5) (5,6) (5,7) (5,8)
				(6,5) (6,6) (6,7) (6,8) 	
				   (7,6) (7,7) (7,8)
				(8,6) (8,7) (8,8)   
				*/
				if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][4]) { //(4,4)
					markedPieces[4][4] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 4);	
				}
				else if(IN(x, y, POSITION_X_INI + 10*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][5]) { //(4,5)
					markedPieces[4][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 10*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 5);	
				}
				else if(IN(x, y, POSITION_X_INI + 12*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][6]) { //(4,6)
					markedPieces[4][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 12*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 6);	
				}
				else if(IN(x, y, POSITION_X_INI + 14*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][7]) { //(4,7)
					markedPieces[4][7] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 14*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 7);	
				}
				else if(IN(x, y, POSITION_X_INI + 16*POSITION_X_OFFSET, POSITION_Y_INI + 4*POSITION_Y_OFFSET) && !markedPieces[4][8]) { //(4,8)
					markedPieces[4][8] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 16*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 4, 8);	
				}
				else if(IN(x, y, POSITION_X_INI + 9*POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][5]) { //(5,5)
					markedPieces[5][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 9*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 5, 5);	
				}
				else if(IN(x, y, POSITION_X_INI + 11*POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][6]) { //(5,6)
					markedPieces[5][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 11*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 5, 6);	
				}
				else if(IN(x, y, POSITION_X_INI + 13*POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][7]) { //(5,7)
					markedPieces[5][7] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 13*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 5, 7);	
				}
				else if(IN(x, y, POSITION_X_INI + 15*POSITION_X_OFFSET, POSITION_Y_INI + 5*POSITION_Y_OFFSET) && !markedPieces[5][8]) { //(5,8)
					markedPieces[5][8] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 15*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);											
					updateRound(globalRound, color, 5, 8);	
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][5]) { //(6,5)
					markedPieces[6][5] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 6, 5);	
				}
				else if(IN(x, y, POSITION_X_INI + 10*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][6]) { //(6,6)
					markedPieces[6][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 10*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 6, 6);	
				}
				else if(IN(x, y, POSITION_X_INI + 12*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][7]) { //(6,7)
					markedPieces[6][7] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 12*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);		
					updateRound(globalRound, color, 6, 7);	
				}
				else if(IN(x, y, POSITION_X_INI + 14*POSITION_X_OFFSET, POSITION_Y_INI + 6*POSITION_Y_OFFSET) && !markedPieces[6][8]) { //(6,8)
					markedPieces[6][8] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 14*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 6, 8);
				}
				else if(IN(x, y, POSITION_X_INI + 9*POSITION_X_OFFSET, POSITION_Y_INI + 7*POSITION_Y_OFFSET) && !markedPieces[7][6]) { //(7,6)
					markedPieces[7][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 9*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);											
					updateRound(globalRound, color, 7, 6);
				}
				else if(IN(x, y, POSITION_X_INI + 11*POSITION_X_OFFSET, POSITION_Y_INI + 7*POSITION_Y_OFFSET) && !markedPieces[7][7]) { //(7,7)
					markedPieces[7][7] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 11*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 7, 7);
				}
				else if(IN(x, y, POSITION_X_INI + 13*POSITION_X_OFFSET, POSITION_Y_INI + 7*POSITION_Y_OFFSET) && !markedPieces[7][8]) { //(7,8)
					markedPieces[7][8] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 13*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 7, 8);
				}
				else if(IN(x, y, POSITION_X_INI + 8*POSITION_X_OFFSET, POSITION_Y_INI + 8*POSITION_Y_OFFSET) && !markedPieces[8][6]) { //(8,6)
					markedPieces[8][6] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 8*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
					updateRound(globalRound, color, 8, 6);
				}
				else if(IN(x, y, POSITION_X_INI + 10*POSITION_X_OFFSET, POSITION_Y_INI + 8*POSITION_Y_OFFSET) && !markedPieces[8][7]) { //(8,7)
					markedPieces[8][7] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 10*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);	
					updateRound(globalRound, color, 8, 7);
				}
				else if(IN(x, y, POSITION_X_INI + 12*POSITION_X_OFFSET, POSITION_Y_INI + 8*POSITION_Y_OFFSET) && !markedPieces[8][8]) { //(8,8)
					markedPieces[8][8] = 1;
					piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 12*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);		
					updateRound(globalRound, color, 8, 8);
				}
			}
		}
	}	

	finalCount = countZeros(markedPieces);
	if(finalCount < iniCount) {
		checkFinalGame(finalCount);		
		changePlayer();
		activeMinimaxForPlayerPC();
	}

	glutPostRedisplay();
}


/*
Descrição:
	Testa se o jogo chegou ao fim.		
Variáveis Globais:
	@gameState: indica se o jogo chegou ao fim ou não.	
*/
void checkFinalGame(int finalCount) {
	int gameResult;
	char playerIA[10] = {"IA"};
	char playerHuman[10] = {"Humano"};

	gameResult = evalFunction(globalRound->board, globalRound->playerWhite.markedPieces, WHITE);
	if(gameResult == MAX_WIN && globalRound->playerWhite.player == PLAYER_PC) {
		printf("%s ganhou.\n", playerIA);
		gameState = GAME_END;
	}
	else if(gameResult == MAX_LOSS && globalRound->playerWhite.player == PLAYER_PC) {
		printf("%s ganhou.\n", playerHuman);
		gameState = GAME_END;
	}
	else if(gameResult == MAX_WIN && globalRound->playerWhite.player == PLAYER_HUMAN) {
		printf("%s ganhou.\n", playerHuman);
		gameState = GAME_END;
	}
	else if(gameResult == MAX_LOSS && globalRound->playerWhite.player == PLAYER_HUMAN) {
		printf("%s ganhou.\n", playerIA);
		gameState = GAME_END;
	}

	gameResult = evalFunction(globalRound->board, globalRound->playerBlack.markedPieces, BLACK);
	if(gameResult == MAX_WIN && globalRound->playerBlack.player == PLAYER_PC) {
		printf("%s ganhou.\n", playerIA);
		gameState = GAME_END;
	}
	else if(gameResult == MAX_LOSS && globalRound->playerBlack.player == PLAYER_PC) {
		printf("%s ganhou.\n", playerHuman);
		gameState = GAME_END;
	}
	else if(gameResult == MAX_WIN && globalRound->playerBlack.player == PLAYER_HUMAN) {
		printf("%s ganhou.\n", playerHuman);
		gameState = GAME_END;
	}
	else if(gameResult == MAX_LOSS && globalRound->playerBlack.player == PLAYER_HUMAN) {
		printf("%s ganhou.\n", playerIA);
		gameState = GAME_END;
	}
}


/*
Descrição:
	Marca a jogada da IA no tabuleiro, dados os índices da posição.
Parâmetros:
	@x, y: índices da posição na matriz do tabuleiro.
	@color: cor da peça da IA.
Variáveis Globais:
	@markedPieces: matriz que indica quais as posições do tabuleiro estão marcadas.
	@globalRound: estrutura da rodada do jogo
	@currentPlayer: jogador atual
	@piecesPlayer: matriz com uma lista de pares de coordenadas para desenhar as peças
	de cada jogador.
*/
void markIAMove(int x, int y, int color) {
	int finalCount;

	markedPieces[x][y] = 1;
	
	if(x == 0) {
		if(y == 0) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 4*POSITION_X_OFFSET, 
											POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 0, 0);
		}
		else if(y == 1) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 6*POSITION_X_OFFSET, 
											POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 0, 1);
		}
		else if(y == 2) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 8*POSITION_X_OFFSET, 
											POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 0, 2);
		}
		else if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 10*POSITION_X_OFFSET - POSITION_X_AJUST, 
											POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 0, 3);
		}
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 12*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 0, 4);		
		}
	}
	else if(x == 1) {
		if(y == 0) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 3*POSITION_X_OFFSET, 
											POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 1, 0);
		}
		else if(y == 1) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 5*POSITION_X_OFFSET, 
											POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 1, 1);
		}
		else if(y == 2) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 7*POSITION_X_OFFSET, 
											POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 1, 2);
		}		
		else if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 9*POSITION_X_OFFSET, 
											POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 1, 3);
		}
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 11*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 1, 4);
		}
		else if(y == 5) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 13*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
			updateRound(globalRound, color, 1, 5);
		}
	}
	else if(x == 2) {
		if(y == 0) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 2*POSITION_X_OFFSET, 
											POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 2, 0);	
		}
		else if(y == 1) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 4*POSITION_X_OFFSET, 
											POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 2, 1);	
		}		
		else if(y == 2) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 6*POSITION_X_OFFSET, 
											POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 2, 2);	
		}	
		else if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 8*POSITION_X_OFFSET, 
											POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 2, 3);	
		}			
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 10*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 2, 4);
		}
		else if(y == 5) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 12*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 2, 5);
		}
		else if(y == 6) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 14*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 2*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
			updateRound(globalRound, color, 2, 6);
		}			
	}
	else if(x == 3) {
		if(y == 0) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + POSITION_X_OFFSET, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 3, 0);
		}
		else if(y == 1) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 3*POSITION_X_OFFSET, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 3, 1);	
		}
		else if(y == 2) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 5*POSITION_X_OFFSET, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
			updateRound(globalRound, color, 3, 2);
		}
		else if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 7*POSITION_X_OFFSET, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);														
			updateRound(globalRound, color, 3, 3);
		}
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 9*POSITION_X_OFFSET - POSITION_X_AJUST, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 3, 4);
		}
		else if(y == 5) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 11*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 3, 5);
		}
		else if(y == 6) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 13*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 3, 6);
		}
		else if(y == 7) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 15*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 3*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);	
			updateRound(globalRound, color, 3, 7);	
		}		
	}
	else if(x == 4) {
		if(y == 0) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI, 
											POSITION_Y_INI + 4*POSITION_Y_OFFSET), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 4, 0);	
		}
		else if(y == 1) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 2*POSITION_X_OFFSET, 
											POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 4, 1);	
		}
		else if(y == 2) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 4*POSITION_X_OFFSET, 
											POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 4, 2);
		}
		else if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 6*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 4, 3);	
		}
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 8*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 4, 4);	
		}
		else if(y == 5) {
				piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 10*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
				updateRound(globalRound, color, 4, 5);	
		}
		else if(y == 6) {
				piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 12*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
												piecesPlayer[currentPlayer]);
				updateRound(globalRound, color, 4, 6);	
		}
		else if(y == 7) {
				piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 14*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
												piecesPlayer[currentPlayer]);
				updateRound(globalRound, color, 4, 7);	
		}
		else if(y == 8) {
				piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
												POSITION_X_INI + 16*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
												POSITION_Y_INI + 4*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
												piecesPlayer[currentPlayer]);
				updateRound(globalRound, color, 4, 8);	
		}		
	}
	else if(x == 5) {
		if(y == 1) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + POSITION_X_OFFSET, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 5, 1);
		}
		else if(y == 2) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 3*POSITION_X_OFFSET, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 5, 2);	
		}
		else if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 5*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 5, 3);	
		}
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 7*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);											
			updateRound(globalRound, color, 5, 4);	
		}
		else if(y == 5) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 9*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 5, 5);	
		}
		else if(y == 6) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 11*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 5, 6);	
		}
		else if(y == 7) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 13*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 5, 7);	
		}
		else if(y == 8) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 15*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 5*POSITION_Y_OFFSET - POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);											
			updateRound(globalRound, color, 5, 8);	
		}		
	}
	else if(x == 6) {
		if(y == 2) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 2*POSITION_X_OFFSET - POSITION_X_AJUST, 
											POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 6, 2);	
		}
		else if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 4*POSITION_X_OFFSET - POSITION_X_AJUST, 
											POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 6, 3);	
		}
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 6*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);		
			updateRound(globalRound, color, 6, 4);	
		}
		else if(y == 5) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 8*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 6, 5);	
		}
		else if(y == 6) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 10*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 6, 6);	
		}
		else if(y == 7) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 12*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);		
			updateRound(globalRound, color, 6, 7);	
		}
		else if(y == 8) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 14*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 6*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 6, 8);
		}		
	}
	else if(x == 7) {
		if(y == 3) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 3*POSITION_X_OFFSET - POSITION_X_AJUST, 
											POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);			
			updateRound(globalRound, color, 7, 3);	
		}
		else if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 5*POSITION_X_OFFSET - POSITION_X_AJUST, 
											POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 7, 4);	
		}
		else if(y == 5) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 7*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 7, 5);	
		}
		else if(y == 6) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 9*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);											
			updateRound(globalRound, color, 7, 6);
		}
		else if(y == 7) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 11*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 7, 7);
		}
		else if(y == 8) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 13*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 7*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 7, 8);
		}
	}
	else if(x == 8)	{
		if(y == 4) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 4*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);
			updateRound(globalRound, color, 8, 4);		
		}
		else if(y == 5) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 6*POSITION_X_OFFSET - 2*POSITION_X_AJUST, 
											POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);	
			updateRound(globalRound, color, 8, 5);
		}
		else if(y == 6) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 8*POSITION_X_OFFSET - 3*POSITION_X_AJUST, 
											POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);																			
			updateRound(globalRound, color, 8, 6);	
		}
		else if(y == 7) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 10*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);	
			updateRound(globalRound, color, 8, 7);
		}
		else if(y == 8) {
			piecesPlayer[currentPlayer] = insertPar(ajustPositionCoordinates(
											POSITION_X_INI + 12*POSITION_X_OFFSET - 4*POSITION_X_AJUST, 
											POSITION_Y_INI + 8*POSITION_Y_OFFSET - 2*POSITION_Y_AJUST), 
											piecesPlayer[currentPlayer]);		
			updateRound(globalRound, color, 8, 8);
		}
	}
	
	finalCount = countZeros(markedPieces);
	checkFinalGame(finalCount);
	glutPostRedisplay();	
	
	changePlayer();
}


/*
Descrição:
	Prepara o programa para calcular a jogada da IA. E posteriormente
	marca a jogada da IA no tabuleiro.
Variáveis Globais:
	@x, y: coordenadas para a jogada da IA
*/
void activeMinimaxForPlayerPC() {
	int depth = 2;	
	int color;
		
	//Prepara argumentos para a função do minimax
	if(globalRound->playerWhite.player == PLAYER_PC) {
		color = WHITE;
	}
	else {
		color = BLACK;
	}
	
	if(countZeros(markedPieces) == 81 || countZeros(markedPieces) == 80)
		firstMove(globalRound);
	else {
		//printf("Calculando jogada da IA.\n");
		seedMinimax(globalRound, depth, color, &x, &y);
		printf("Minimax: IA deve jogar em (%d,%d).\n", x, y);
	}

	markIAMove(x, y, color);
}


/*
Descrição:
	Conta quantas posições não marcadas existem na matriz
Parâmetros:
	@markedPieces: matriz com as posições do tabuleiro. Indica se uma
	determinada posição está ou não marcada.
Retorno:
	O número de posições não marcadas. (vazias)
*/
int countZeros(int markedPieces[BOARD_ROW][BOARD_COLUMN]) {
	int i, j, count = 0;

	for(i = 0; i < BOARD_ROW; i++)
		for(j = 0; j < BOARD_COLUMN; j++)
			if(markedPieces[i][j] == 0)
				count++;

	return count;
}









