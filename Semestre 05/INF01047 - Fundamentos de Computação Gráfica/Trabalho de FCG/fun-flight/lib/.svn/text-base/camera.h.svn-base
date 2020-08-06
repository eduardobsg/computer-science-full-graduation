#ifndef __CAMERA_H__
#define __CAMERA_H__ 

#include <GL/glut.h>
#include "moviment.h"

#include <iostream>
#include <cmath> 

#define PI 3.14159265

/*
CAMERA movement:

Translation:
w : forwards
s : backwards
a : left
d : right
r : up
f : down

Rotation:
//Rotation around Y axis
q : turn left
e : turn right
//Rotation around X axis
z : turn left-down 
x : turn right-up
//Rotation around Z axis
t : turn up
g : turn down

*/

using namespace std;

enum CamerasIndex {ORTHOGRAPHIC = 0, PERSPECTIVE = 1};

class Camera
{
	//---------------------------------------------------------------
	//Variables
	//---------------------------------------------------------------	
	protected:
		bool CameraView; //Perspective: true (1), Orthographic: false (0)
		char *CameraName;
		
		//Perspective
		GLfloat PerspAspect;
		GLfloat PerspAngle; //open angle for perspective projection
		GLfloat PerspNear;
		GLfloat PerspFar; 
		
		//Orthographic
		GLfloat OrthoMinX;
		GLfloat OrthoMaxX;
		GLfloat OrthoMinY;
		GLfloat OrthoMaxY;
		GLfloat OrthoNearPlane; 
		GLfloat OrthoFarPlane;
		GLfloat OrthoInc; //increment for orthographic projection	
				
		//For gluLookAt
		GLfloat EyeX;
		GLfloat EyeY;
		GLfloat EyeZ;
		GLfloat AtX;
		GLfloat AtY;
		GLfloat AtZ;
		GLfloat UpX;
		GLfloat UpY;
		GLfloat UpZ;
		
		Vector3D Position;
		Vector3D ViewDir;		
		bool ViewDirChanged;
		GLfloat RotatedX, RotatedY, RotatedZ;	
	
	//---------------------------------------------------------------
	//Methods
	//---------------------------------------------------------------
	public: 
		CMoviment moviment;
	
		//Constructor
		Camera();
		
		//Destructor
		~Camera();
		
		//Setters
		void SetPerspAspect(GLfloat _PerspAspect){ this->PerspAspect = _PerspAspect; }
		void SetPerspAngle(GLfloat _PerspAngle){ this->PerspAngle = _PerspAngle; }
		void SetPerspNear(GLfloat _PerspNear){ this->PerspNear = _PerspNear; }
		void SetPerspFar(GLfloat _PerspFar){ this->PerspFar = _PerspFar; }
		
		void SetOrthoMinX(GLfloat _OrthoMinX){ this->OrthoMinX = _OrthoMinX; }
		void SetOrthoMaxX(GLfloat _OrthoMaxX){ this->OrthoMaxX = _OrthoMaxX; }
		void SetOrthoMinY(GLfloat _OrthoMinY){ this->OrthoMinY = _OrthoMinY; }
		void SetOrthoMaxY(GLfloat _OrthoMaxY){ this->OrthoMaxY = _OrthoMaxY; }
		void SetOrthoNearPlane(GLfloat _OrthoNearPlane){ this->OrthoNearPlane = _OrthoNearPlane; }
		void SetOrthoFarPlane(GLfloat _OrthoFarPlane){ this->OrthoFarPlane = _OrthoFarPlane; }
		void SetOrthoInc(GLfloat _OrthoInc){ this->OrthoInc = _OrthoInc; } 
				
		void SetEyeX(GLfloat _EyeX){ this->EyeX = _EyeX; }
		void SetEyeY(GLfloat _EyeY){ this->EyeY = _EyeY; }
		void SetEyeZ(GLfloat _EyeZ){ this->EyeZ = _EyeZ; }		
		void SetAtX(GLfloat _AtX){ this->AtX = _AtX; }
		void SetAtY(GLfloat _AtY){ this->AtY = _AtY; }
		void SetAtZ(GLfloat _AtZ){ this->AtZ = _AtZ; }		
		void SetUpX(GLfloat _UpX){ this->UpX = _UpX; }
		void SetUpY(GLfloat _UpY){ this->UpY = _UpY; }
		void SetUpZ(GLfloat _UpZ){ this->UpZ = _UpZ; }			
		
		//Setups the orthographic camera attributes
		void SetOrthoCamera(GLfloat, GLfloat, GLfloat, GLfloat,
						    GLfloat, GLfloat, GLint);
						 
		//Setups the perspective camera attributes						 
		void SetPerspCamera(GLfloat, GLfloat, GLfloat, GLfloat);	
		
		void SetCameraPosition(GLfloat, GLfloat, GLfloat);							
		 
			
		//Chooses the camera view, between perspective and orthographic	
		void SetCameraView(bool);
		
		//Getters
		GLfloat GetPerspAspect(void){ return this->PerspAspect; }
		GLfloat GetPerspAngle(void){ return this->PerspAngle; }
		GLfloat GetPerspNear(void){ return this->PerspNear; }
		GLfloat GetPerspFar(void){ return this->PerspFar; }
		
		GLfloat GetOrthoMinX(void){ return this->OrthoMinX; }
		GLfloat GetOrthoMaxX(void){ return this->OrthoMaxX; }
		GLfloat GetOrthoMinY(void){ return this->OrthoMinY; }
		GLfloat GetOrthoMaxY(void){ return this->OrthoMaxY; }
		GLfloat GetOrthoNearPlane(void){ return this->OrthoNearPlane; }
		GLfloat GetOrthoFarPlane(void){ return this->OrthoFarPlane; }
		GLfloat GetOrthoInc(void){ return this->OrthoInc; } 
				
		GLfloat GetEyeX(void){ return this->EyeX; }
		GLfloat GetEyeY(void){ return this->EyeY; }
		GLfloat GetEyeZ(void){ return this->EyeZ; }		
		GLfloat GetAtX(void){ return this->AtX; }
		GLfloat GetAtY(void){ return this->AtY; }
		GLfloat GetAtZ(void){ return this->AtZ; }		
		GLfloat GetUpX(void){ return this->UpX; }
		GLfloat GetUpY(void){ return this->UpY; }
		GLfloat GetUpZ(void){ return this->UpZ; }	
				
		bool GetCameraView(void){ return this->CameraView; }
		char * GetCameraName(void){ return this->CameraName; }
		
		GLfloat GetPositionX(void){ return this->Position.x; }
		GLfloat GetPositionY(void){ return this->Position.y; }
		GLfloat GetPositionZ(void){ return this->Position.z; }				
		
		//Initializes the camera
		void InitCamera();
	
		//For camera motion
		void GetViewDir(void);
		void Render(void);	
		
		void RotateX(GLfloat);
		void RotateY(GLfloat);
		void RotateZ(GLfloat);
		
		void Move(Vector3D);
		void MoveForwardsBackwards(GLfloat);
		void MoveUpDown(GLfloat);
		void MoveLeftRight(GLfloat);

		Vector3D ReturnVector3D(GLfloat, GLfloat, GLfloat);
		void AddVector3DToVector3D(Vector3D *, Vector3D *);
};

#endif
