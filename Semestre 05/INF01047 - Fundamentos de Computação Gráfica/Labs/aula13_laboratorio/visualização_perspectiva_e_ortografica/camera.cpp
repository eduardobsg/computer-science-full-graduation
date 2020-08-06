/* Camera.cpp
*  
*  abril, 2002 - Luciana Nedel
*  adaptado por Carla Freitas em 2006, 2008 e 2009
*
*  Exemplo para manipulacao de camera em OpenGL
*/

/* include de definicoes das funcoes da glut 
   glut.h inclui gl.h, que contem os headers de funcoes da OpenGL propriamente dita
   glut.h inclui tambem definicoes necessarias para o uso de OpenGl nos diversos ambientes Windows
*/

#include <GL/glut.h>
#include <stdio.h>

//#define PERSPECTIVA 0       // projecao ortografica
#define PERSPECTIVA 1         // projecao perspectiva

// Estrutura que define os parametros da camera

typedef struct camera {
        GLdouble atx;
        GLdouble aty;
        GLdouble atz;
        GLdouble tox;
        GLdouble toy;
        GLdouble toz;
} Observador;

Observador Camera1;

// Parametros de projecao
GLfloat fAspect;
GLfloat angle = 100;    // angulo de abertura para proj. perspectiva

// limites do volume ortografico
GLdouble minX=-100.00;
GLdouble maxX=100.00;
GLdouble minY=-100.00;
GLdouble maxY=100.00;
GLint incremento=0;

// planos near e far para recorte em profundidade
GLdouble near_plane= 2.0;
GLdouble far_plane=240.0;
 

// Inicializacao
void SetupRC(void)
{
 
    // Especifica que a cor de fundo da janela sera branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
    // Limpa a janela e habilita o teste para eliminar faces ocultas por outras
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
	// habilita o uso de uma cor por face
    glShadeModel(GL_FLAT); 
    
    // inicializa camera    
    Camera1.atx=40.0;
    Camera1.aty=60.0;
    Camera1.atz=100.0;
    
    Camera1.tox=0.0;   // olhando para o ponto central da piramide 
    Camera1.toy=0.0;
    Camera1.toz=0.0;
    
}


/* Funcao usada para especificar o volume de visualizacao
*  no caso de projecao perspectiva
*  So eh executada se a constante PERSPECTIVA  = 1
*/  
void PerspectiveViewing(void)
{
    // Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa matriz modelview com a identidade
	glLoadIdentity();
	// Especifica posicao do observador e do alvo
	gluLookAt(Camera1.atx,Camera1.aty,Camera1.atz,Camera1.tox,Camera1.toy,Camera1.toz, 0,1,0);

	// Especifica manipulacao da matriz de projecao
	glMatrixMode(GL_PROJECTION);
	// Inicializa matriz com a identidade
	glLoadIdentity();
 
    // Especifica a projecao perspectiva
    gluPerspective(angle,fAspect,0.1,500);
   //  gluPerspective(angle,fAspect,near_plane,far_plane);
}

/* Funcao usada para especificar o volume de visualizacao
*  no caso de projecao perspectiva
*  Executada quando PERSPECTIVA  = 0 (situacao inicial)
*/  
void OrthoViewing(void)
{
	 // Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa matriz modelview com a identidade
	glLoadIdentity();
	// Especifica posicao do observador e do alvo
	gluLookAt (Camera1.atx,Camera1.aty,Camera1.atz,Camera1.tox,Camera1.toy,Camera1.toz, 0,1,0);
 
    // Especifica manipulacao da matriz de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa matriz com a identidade
	glLoadIdentity();
 
    // Especifica a projecao ortográfica
    
    glOrtho(minX-incremento,
            maxX+incremento,
            minY-incremento,
            maxY+incremento,
            near_plane,far_plane);
        
    glMatrixMode(GL_MODELVIEW);
}
// Chamada pela GLUT quando a janela e redimensionada
void ChangeSize(GLsizei w, GLsizei h)
{
	// Para prevenir uma divisao por zero
	if ( h == 0 )
		h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
            
	// Calcula a correcao de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

    if (PERSPECTIVA)
        {                        // chamada para atualizar o volume de visualizacao
          PerspectiveViewing();  // no caso de perspectiva
        }
    else
        {                        // chamada para atualizar o volume de visualizacao
          OrthoViewing();        // no caso de projecao ortografica
        }
    glutPostRedisplay();
}


// Minha funcao de desenho
void RenderScene(void)
{
	// Limpa a janela
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_LINES);
       // eixos coordanados x = vermelho, y = verde  z = azul
       glColor3f(1.0f, 0.0f, 0.0f);
       glVertex3i(-100,0,0);
       glVertex3i(100,0,0);
       
       glColor3f(0.0f, 1.0f, 0.0f);
       glVertex3i(0, -100,0);
       glVertex3i(0, 100,0);
       
       glColor3f(0.0f, 0.0f, 1.0f);
       glVertex3i(0,0,-100);
       glVertex3i(0,0,100);
    glEnd();
 
	// Desenha uma piramide de base quadrada (lado 20) com faces coloridas
    // localizada na origem, com altura 30 	
    glBegin(GL_QUADS);
       // face da base - preta
       glColor3f(0.0f, 0.0f, 0.0f);
       glVertex3i(-20,0,-20);
       glVertex3i(20,0,-20);
       glVertex3i(20,0,20);
       glVertex3i(-20,0,20);
    glEnd();
    
    glBegin(GL_TRIANGLES);  
       // face voltada para eixo z positivo
       // azul
       glColor3f(0.0f, 0.0f, 1.0f);
       glVertex3i(-20,0,20);
       glVertex3i(20,0,20);
       glVertex3i(0,30,00);
       
       // face voltada para o eixo x positivo   
       // amarela    
       glColor3f(1.0f, 1.0f, 0.0f);
       glVertex3i(20,0,20);
       glVertex3i(20,0,-20);
       glVertex3i(0,30,00);
       
       // face voltada para o eixo z negativo  
       // vermelha  
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3i(20,0,-20);
       glVertex3i(-20,0,-20);
       glVertex3i(0,30,00);
       
       // face voltada para o eixo x negativo 
       //  verde    
       glColor3f(0.0f,1.0f, 0.0f);
       glVertex3i(-20,0,-20);
       glVertex3i(-20,0,20);
       glVertex3i(0,30,0);
     glEnd();
 

	//Garante a execucao dos comandos de desenho
	// glFlush();
	glutSwapBuffers();
}

/* Minha Callback para gerenciar eventos do mouse
 * Devolve o botao pressionado, o estado do botão e
 * posicao do cursor, relativa a janela.
*/
// A especificacao da GLUT traz os demais detalhes desse tratamento
 
void HandleMouse(int button, int state, int x, int y)
{
    // o botao esquerdo diminui o angulo (perspectiva)
    // ou a largura do volume ortografico
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom-in
			if (PERSPECTIVA)
                if (angle >= 10)
				     angle -= 5;
                else;
            else incremento-=10; // veja o que acontece se fica negativo!!
    
		}
    // o botao direito aumenta o angulo (perspectiva)
    // ou a largura do volume ortografico
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			// Zoom out
           if (PERSPECTIVA)
              if (angle <= 130)
				   angle += 5;
              else;
           else incremento+=10;
		}
	
    if (PERSPECTIVA) 
        PerspectiveViewing();
    else
        OrthoViewing();
	glutPostRedisplay();
}


// Programa Principal
int main( int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400,350);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(HandleMouse);
	SetupRC();
	glutMainLoop();
    return (0); 
}
