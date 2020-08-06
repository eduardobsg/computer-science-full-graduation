#include "camera.h"

/* Constructor of the camera
*/
Camera::Camera() 
{
	this->CameraView = true; //creates the camera object assuming a perspective camera
}


/* Destructor of the camera
*/
Camera::~Camera()
{
	cout << "Camera " << this->CameraName << " has been deleted." << endl;
}


/* Initializes the camera
*/
void Camera::InitCamera()
{
	if(this->CameraView == true)
	{
		//Perspective camera	
		PerspAngle = 30; //open angle for perspective projection
		PerspNear = 1.0;
		PerspFar = 100.0;
		
		this->EyeX = 0.0;
		this->EyeY = 2.0; 
		this->EyeZ = 15.0;
		this->AtX = 0.0;
		this->AtY = 0.0; 
		this->AtZ = 0.0;
		this->UpX = 0.0;
		this->UpY = 1.0; 
		this->UpZ = 0.0;	
	}
	else
	{
		//Orthographic camera
		OrthoMinX = -10.00;
		OrthoMaxX = 10.00;
		OrthoMinY = -10.00;
		OrthoMaxY = 10.00;
		OrthoNearPlane = 0.0; 
		OrthoFarPlane = 240.0;	
		OrthoInc = 0; 	
		
		this->EyeX = 0.0;
		this->EyeY = 100.0; 
		this->EyeZ = 0.0;
		this->AtX = 0.0;
		this->AtY = 0.0; 
		this->AtZ = 0.0;
		this->UpX = 0.0;
		this->UpY = 0.0; 
		this->UpZ = -1.0;		
	}
}


/* Chooses the camera view, between perspective and orthographic
 * Whenever view = true, the camera is set as perspective
 * Whenever view = false, the camera is set as orthographic
*/
void Camera::SetCameraView(bool view = true)
{
	if(view == true)
		this->CameraView = true; //camera view set to perspective
	else
		this->CameraView = false; //camera view set to orthographic
		
	this->InitCamera();
}


/* Set the orthographic camera attributes
*/
void Camera::SetOrthoCam(GLdouble _OrthoMinX, GLdouble _OrthoMaxX,
						   GLdouble _OrthoMinY, GLdouble _OrthoMaxY,
						   GLdouble _OrthoNearPlane, GLdouble _OrthoFarPlane,
						   GLint _OrthoInc)
{
	this->OrthoMinX = _OrthoMinX;
	this->OrthoMaxX = _OrthoMaxX;
	this->OrthoMinY = _OrthoMinY;
	this->OrthoMaxY = _OrthoMaxY;
	this->OrthoNearPlane = _OrthoNearPlane; 
	this->OrthoFarPlane = _OrthoFarPlane;	 
	this->OrthoInc = _OrthoInc;	
}

/* Set the perspective camera attributes						 
*/
void Camera::SetPerspCam(GLdouble _PerspAngle, GLdouble _PerspAspect, 
						   GLdouble _PerspNear, GLdouble _PerspFar)
{
	this->PerspAngle = _PerspAngle;
	this->PerspAspect = _PerspAspect;
	this->PerspNear = _PerspNear;
	this->PerspFar = _PerspFar; 
}
	
	
/* Set the gluLookAt attributes
*/
void Camera::SetCamPosition(GLdouble _EyeX, GLdouble _EyeY, GLdouble _EyeZ,
							  GLdouble _AtX, GLdouble _AtY, GLdouble _AtZ,
							  GLdouble _UpX, GLdouble _UpY, GLdouble _UpZ)
{
		this->EyeX = _EyeX;
		this->EyeY = _EyeY; 
		this->EyeZ = _EyeZ;
		this->AtX = _AtX;
		this->AtY = _AtY; 
		this->AtZ = _AtZ;
		this->UpX = _UpX;
		this->UpY = _UpY; 
		this->UpZ = _UpZ;		
}











