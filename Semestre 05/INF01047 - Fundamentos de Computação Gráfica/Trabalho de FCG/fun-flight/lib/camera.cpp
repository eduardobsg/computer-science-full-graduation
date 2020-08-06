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
	cout << "Camera " << this->CameraName << " has been deleted.\n" << endl;
}


/* Initializes the camera
*/
void Camera::InitCamera()
{
	if(this->CameraView == true)
	{
		//Perspective camera	
		PerspAngle = 30.0; //open angle for perspective projection
		PerspNear = 0.0001;
		PerspFar = 100.0;
		
		this->EyeX = 0.0;
		this->EyeY = 5.0; 
		this->EyeZ = 20.0;
		this->AtX = -10.0;
		this->AtY = 10.0; 
		this->AtZ = 0.0;
		this->UpX = 0.0;
		this->UpY = 1.0; 
		this->UpZ = 0.0;	
	}
	else
	{
		//Orthographic camera
		OrthoMinX = -5.00;
		OrthoMaxX = 5.00;
		OrthoMinY = -5.00;
		OrthoMaxY = 5.00;
		OrthoNearPlane = 0.0; 
		OrthoFarPlane = 240.0;	
		OrthoInc = 0.0; 	
		
		this->EyeX = 0.0;
		this->EyeY = 40.0; 
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
void Camera::SetOrthoCamera(GLfloat _OrthoMinX, GLfloat _OrthoMaxX,
						    GLfloat _OrthoMinY, GLfloat _OrthoMaxY,
						    GLfloat _OrthoNearPlane, GLfloat _OrthoFarPlane,
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
void Camera::SetPerspCamera(GLfloat _PerspAngle, GLfloat _PerspAspect, 
						    GLfloat _PerspNear, GLfloat _PerspFar)
{
	this->PerspAngle = _PerspAngle;
	this->PerspAspect = _PerspAspect;
	this->PerspNear = _PerspNear;
	this->PerspFar = _PerspFar; 
}
	



