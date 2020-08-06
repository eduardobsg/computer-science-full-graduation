/*

   Nome: mod3D.cpp
   Autora: Silvia Olabarriaga (2001)
   Adaptado por: Carla Freitas (2002,2007,2011)


   Implementa visualizacao de um objeto 3D, rotacionando-o sob comando

   do mouse para inspecao visual


*/


// Includes

#include <GL/glut.h>
#include <iostream>
#include <stdio.h>

typedef GLfloat PontoXYZ[3];

//
// modelo geometrico da piramide
//


// tabela de vertices
// entre (-0.5, -0.5, -0.5) a (0.5, 0.5, 0.5)

PontoXYZ pirVert[4] = {
         { -0.5, -0.5,  0.5 },   // vertice 0
         {  0.5, -0.5,  0.5 },   // vertice 1
         {  0.0, -0.5, -0.5 },   // vertice 2
         {  0.0,  0.5,  0.0 } }; // vertice 3



// tabela de faces

const int nFaces = 4;
int pirFaces[nFaces][3] = {
         { 3, 0, 1 },
         { 3, 1, 2 },
         { 3, 2, 0 },
         { 1, 0, 2 } };



// tabela de cores por face

PontoXYZ pirCor[nFaces] =  {
         { 1.0f, 0.0f, 0.0f},
         { 0.0f, 1.0f, 0.0f},
         { 0.0f, 0.0f, 1.0f},
         { 1.0f, 0.0f, 1.0f} };



// variaveis para controle da rotacao com o mouse

static bool rotacionaX = false;

static bool rotacionaY = false;


// funcao para desenho

void piramide (void)

{
     for ( int i=0; i < nFaces; i++ ) {

       glColor3fv( pirCor[i] );

       glBegin( GL_POLYGON );
           glVertex3fv(pirVert[ pirFaces[i][0] ]);
           glVertex3fv(pirVert[ pirFaces[i][1] ]);
           glVertex3fv(pirVert[ pirFaces[i][2] ]);
       glEnd();

     }
}


// Funcao de desenho
// chamada pela OpenGL

void RenderScene ()

{
     glClear( GL_COLOR_BUFFER_BIT );
     piramide();
     glutSwapBuffers();  // for double buffers

}


// Inicializacoes
// chamada por main


void initFunc ()

{

     glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
     
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();
     glOrtho(-2.0,2.0,-2.0,2.0,8.0,12.0);
     
     glMatrixMode (GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
     
     printf("Use o botao esquerdo do mouse para rotacionar em torno de X.");
     printf("\nUse o botao direito para rotacionar em Y.");
     printf("\nO botãao do meio para a animacao.");
    

     // habilita remocao de faces ocultas

     //glFrontFace (GL_CCW);  
     
     //glEnable(GL_CULL_FACE);

}



// Idle function
// chamada quando OpenGl nao tem nada a fazer
// pode ser usada para implementar animacao

void idleFunc()

{
    if ( rotacionaX ) {
         glRotatef( 0.7f, 1.0f, 0.0f, 0.0f );
         glutPostRedisplay();
    } else if ( rotacionaY) {
         glRotatef( 0.7f, 0.0f, 1.0f, 0.0f );
         glutPostRedisplay();
    }

}

// trata eventos do mouse
// botao esquerdo - rotaciona em  x
// botao direito - rotaciona em  y


void mouseFunc ( int button, int state, int x, int y )

{
     if ( state == GLUT_DOWN ) {
        if (button == GLUT_LEFT_BUTTON )
            rotacionaX = true;
        else if (button == GLUT_RIGHT_BUTTON )
                rotacionaY = true;
        else if (button ==  GLUT_MIDDLE_BUTTON) {
                      rotacionaX = false;
                      rotacionaY = false;   
                      }               
        } 
  /*    
     else if ( state == GLUT_UP) {
               rotacionaX = false;
               rotacionaY = false;
          } */
}


// funcao principal do programa

int main( int argc, char** argv)

{

    glutInit(&argc, argv);
     // create OpenGL window

     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);      // double buffer
     glutInitWindowSize(400,400);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Back-Face Culling");
     

     // local initialization

     initFunc();
     
     // configure callbacks

     glutDisplayFunc(RenderScene);
     glutIdleFunc(idleFunc);
     glutMouseFunc(mouseFunc);
     glutMainLoop();
     return 0;

}
