/* MaisViewports.cpp
 *
 *  fevereiro,2002 por Carla Freitas  (criado como DuasViewports)
 *  atualizado em abril de 2008, por Carla
 *
 *  uso de duas viewports na mesma janela
 *
 */

/* include de definicoes das funcoes da glut
 glut.h inclui gl.h, que contem os headers de funcoes da OpenGL propriamente dita
 glut.h inclui tambem definicoes necessarias para o uso de OpenGl nos diversos ambientes Windows
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// estrutura que descreve um ponto (x,y)
typedef struct XY {
	GLfloat x;
	GLfloat y;
} PontoXY;

PontoXY V1, V2, V3, V4, V5;

// Inicializa os pontos com valores default, cor azul
void SetupPontos(void) {

	V1.x = 0; // V1 = (0,0)
	V1.y = 0;
	V2.x = 0; // V2 = (0,10)
	V2.y = 10;
	V3.x = 10; // V3 = (10,10)
	V3.y = 10;
	V4.x = 5; // V4 = (5,5)
	V4.y = 5;
	V5.x = 10; // V5 = (10,0)
	V5.y = 0;

}

// Inicializa cor de fundo e regiao visivel default
//
void SetupJanela(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // cor branca de fundo da janela
}

//  Desenha Objeto 1
void DesenhaObjeto_1(void) {
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(V1.x, V1.y);
	glVertex2f(V2.x, V2.y);
	glVertex2f(V4.x, V4.y);
	glVertex2f(V3.x, V3.y);
	glVertex2f(V5.x, V5.y);
	glEnd();
}

//  Desenha Objeto 2
void DesenhaObjeto_2(void) {
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(V1.x, V1.y);
	glVertex2f(V3.x, V3.y);
	glVertex2f(V5.x, V5.y);
	glEnd();
}
// desenha eixos
void DesenhaEixos(void) {
	glColor3f(1.0f, 0.0f, 0.0f); // eixos vermelhos
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	glVertex2f(0.0, -10.0);
	glVertex2f(0.0, 10.);
	glVertex2f(-10.0, 0.0);
	glVertex2f(10.0, 0.0);
	glEnd();

	glPopMatrix();
}

// Funcao que desenha
// Executada sempre que ocorre qualquer evento de janela
void RenderScene(void) {
	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, 300, 400); // 1a. viewport a esquerda da janela

	// Chamadas de funcoes OpenGL para desenho

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-15, 15, -15, 15); //  area visivel do universo

	DesenhaEixos();
	DesenhaObjeto_1(); // objetos originais
	DesenhaObjeto_2();

	// 2a. viewport

	// define a 2a. viewport
	glViewport(300, 0, 300, 400); // 2a. viewport no centro da janela


	// Recomeca a exibir o SRU
	DesenhaEixos();

	glLoadIdentity(); // objetos transformados
	glPushMatrix();
	glScalef(1, -1, 1);
	glTranslatef(-5, -5, 0);
	DesenhaObjeto_1(); // 1
	glScalef(-1, 1, 1);
	DesenhaObjeto_2(); // 2

	// define a 3a. viewport
	glViewport(600, 0, 300, 400); // 3a. viewport a direita da janela


	// Recomeca a exibir o SRU
	DesenhaEixos();

	glPopMatrix();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-5, -5, 0);
	DesenhaObjeto_2(); // 3
	glScalef(-1, 1, 1);
	DesenhaObjeto_1(); // 4

	glutSwapBuffers();
}
// Callback comum de teclado
void KeyboardFunc(unsigned char key, int x, int y) {
	if (key == 'q') // encerra o programa
	{
		exit(0);
	}

}

// Parte principal - ponto de inicio de execucao
// Cria janela
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a funcao callback de desenho

int main(int argc, char **argv) {
	// Indica que devem ser usados dois buffers para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);

	glutInit(&argc, argv);

	// Cria uma janela com o titulo especificado
	glutInitWindowSize(900, 400);
	glutCreateWindow("Exemplo com 3 viewports");

	// Especifica a funcao de desenho
	glutDisplayFunc(RenderScene);

	// Callback de teclado
	glutKeyboardFunc(KeyboardFunc);

	// Executa a inicializacao de parametros de exibicao para a janela corrente
	SetupJanela();

	// Inicializa as informacoes geometricas do objeto
	// cores valem para a janela corrente
	SetupPontos();

	// Dispara a "maquina de estados" de OpenGL
	glutMainLoop();

	return (0);

}
