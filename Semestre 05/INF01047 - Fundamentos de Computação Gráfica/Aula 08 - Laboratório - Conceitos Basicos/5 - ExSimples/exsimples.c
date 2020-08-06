/*
 *--------------------------------------------------
 *	exSimples.c
 *	
 *	Autor: Prof. Marcelo Walter
 *	Data: Jan 19, 1999
 *	Ultima modificacao: Outubro, 2003
 *
 *	Este programa introduz os principais
 *	conceitos de programacao 2D com GLUT e
 *	OpenGL. Este programa desenha um quadrado
 *	aproximadamente centrado no meio da tela
 *	A cor do quadrado muda aleatoriamente
 *	ao pressionar-se o botao esquerdo do mouse
 
Se você executar o programa, observará algumas situações que poderiam ser 
melhoradas. Pense nos problemas abaixo e como você acha que os resolveria 
utilizando as rotinas de GLUT.

a) Caso você tente redimensionar a janela, observará que o fundo da tela não 
será "limpo" e que a posição do quadrado é variável dentro da janela. Porque 
ocorrem estas duas situações? Como corrigi-las?

b) Tente desenhar outros objetos, ao invés de um quadrado um triângulo por exemplo.

c) Vamos supor que você queira mudar interativamente a posição onde o quadrado 
é desenhado via teclado, ou seja, suponha que pressionando-se determinada tecla 
o quadrado deva mover-se 20 pixels acima e à direita da posição corrente. Como 
você faria isto? 

d) O clique do mouse na verdade causa 2 mudanças de cor em seguida, muito rápidas. 
Porque isto acontece? Como você mudaria o código acima para a cor do quadrado 
mudar somente uma vez quando o mouse é pressionado?
 
 *--------------------------------------------------
 */

/*
 *--------------------------------------------------
 * Includes
 *--------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

/* Global Variables */
int width, height;
int up, down, left, right;


/*
 *--------------------------------------------------
 * Prototipos para as funcoes globais
 *--------------------------------------------------
 */

void setupGlobalVariables( void );
void desenhaCB( void );
void tecladoCB( unsigned char tecla, int x, int y );
void redesenhaCB( int w, int h );
void initOpenGL( void );
void initGLUT( void );
void mouseCB( int botao, int estado, int x, int y );
extern int rand ( void );


/*
 *--------------------------------------------------
 * Funcao principal
 *--------------------------------------------------
 */
int main( int argc, char *argv[] ){
  glutInit( &argc, argv );
  
  glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE );
  
  initOpenGL();

  initGLUT();
  
  setupGlobalVariables();
  
  glutMainLoop();	
  return 1;
}


/*
 *--------------------------------------------------
 * Esta funcao inicializa as variáveis globais
 *--------------------------------------------------
 */
void setupGlobalVariables( void ){
     width = 300;
     height = 300;
     up = 0;
     down = 0;
     left = 0;
     right = 0;     
}

/*
 *--------------------------------------------------
 * Esta funcao inicializa a janela OpenGL
 *--------------------------------------------------
 */
void initOpenGL( void ){
  /* Cor default fundo preta */
  glClearColor( 0, 0, 0, 0 );		
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  /* Cor default para objetos */
  glColor3f( 1.0, 0.0, 0.0 );
}

/*
 *--------------------------------------------------
 * Esta funcao as funcoes relacionadas com GLUT
 * registra as rotinas de callback
 *--------------------------------------------------
 */
void initGLUT( void ){
  glutInitWindowPosition( 200, 100 );
  glutCreateWindow( "Exemplo Simples 1" );

  /* Registra as rotinas de CallBack */
  glutDisplayFunc( desenhaCB );	
  glutKeyboardFunc( tecladoCB );
  glutReshapeFunc( redesenhaCB );
  glutMouseFunc( mouseCB );

}

/*
 *----------------------------------------------------------
 *	Rotina para tratamento de evento - Exibicao da janela
 *----------------------------------------------------------
 */
void desenhaCB( void ){
    /* Limpa buffer de cor */
    glClear ( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	
	glBegin(GL_POLYGON);
		//glVertex2i( (int)width*2/3, (int)height*2/3 );
		glVertex2i( (int)width*2/3 + right - left, (int)height/2 + up - down);
		glVertex2i( (int)width/2 + right - left, (int)height/2 + up - down );
		glVertex2i( (int)width/2 + right - left, (int)height*2/3 + up - down );
	glEnd();

	glFlush();
}       


/*
 *--------------------------------------------------
 *	Rotina para tratamento de evento - Teclado
 *
 *	tecla: Tecla pressionada pelo usuario
 *	x - posicao x do mouse
 *	y - posicao y do mouse
 *
 *--------------------------------------------------
 */
void tecladoCB( unsigned char tecla, int x, int y ){
   int i = 10;  
   switch( tecla ) {
	case 'q':			/* Encerra o programa */
	case 'Q':
		exit( 0 );
		break;
	case 'w':
    case 'W':
          if ((int)height*2/3 + up - down < height){         
            printf("height: %d, up: %d\n", height, (int)height*2/3 + up - down);
            up += i;  
          }
          break;   	
   	case 's':
    case 'S':
         if ((int)height/2 + up - down > 0){
            printf("height: %d, down: %d\n", height, (int)height/2 + up - down);
            down += i;     
         }
         break;
    case 'a':
    case 'A':
          if ((int)width/2 + right - left > 0){
             printf("width: %d, left: %d\n", width, (int)width/2 + right - left);
             left += i;
          }
          break;
    case 'd':
    case 'D':
          if ((int)width*2/3 + right - left < width){
             printf("width: %d, right: %d\n", width, (int)width*2/3 + right - left);
             right += i;                
          }
          break;
	default:
		  printf("Opcao nao definida!\n");
	}
	
	glutPostRedisplay();
}   


/*
 *----------------------------------------------------------
 *	Rotina para tratamento de eventos relacionados ao mouse
 *
 *  botao: Botao que foi pressionado. Um de 3 valores
 *	GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON
 *
 *	estado: Se o mouse foi clicado ou solto
 *	GLUT_UP ou GLUT_DOWN
 *
 *	x,y: posicao do mouse dentro da janela
 *----------------------------------------------------------
 */
void mouseCB( int botao, int estado, int x, int y ){
	if ( botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN )
		glColor3ub( (char) (rand()%256), (char) (rand()%256), (char) (rand()%256) );

	glutPostRedisplay();
}                              
                                   

/*
 *--------------------------------------------------
 *	Rotina para tratamento de evento
 *	Alteracao de tamanho da janela
 *	w - largura corrente da janela
 *	h - altura corrente da janela
 *--------------------------------------------------
 */
void redesenhaCB( int w, int h ){
  width = w;
  height = h;    

  glViewport( 0, 0, w, h );

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0, (GLfloat) w, 0, (GLfloat) h , -1.0, 1.0 );

}					

