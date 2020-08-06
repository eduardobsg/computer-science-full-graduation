/*
 *------------------------------------------------------------
 *		solar.c
 *		Marcelo Walter
 *		may, 99
 *------------------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>

/* DEFINES */
#define		X		0
#define		Y		1
#define		Z		2
#define		XYZ		3
#define		TRUE	1
#define		FALSE	0

/*  Prototypes for module global functions */

static void initWin();
static void winDisplay();
static void winKbd( unsigned char, int, int );
static void winReshape( int, int );
static void winMotion (int x, int y);
static void winMouse( int button, int state, int x, int y );
static void drawAxes( double scale);
static void dayAdd(void);
static void daySubtract(void);
static void yearAdd(void);
static void yearSubtract(void);
static void specialKbd( int key, int x, int y);
static void dayAddMoon(void);
static void daySubtractMoon(void);


/* Global Variables */

/* Module global rotation */
static float    rot[XYZ] = { 37.0, -50.0, 3.0 };

static int		day = 0;
static int		year = 0;
static int		moonday = 0;
static int		animation = FALSE;
static float	space_ship = 0.0;

/* current mouse position */
static int mouseX;

/* mouse button pressed */
static int mouseButton;

/*
 *----------------------------------------------------------
 *	main
 *----------------------------------------------------------
 */
int main( int argc, char *argv[] )
{
	
	glutInitWindowPosition( 100, 100);
	glutInitWindowSize( 400, 400 );
	
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	initWin();
	glutMainLoop();
	return 1;
	
}


/*
 *----------------------------------------------------------
 *	initWin
 *	This function initializes the OpenGL window 
 *----------------------------------------------------------
 */
static void initWin()
{
	
	glutCreateWindow( "Solar System - MW" );
	
	glutDisplayFunc( winDisplay );	/*  Window callbacks */
	glutKeyboardFunc( winKbd );
	glutReshapeFunc( winReshape );
	glutMouseFunc( winMouse );
	glutMotionFunc( winMotion );
	glutSpecialFunc( specialKbd );
	
	glEnable( GL_DEPTH_TEST );		/* Ensure proper Z-buffering */
	glDepthFunc(GL_LESS);
	
	glClearColor( 1, 1, 1, 0 );		/*  Default background colour */
	
}

/*
 *----------------------------------------------------------
 *	winMotion
 *----------------------------------------------------------
 */
static void winMotion (int x, int y)
{
	
	rot[mouseButton] -= (float)(mouseX - x) / 5.0;
	
	mouseX = x;
	glutPostRedisplay();
}

/*
 *----------------------------------------------------------
 *	winMouse
 *----------------------------------------------------------
 */
static void winMouse( int button, int state, int x, int y )
{
	if (state == GLUT_DOWN){
		mouseX = x;
		switch( button ) {
			case GLUT_LEFT_BUTTON:		/* Save button as array index */
				mouseButton = Y;
				break;
				
			default:
				mouseButton  = -1;
				break;
      	}
	}
}

/*
 *----------------------------------------------------------
 *	winDisplay
 *	This function handles window redisplay requests
 *----------------------------------------------------------
 */
static void winDisplay()
{
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glColor3f( 0.0, 0.0, 0.0 );	/*  Set colour to black */
	
	glPushMatrix();
	  glRotatef( rot[Y], 0.0, 1.0, 0.0 );
	  drawAxes(2.0);
	  glColor3f( 0.0, 0.0, 0.0 );		/*  Set colour to black */
	  glutWireSphere(1.0, 15, 15);		/* draw sun */
	  glRotatef( (GLfloat) year, 0.0, 1.0, 0.0);
	
	  glPushMatrix();
		glTranslatef( 2.0, 0.0, 0.0);
		glRotatef( (GLfloat) day, 0.0, 1.0, 0.0);
		drawAxes(0.9);
		glColor3f( 0.0, 1.0, 0.0 );	/*  Set colour to black */
		glutWireSphere(0.4, 15, 15);	/* draw planet */
	  glPopMatrix();
	
	  glPushMatrix();
		glTranslatef( -2.5, 0.0, 0.0);
		glRotatef( (GLfloat) day, 0.0, 1.0, 0.0);
		drawAxes(0.8);
		glColor3f( 0.0, 0.0, 1.0 );	/*  Set colour to  */
		glutWireSphere(0.3, 15, 15);	/* draw another planet */
	  
		glPushMatrix();
			glTranslatef(1.0,0.0,0.0);
			glRotatef( (GLfloat) moonday, 0.0, 1.0, 0.0);
			drawAxes(0.3);
			glColor3f( 0.0, 1.0, 1.0 );	/*  Set colour to cyan */
			glTranslatef(space_ship,0,0);
			glutWireSphere(0.1, 15, 15);	/* draw a moon */
		glPopMatrix();
	
	  glPopMatrix();
	
	
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
	
}
/*
 *----------------------------------------------------------
 *	specialKbd
 *	This function handles special keyboard strokes
 *	key:	Key pressed by user
 *	x:	X-position of mouse
 *	y:	Y-position of mouse
 *----------------------------------------------------------
 */
static void specialKbd( int key, int x, int y)
{
	switch ( key ){
		case GLUT_KEY_LEFT:
			yearSubtract();
			break;
		case GLUT_KEY_RIGHT:
			yearAdd();
			break;
		case GLUT_KEY_UP:
			dayAdd();
			break;
		case GLUT_KEY_DOWN:
			daySubtract();
			break;
		case GLUT_KEY_F5:
			dayAddMoon();
			break;
		case GLUT_KEY_F6:
			daySubtractMoon();
			break;
		case GLUT_KEY_F10:
			yearAdd();
			dayAdd();
			dayAddMoon();
			break;
		case GLUT_KEY_F3:
			space_ship += 0.05;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

/*
 *------------------------------------
 *	Routine for animation
 *------------------------------------
 */
void myAnimation(void)
{
	int i;
	rot[Y] -= 10;
	yearAdd();
	dayAdd();
	dayAddMoon();
	for(i=0;i<10000000;i++);
	glutPostRedisplay();
}
/*
 *----------------------------------------------------------
 *	winKbd
 *	This function handles keyboard strokes
 *	key:	Key pressed by user
 *	x:	X-position of mouse
 *	y:	Y-position of mouse
 *----------------------------------------------------------
 */
static void winKbd( unsigned char key, int x, int y )
{
	switch( key ) {
		case 'q':			/*  Quit program */
		case 'Q':
			exit( 0 );
		case 'a':
		case 'A':
			animation=!animation;
			if(animation) glutIdleFunc(myAnimation);
			else  glutIdleFunc(NULL);
			break;
		case 'b':
		case 'B':
			yearAdd();
			dayAdd();
			dayAddMoon();
			break;
		default:
			break;
	}
	glutPostRedisplay();
	
}

/*
 *----------------------------------------------------------
 *	winReshape
 *	This function resets the viewport to cover the entire window
 *	w:	Current width of window
 *	h:	Current height of window
 *----------------------------------------------------------
 */
static void winReshape( int w, int h )
{
	glViewport( 0, 0, w, h );
	glMatrixMode( GL_PROJECTION );	
	glLoadIdentity();
	gluPerspective( 60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0 );
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	/* move initial default camera position away from origin */
	glTranslatef(0.0, 0.0, -7.0);
	glRotatef( rot[Z], 0.0, 0.0, 1.0 );
	glRotatef( rot[X], 1.0, 0.0, 0.0 );
	
}

/*
 *----------------------------------------------------------
 *	drawAxes
 *----------------------------------------------------------
 */
static void drawAxes(double scale)
{
	static float axes[4][XYZ] = {
		{0.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}
	};
	glPushMatrix();
	glColor3f( 1.0, 0.0, 0.0 );
	glScalef( scale, scale, scale );
	
	glRasterPos3f(axes[1][0], axes[1][1], axes[1][2]);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');
	glBegin( GL_LINES );
   	glVertex3fv( axes[0] );
   	glVertex3fv( axes[1] );
   	glEnd();
	
	glRasterPos3f(axes[2][0], axes[2][1], axes[2][2]);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
   	glBegin( GL_LINES );
   	glVertex3fv( axes[0] );
   	glVertex3fv( axes[2] );
   	glEnd();
	
	glRasterPos3f(axes[3][0], axes[3][1], axes[3][2]);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Z');
   	glBegin( GL_LINES );
   	glVertex3fv( axes[0] );
   	glVertex3fv( axes[3] );
   	glEnd();
	
	glPopMatrix();
}

/* add one day for planet */
void dayAdd(void)
{
	day = (day + 10) % 360;
}

/* subtract one day for planet */
void daySubtract(void)
{
	day = (day - 10) % 360;
}

/* add one day for moon */
void dayAddMoon(void)
{
	moonday = (moonday + 15) % 360;
}

/* subtract one day for moon */
void daySubtractMoon(void)
{
	moonday = (moonday - 15) % 360;
}

/* add one year */
void yearAdd(void)
{
	year = (year + 15) % 360;
}

/* subtract one year */
void yearSubtract(void)
{
	year = (year - 15) % 360;
}
