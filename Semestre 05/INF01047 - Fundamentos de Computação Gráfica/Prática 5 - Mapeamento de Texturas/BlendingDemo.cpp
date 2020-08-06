#include <stdio.h>
#include <gl/glut.h>
#include <stdlib.h>

static int leftFirst = GL_TRUE;
static GLenum sfactor = GL_SRC_ALPHA;
static GLenum dfactor = GL_ONE_MINUS_SRC_ALPHA; 
static GLfloat Displacement = 1.0;

static void init(void)
{
	glEnable(GL_BLEND);
	glBlendFunc(sfactor, dfactor);
	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

static void drawLeftTriangle( void)
{
	glBegin(GL_TRIANGLES);
	glColor4f(1.0, 1.0, 0.0, 0.75);
	glVertex3f(0.1, 0.9, 0.0);
	glVertex3f(0.1, 0.1, 0.1 );
	glVertex3f(0.7, 0.5, 0.0);
	glEnd();
}
static void drawRightTriangle(void)
{ 
   glBegin(GL_TRIANGLES);
  	glColor4f(0.0, 1.0, 1.0, 0.75);
		glVertex3f((0.9 + Displacement), 0.9, 0.0);
		glVertex3f((0.3 + Displacement), 0.5, 0.0);
		glVertex3f((0.9 + Displacement), 0.1, 0.0);
	glEnd();
}

void display( void)
{
	glClear(GL_COLOR_BUFFER_BIT);
 	if (leftFirst) {
		drawLeftTriangle();
		drawRightTriangle();
	}
	else {
		drawRightTriangle();
		drawLeftTriangle();
	}
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w<= h)
		gluOrtho2D(0.0, 1.5, 0.0, 1.5*(GLfloat)h/(GLfloat)w);
	else
		gluOrtho2D(0.0, 1.5*(GLfloat) w/(GLfloat)h, 0.0, 1.5);
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key) {
	case 't':
	case 'T':
		leftFirst = !leftFirst;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}
void MenuFunc( int value )
{
	switch (value ) 
	{
	case 0:
		break;
	case 1: sfactor = GL_ZERO; break;
	case 2:	sfactor = GL_ONE;	break;
	case 3: sfactor = GL_DST_COLOR;	break;
	case 4: sfactor = GL_SRC_COLOR;	break;
	case 5:	sfactor = GL_ONE_MINUS_DST_COLOR;	break;
	case 6:	sfactor = GL_ONE_MINUS_SRC_COLOR;	break;
	case 7:	sfactor = GL_SRC_ALPHA;break;
	case 8:	sfactor = GL_ONE_MINUS_SRC_ALPHA;	break;
	case 9:	sfactor = GL_DST_ALPHA; break;
	case 10: sfactor = GL_ONE_MINUS_DST_ALPHA;	break;
	case 11: sfactor = GL_SRC_ALPHA_SATURATE;	break;
	case 12: dfactor = GL_ZERO;	break;
	case 13: dfactor = GL_ONE;	break;
	case 14: dfactor = GL_DST_COLOR;break;
	case 15: dfactor = GL_SRC_COLOR;break;
	case 16: dfactor = GL_ONE_MINUS_DST_COLOR;	break;
	case 17: dfactor = GL_ONE_MINUS_SRC_COLOR;	break;
	case 18: dfactor = GL_SRC_ALPHA;		break;
	case 19: dfactor = GL_ONE_MINUS_SRC_ALPHA;	break;
	case 20: dfactor = GL_DST_ALPHA;		break;
	case 21: dfactor = GL_ONE_MINUS_DST_ALPHA;	break;
	case 22: dfactor = GL_SRC_ALPHA_SATURATE;	break;
	default:		exit(0);	break;
	}
 
 glBlendFunc(sfactor, dfactor);
	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
    Displacement = 1.0;
    
  	glutPostRedisplay();
}

void idlefunc( void)
{
	if( Displacement > 0)
		Displacement -= 0.05;
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	init();
	glutIdleFunc( idlefunc );
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
    glutCreateMenu( MenuFunc );
	glutAddMenuEntry( "REPEAT", 0);
	glutAddMenuEntry( "Source GL_ZERO", 1);
	glutAddMenuEntry( "Source GL_ONE", 2);
	glutAddMenuEntry( "Source GL_DST_COLOR", 3);
	glutAddMenuEntry( "Source GL_SRC_COLOR", 4);
	glutAddMenuEntry( "Source GL_ONE_MINUS_DST_COLOR", 5);
	glutAddMenuEntry( "Source GL_ONE_MINUS_SRC_COLOR", 6);
	glutAddMenuEntry( "Source GL_SRC_ALPHA", 7);
	glutAddMenuEntry( "Source GL_ONE_MINUS_SRC_ALPHA", 8);
	glutAddMenuEntry( "Source GL_DST_ALPHA", 9);
	glutAddMenuEntry( "Source GL_ONE_MINUS_DST_ALPHA", 10);
	glutAddMenuEntry( "Source GL_SRC_ALPHA_SATURATE", 11);
 	glutAddMenuEntry( "Destination GL_ZERO", 12);
	glutAddMenuEntry( "Destination GL_ONE", 13);
	glutAddMenuEntry( "Destination GL_DST_COLOR", 14);
	glutAddMenuEntry( "Destination GL_SRC_COLOR", 15);
	glutAddMenuEntry( "Destination GL_ONE_MINUS_DST_COLOR", 16);
	glutAddMenuEntry( "Destination GL_ONE_MINUS_SRC_COLOR", 17);
	glutAddMenuEntry( "Destination GL_SRC_ALPHA", 18);
	glutAddMenuEntry( "Destination GL_ONE_MINUS_SRC_ALPHA", 19);
	glutAddMenuEntry( "Destination GL_DST_ALPHA", 20);
	glutAddMenuEntry( "Destination GL_ONE_MINUS_DST_ALPHA", 21);
	glutAddMenuEntry( "Destination GL_SRC_ALPHA_SATURATE", 22);
	glutAddMenuEntry( "Exit", 23);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}

