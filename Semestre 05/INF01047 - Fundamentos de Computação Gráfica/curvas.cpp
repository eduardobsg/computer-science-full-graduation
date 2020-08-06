//Aula 17 - Modelagem de Curvas e Superfícies Paramétricas

#include <GL/glut.h>

GLfloat ctrlpoints[4][3] = { {-4.0/5, -4.0/5, 0.0}, {-2.0/5, 4.0/5, 0.0},
							 {2.0/5, -4.0/5, 0.0}, {4.0/5, 4.0/5, 0.0} };
							 
void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glBegin(GL_LINE_STRIP);
		for(int i = 0; i <= 30; i++)
			glEvalCoord1f((GLfloat) i/30.0);
	glEnd();
	
	/* The following code displays the controls points as dots. */
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
		for(int i = 0; i < 4; i++)
			glVertex3fv(&ctrlpoints[i][0]);
	glEnd();
	
	glFlush();		
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Curves");

    glutDisplayFunc(display);
    init();

    glutMainLoop();
    
    return 0;
}
