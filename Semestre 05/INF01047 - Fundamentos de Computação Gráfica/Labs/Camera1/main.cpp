/**********************************************************************
	
  camera with OpenGL

  June, 11th, 2000

  This tutorial was written by Philipp Crocoll
  Contact: 
	philipp.crocoll@web.de
	www.codecolony.de

  Every comment would be appreciated.

  If you want to use parts of any code of mine:
	let me know and
	use it!

**********************************************************************
ESC: exit

CAMERA movement:
w : forwards
s : backwards
a : turn left
d : turn right
x : turn up
y : turn down
v : strafe right
c : strafe left
r : move up
f : move down

***********************************************************************/

#include <GL/glut.h>
#include "camera.h"


Camera camera;


void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
{
	glBegin(GL_LINES);
	for (int xc = 0; xc < LinesX; xc++)
	{
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / 2.0);
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
					0.0,
					size / -2.0);
	}
	for (int zc = 0; zc < LinesX; zc++)
	{
		glVertex3f(	size / 2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
		glVertex3f(	size / -2.0,
					0.0,
					-size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
	}
	glEnd();
}

void PerspectiveViewport(void)
{
	GLsizei width = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei height = glutGet(GLUT_WINDOW_HEIGHT);
	
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();

	gluPerspective(40.0,(GLdouble)width/(GLdouble)height,0.5,20.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	camera.Render();
	PerspectiveViewport();
	glTranslatef(0.0,0.8,0.0);

	glScalef(3.0,1.0,3.0);
	
	GLfloat size = 2.0;
	GLint LinesX = 30;
	GLint LinesZ = 30;
	
	GLfloat halfsize = size / 2.0;
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		glTranslatef(0.0,-halfsize ,0.0);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();
	glColor3f(0.0,0.0,1.0);
	glPushMatrix();
		glTranslatef(-halfsize,0.0,0.0);	
		glRotatef(90.0,0.0,0.0,halfsize);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,-size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
		glTranslatef(0.0,0.0,-halfsize);	
		glRotatef(90.0,halfsize,0.0,0.0);
		DrawNet(size,LinesX,LinesZ);
		glTranslatef(0.0,size,0.0);
		DrawNet(size,LinesX,LinesZ);
	glPopMatrix();
		
	glFlush();  
	glutSwapBuffers();

}
void KeyDown(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 27:		//ESC
		exit(0);
		break;
	case 'a':		
		camera.RotateY(5.0);
		break;
	case 'd':		
		camera.RotateY(-5.0);
		break;
	case 'w':		
		camera.MoveForwards( -0.1 ) ;
		break;
	case 's':		
		camera.MoveForwards( 0.1 ) ;
		break;
	case 'x':		
		camera.RotateX(5.0);
		break;
	case 'y':		
		camera.RotateX(-5.0);
		break;
	case 'c':		
		camera.StrafeRight(-0.1);
		break;
	case 'v':		
		camera.StrafeRight(0.1);
		break;
	case 'f':
		camera.Move(camera.ReturnVector3D(0.0,-0.3,0.0));
		break;
	case 'r':
		camera.Move(camera.ReturnVector3D(0.0,0.3,0.0));
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300,300);
	glutCreateWindow("camera");
	camera.Move( camera.ReturnVector3D(0.0, 0.0, 3.0 ));
	camera.MoveForwards( 1.0 );
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyDown);
	glutMainLoop();
	return 0;             
}
