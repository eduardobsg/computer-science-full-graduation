/*

   BMP_TextureDemo.cpp  baseado em mod3d.cpp de S. Olabarriaga
   Modificado por Carla Freitas(2002) 

   Implementa visualizacao de um objeto, com textura rotacionando-o sob comando
   do mouse para inspecao visual
   Usa a função LoadDIBitmap() definida em bitmap.c
*/

// Includes
#include <iostream.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include "bitmap.h"

typedef struct rRGB{
        GLfloat R;
        GLfloat G;
        GLfloat B;
} corRGB;

typedef struct XYZ {
        float x;
        float y;
        float z;
} PontoXYZ;

// tabela de vertices
PontoXYZ vert[8] = {
         { -5.0, -5.0,  -5.0 },      // 0
         { -5.0, 5.0,  -5.0 },       // 1
         { -5.0, 5.0, 5.0 },         // 2
         { -5.0, -5.0, 5.0 },        // 3
         { 5.0, -5.0, -5.0 },        // 4
         { 5.0, -5.0, 5.0 },         // 5
         { 5.0, 5.0, 5.0 },          // 6
         { 5.0, 5.0, -5.0}           // 7
         };

// tabela de cores por face
corRGB corFace[6] =  {
         {1.0f,0.0f,0.0f}, // Red
         {1.0f,1.0f,1.0f}, // White para receber a textura
         {0.0f,1.0f,0.0f}, // Green
         {1.0f,0.0f,1.0f}, // 
         {0.0f,0.0f,1.0f}, // Blue
         {1.0f,1.0f,0.0f}  // Yellow
                        };
// variaveis para controle da rotacao com o mouse
static bool rotacionaX = false;
static bool rotacionaY = false;

// parte de código extraído de "texture.c" por Michael Sweet (OpenGL SuperBible)
int i;                       /* Looping var */
BITMAPINFO	*info;           /* Bitmap information */
GLubyte	    *bits;           /* Bitmap RGB pixels */
GLubyte     *ptr;            /* Pointer into bit buffer */
GLubyte	    *rgba;           /* RGBA pixel buffer */
GLubyte	    *rgbaptr;        /* Pointer into RGBA buffer */
GLubyte     temp;            /* Swapping variable */
GLenum      type;            /* Texture type */
GLuint      texture;         /* Texture object */



bool inicializaTextura(void)
{ 
    // Load a texture object (256x256 true color) 
    bits = LoadDIBitmap("tiger.bmp", &info);
    if (bits == (GLubyte *)0)
        return (false);
   
    // Figure out the type of texture
    if (info->bmiHeader.biHeight == 1)
      type = GL_TEXTURE_1D;
    else
      type = GL_TEXTURE_2D;

    // Create and bind a texture object 
    glGenTextures(1, &texture);
	glBindTexture(type, texture);

    // Set texture parameters 
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP);    
     
    // Create an RGBA image
    rgba = (GLubyte *)malloc(info->bmiHeader.biWidth * info->bmiHeader.biHeight * 4);
    
    i = info->bmiHeader.biWidth * info->bmiHeader.biHeight;
    for( rgbaptr = rgba, ptr = bits;  i > 0; i--, rgbaptr += 4, ptr += 3)
    {
            rgbaptr[0] = ptr[2];     // windows BMP = BGR 
            rgbaptr[1] = ptr[1];
            rgbaptr[2] = ptr[0];
            rgbaptr[3] = (ptr[0] + ptr[1] + ptr[2]) / 3;            
    }

    glTexImage2D(type, 0, 4, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 
                  0, GL_RGBA, GL_UNSIGNED_BYTE, rgba );   
 
    printf("Textura %d", texture);
    return (true);
}  

// funcao para desenho com textura
void cubo (int j)
{    
   glColor4f( (float) corFace[j].R, (float) corFace[j].G, (float) corFace[j].B, 1.0f ) ; 
   glShadeModel(GL_FLAT);
    
   if (j == 1)
   {         
      glEnable (type);
      glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);             
      glBegin( GL_POLYGON );
         glTexCoord2f(1.0f, 0.0f);  glVertex3f(vert[0].x,vert[0].y,vert[0].z);
         glTexCoord2f(0.0f, 0.0f);  glVertex3f(vert[4].x,vert[4].y,vert[4].z);
         glTexCoord2f(0.0f, 1.0f);  glVertex3f(vert[7].x,vert[7].y,vert[7].z);
         glTexCoord2f(1.0f, 1.0f);  glVertex3f(vert[1].x,vert[1].y,vert[1].z);
      glEnd(); 
      glDisable(type);          
   }
   else 
   {
      if (j==3) 
      {
         glEnable (type);
         glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
      }
      glBegin( GL_POLYGON );     
      switch (j) 
      {
            case 0:
              glVertex3f(vert[3].x,vert[3].y,vert[3].z);
              glVertex3f(vert[0].x,vert[0].y,vert[0].z);
              glVertex3f(vert[1].x,vert[1].y,vert[1].z);            
              glVertex3f(vert[2].x,vert[2].y,vert[2].z);
              break; 
            case 2:
              glVertex3f(vert[4].x,vert[4].y,vert[4].z);
              glVertex3f(vert[5].x,vert[5].y,vert[5].z);
              glVertex3f(vert[6].x,vert[6].y,vert[6].z);
              glVertex3f(vert[7].x,vert[7].y,vert[7].z);
              break; 
            case 3:
              glTexCoord2f(1.0f, 0.0f);  glVertex3f(vert[5].x,vert[5].y,vert[5].z);
              glTexCoord2f(0.0f, 0.0f);  glVertex3f(vert[3].x,vert[3].y,vert[3].z);
              glTexCoord2f(0.0f, 1.0f);  glVertex3f(vert[2].x,vert[2].y,vert[2].z);
              glTexCoord2f(1.0f, 1.0f);  glVertex3f(vert[6].x,vert[6].y,vert[6].z);
              break;
            case 4:
              glVertex3f(vert[3].x,vert[3].y,vert[3].z);
              glVertex3f(vert[5].x,vert[5].y,vert[5].z);
              glVertex3f(vert[4].x,vert[4].y,vert[4].z);
              glVertex3f(vert[0].x,vert[0].y,vert[0].z);
              break;    
            case 5:            
              glVertex3f(vert[1].x,vert[1].y,vert[1].z);
              glVertex3f(vert[7].x,vert[7].y,vert[7].z);
              glVertex3f(vert[6].x,vert[6].y,vert[6].z);         
              glVertex3f(vert[2].x,vert[2].y,vert[2].z);      
              break; 
          }                
          glEnd();
          glDisable(type);
      }
}

// Desenha Cubo colorido com texturas.
void drawFunc ()
{
     glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
     
     for (int j=0; j< 6; j++)
        cubo(j);
 
     glutSwapBuffers();  
}

// Desenha Textura simples na Janela
void drawTexture ()
{
     glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
     glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();
     glMatrixMode (GL_MODELVIEW);
     glLoadIdentity();     
     
     glRasterPos2i(-1,-1);
     glDrawPixels(256,256,GL_RGBA, GL_UNSIGNED_BYTE, rgba); 
 
     glutSwapBuffers();  // for double buffers
}

// Inicializações
void initFunc ()
{
    glClearColor( 1.0f, 1.0f, 1.0f, 0.0f );
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0,-10.0, 10.0, -20.0, 20.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
     
    //habilita remocao de faces ocultas
    glEnable (GL_DEPTH_TEST);
    
    if (!inicializaTextura()) {
       printf ("Problemas na abertura da textura!");
       cin >> texture;
       exit(0);
    }
}

// Função Idle
void idleFunc() 
{
    if ( rotacionaX ) {
         glRotatef( 0.7f, 1.0f, 0.0f, 0.0f );
         glutPostRedisplay();
    } 
    if ( rotacionaY) {
         glRotatef( 0.7f, 0.0f, 1.0f, 0.0f );
         glutPostRedisplay();
    }
}

//Callback do Mouse
void mouseFunc ( int button, int state, int x, int y )
{
     if ( state == GLUT_DOWN ) {
        if (button == GLUT_LEFT_BUTTON )
           rotacionaX = true;
        if (button == GLUT_RIGHT_BUTTON )
           rotacionaY = true;
     }
     if ( state == GLUT_UP ) {
           rotacionaX = false;
           rotacionaY = false;
     }
}

//Main Function
int main( int argc, char** argv)
{      
     glutInit(&argc, argv);      
     glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  
     glutInitWindowSize(256,256);
     glutInitWindowPosition(450,0);
     
     //cria janela mostrando textura
     glutCreateWindow("Textura");
     glutDisplayFunc(drawTexture);     
     
     //cria janela para colar textura
     glutInitWindowSize(400,400);
     glutInitWindowPosition(0,0);
     glutCreateWindow("Demo Visualizacao");

     // local initialization
     initFunc();
    
     // configure callbacks
     glutDisplayFunc(drawFunc);
     glutIdleFunc(idleFunc);
     glutMouseFunc(mouseFunc);     
     
     glutMainLoop();
     return (0);
}
