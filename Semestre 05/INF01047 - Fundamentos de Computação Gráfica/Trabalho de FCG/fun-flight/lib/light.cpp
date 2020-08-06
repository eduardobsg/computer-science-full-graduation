#include "light.h"

#define ANGLE_PER_DAY 1//360*DAY_SPEED/DAY_TIME_UNITS

/* Constructor of an Model. 
*/
Light::Light() 
{
}


/* Destructor of the Model  
*/
Light::~Light()
{
	cout << "Light has been deleted." << endl;
}

/* Initializes the light
*/
void Light::InitLight(char* _name,
		      str_ambient _ambient, 
		      str_diffuse _diffuse, 
		      str_specular _specular, 
		      str_position _position)
{
	this->name = _name;
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;
	this->position = _position;
}


/* Setups the light's attributes
*/
void Light::SetLight(GLfloat _transx, GLfloat _transy, GLfloat _transz, 
				     GLfloat _rotx, GLfloat _roty, GLfloat _rotz)
{
	this->transx = _transx;
	this->transy = _transy;
	this->transz = _transz;

	this->rotx = _rotx;
	this->roty = _roty;
	this->rotz = _rotz;
}

// Puts the light at location specified by it's contents

void Light::PlaceLight()
{	
	glPushMatrix();
		glLoadIdentity();

		//Sets the position of the light in the world 
		//glTranslatef(this->transx, this->transy, this->transz);
	
		//Do translation around the origin
		glRotated ((GLdouble) this->rotx, 1.0, 0.0, 0.0);
		glRotated ((GLdouble) this->roty, 0.0, 1.0, 0.0);
		glRotated ((GLdouble) this->rotz, 0.0, 0.0, 1.0);	

		//Scale the light according to the size passed as a parameter
        //glScalef(this->scalex, this->scaley, this->scalez);
    
		glLightfv (GL_LIGHT0, GL_POSITION, (GLfloat[4]) {this->GetPositionx(), this->GetPositiony(), 
			this->GetPositionz(), this->GetPositionw()});
	glPopMatrix();
}

//------------------------------------------------------------------------------
// Function: void lighting()
// Sets lighting parameters
//------------------------------------------------------------------------------
void Light::lighting()
{
	this->SetRotateZ(ANGLE_PER_DAY + this->GetRotateZ());
		if(this->GetRotateZ() > 360.0) 
			this->SetRotateZ(0.0);
	this->PlaceLight();
}



















