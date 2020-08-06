#include <gl/glut.h>
#include <stdio.h>


#define    checkImageWidth 64
#define    checkImageHeight 64
GLubyte checkImage[checkImageWidth][checkImageHeight][3];

void makeCheckImage(void)
{
    int i, j, c;

    for (i = 0; i < checkImageWidth; i++) {
        for (j = 0; j < checkImageHeight; j++) {
            c = ((((i&0x8)==0)^((j&0x8))==0));
            checkImage[i][j][0] = (GLubyte) c ;
            checkImage[i][j][1] = (GLubyte) c * 255;
            checkImage[i][j][2] = (GLubyte) c ;
        }
    }
}

void myinit(void)
{     
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //gera imagem a ser usada como textura.
    makeCheckImage();
        
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth, checkImageHeight, 
                 0, GL_RGB, GL_UNSIGNED_BYTE, &checkImage[0][0][0]);
    
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    glEnable(GL_TEXTURE_2D);
    
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //glColor3f(1.0,1.0,0.0);
    
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0);  glVertex3f(-2.0, -1.0, 0.0);
        glTexCoord2f(0.0, 1.0);  glVertex3f(-2.0,  1.0, 0.0);
        glTexCoord2f(1.0, 1.0);  glVertex3f( 0.0,  1.0, 0.0);
        glTexCoord2f(1.0, 0.0);  glVertex3f( 0.0, -1.0, 0.0);
    glEnd();
    
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex3f( 1.0, -1.0,  0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f( 1.0,  1.0,  0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f( 2.5,  1.0, -1.5);
        glTexCoord2f(1.0, 0.0); glVertex3f( 2.5, -1.0, -1.5);
    glEnd();
    
    glFlush();
}

void myReshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0*(GLfloat)w/(GLfloat)h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.6);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize( 500, 500);
    glutCreateWindow ("Demo textura simples");
    glutDisplayFunc(display);
    myinit();
    glutReshapeFunc (myReshape);
    glutMainLoop();
    
    return 0;
}
