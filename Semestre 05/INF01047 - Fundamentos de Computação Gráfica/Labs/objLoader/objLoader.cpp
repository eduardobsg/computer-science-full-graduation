//Help: http://www.3dcodingtutorial.com/Working-with-3D-models/Importing-the-model-in-C++.html

#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>
//#include <string>
//#include <vector>

#include "lib/model.h"
#include "lib/camera.h"

using namespace std;

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------

//Cameras
Camera camera;

//Models
Model model;


//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

/* Prototype: void init(void)
 * Initialization function
*/
void init(int argc, char **argv) 
{
	//Sets black color without any transparency
   	glClearColor(0.0, 0.0, 0.0, 0.0);   

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	
    //Enables Z buffer	
   	glEnable(GL_DEPTH_TEST);
   	
   	if(argc < 1)
    {
        cout << "null parameter" << endl;
        exit(0);
    }       		   	
	
	//Model
	model.InitModelFiles(argv[1], argv[3], argv[2]);
	
	//Cameras - Perspective
	camera.SetCameraView(true);
	camera.InitCamera();
}


/* Sets the camera to perspective viewing. Uses as global variable
 * fAspect, calculated in function void reshape(int w, int h) and
 * camera[ORTHOGRAPHIC], initialized when the perspective viewing is selected
*/  
void PerspectiveViewport(GLint width, GLint height)
{
	cout << "Setting Perspective camera." << endl;

	//Sets the viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	camera.SetPerspAspect( (GLfloat)width / (GLfloat)height );

	//Speficies the manipulation of the projection matrix
	glMatrixMode(GL_PROJECTION);
	
	//Initializes projection matrix with the identity matrix
	glLoadIdentity();

	//Specifies perspective projection
    //void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar); 
	gluPerspective(camera.GetPerspAngle(),
				   camera.GetPerspAspect(), 
				   camera.GetPerspNear(),
				   camera.GetPerspFar());

	//Specifies the observer and target positions
	/* void gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, 
	   				  GLdouble centerX, GLdouble centerY, GLdouble centerZ, 
	   				  GLdouble upX, GLdouble upY, GLdouble upZ)*/
	gluLookAt(camera.GetEyeX(), camera.GetEyeY(), 
			  camera.GetEyeZ(), camera.GetAtX(), 
			  camera.GetAtY(), camera.GetAtZ(), 
			  camera.GetUpX(), camera.GetUpY(), 
			  camera.GetUpZ());
			  
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();	
	
	//Draw
	glPushMatrix();
		model.DrawModel();
	glPopMatrix();	
}


/* Sets the camera to perspective viewing. Uses as global variable
 * camera[ORTHOGRAPHIC], initialized when the orthographic viewing is selected
*/  
void OrthoViewport(GLint width, GLint height)
{
	cout << "Setting Orthographic camera." << endl; 
 
 	//Sets the viewport
 	glViewport(0.75*width, 0.75*height, 0.25*width, 0.25*height); 
 	
    //Speficies the manipulation of the projection matrix
	glMatrixMode(GL_PROJECTION);
	
	//Initializes projection matrix with the identity matrix
	glLoadIdentity();
 
    //Specifies orthographic projection
    //void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal);
	glOrtho(camera.GetOrthoMinX() - camera.GetOrthoInc(),
            camera.GetOrthoMaxX() + camera.GetOrthoInc(),
            camera.GetOrthoMinY() - camera.GetOrthoInc(),
            camera.GetOrthoMaxY() - camera.GetOrthoInc(),
            camera.GetOrthoNearPlane(), camera.GetOrthoFarPlane()); //Sets the camera viewport and orthographic visualization    

	//Specifies the observer and target positions
	gluLookAt(camera.GetEyeX(), camera.GetEyeY(), 
			  camera.GetEyeZ(), camera.GetAtX(), 
			  camera.GetAtY(), camera.GetAtZ(), 
			  camera.GetUpX(), camera.GetUpY(), 
			  camera.GetUpZ());
			  
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	
	//Draw box
	glPushMatrix();
		model.DrawModel();
	glPopMatrix();
}


/* Prototype: void display(void)
 * Callback function for glutDisplayFunc()
 * Draw the models on the scene.
*/
void display(void)
{ 	
	//Clears the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     
	
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
		
	if(camera.GetCameraView() == true)
		PerspectiveViewport(width, height);
	else
		OrthoViewport(width, height);

	//Sets a delay to draw the scene
	usleep(10000); 
	
	//Garantees the execution of the drawing commands
	glutSwapBuffers();  
}


/* Prototype: void keyboard(unsigned char key, int x, int y)
 * Callback function for glutKeyboardFunc().
 * Handles the pressed keys of the keyboard
*/ 
void keyboard(unsigned char key, int x, int y)
{
	switch(key) 
	{
		case 27: //ESC key
			exit(0);
         	break;
		case 'r':         
		 	cout << "Reset rotation all models" << endl;
			model.SetRotateX(0.0);
			model.SetRotateY(0.0);
			model.SetRotateZ(0.0);
         	glutPostRedisplay();
         	break;	
        
        //Rotation for the box 	
	  	case 'q':  
	  		cout << "Rotation around x axis" << endl;       
		  	model.SetRotateX(5.0 + model.GetRotateX());
				if(model.GetRotateX() > 360.0) 
					model.SetRotateX(0.0);
         	glutPostRedisplay();
         	break;
	  	case 'w':  
	  		cout << "Rotation around y axis" << endl;       
		  	model.SetRotateY(5.0 + model.GetRotateY());
				if(model.GetRotateY() > 360.0) 
					model.SetRotateY(0.0);
         	glutPostRedisplay();
         	break;
	 	case 'e':         
		 	cout << "Rotation around z axis" << endl;
			model.SetRotateZ(5.0 + model.GetRotateZ());
				if(model.GetRotateZ() > 360.0) 
					model.SetRotateZ(0.0);
         	glutPostRedisplay();
         	break;	
   	}
}


/* Prototype: handleMouse(int button, int state, int x, int y)
 * Callback function for glutMouseFunc().
 * Handles the pressed keys of the mouse
*/ 
void handleMouse(int button, int state, int x, int y)
{
	int increment = 10;	
	
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			//Zoom-in
            if(camera.GetPerspAngle() >= 10.0)
				camera.SetPerspAngle( camera.GetPerspAngle() - increment );
            camera.SetOrthoInc( camera.GetOrthoInc() - increment/5 ); 
    		}
		}

	if(button == GLUT_RIGHT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			//Zoom-out
			if(camera.GetPerspAngle() <= 150)
				camera.SetPerspAngle( camera.GetPerspAngle() + increment );
            camera.SetOrthoInc( camera.GetOrthoInc() + increment/5 );  
		}
	}
	
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
   	cout << "Initializing..." << endl;	
   	
	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	
	//Set the position of the window
	glutInitWindowPosition(0, 100); 
	
	//Set the windows size in pixels
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Main Window");
	
	//GLUT functions
   	glutDisplayFunc(display); 
   	glutIdleFunc(display);
   	glutKeyboardFunc(keyboard);
   	glutMouseFunc(handleMouse);
   	
 	init(argc, argv);
   	
   	glutMainLoop();
   	
   	return 0;
}

