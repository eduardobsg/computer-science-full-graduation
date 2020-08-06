#ifndef __MOVIMENT_H__
#define __MOVIMENT_H__

#include <GL/glut.h>
#include "glm.h"

#include <iostream>
#include <cmath>  

#define PI 3.14159265

/*
Moviment:

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

//---------------------------------------------------------------
//CMoviment
//---------------------------------------------------------------
class CMoviment
{
	//---------------------------------------------------------------
	//Variables
	//---------------------------------------------------------------	
	protected:		
		Vector3D Position;
		Vector3D ViewDir;		
		GLfloat RotatedX;
		GLfloat RotatedY;
		GLfloat RotatedZ;	
		GLfloat Speed;
	
	//---------------------------------------------------------------
	//Methods
	//---------------------------------------------------------------
	public: 
		//Constructor
		CMoviment();
		
		//Destructor
		~CMoviment();
		
		//Setters		 
		void SetPositionX(GLfloat _x){ this->Position.x = _x; }
		void SetPositionY(GLfloat _y){ this->Position.y = _y; }
		void SetPositionZ(GLfloat _z){ this->Position.z = _z; }
		void SetSpeed(GLfloat _Speed){ this->Speed = _Speed; }								

		void SetRotatedX(GLfloat _RotatedX){ this->RotatedX = _RotatedX; }
		void SetRotatedY(GLfloat _RotatedY){ this->RotatedY = _RotatedY; }
		void SetRotatedZ(GLfloat _RotatedZ){ this->RotatedZ = _RotatedZ; }
				
		void SetPosition(GLfloat, GLfloat, GLfloat);										
		void SetViewDir(GLfloat, GLfloat, GLfloat);		
		
		//Getters		
		GLfloat GetPositionX(void){ return this->Position.x; }
		GLfloat GetPositionY(void){ return this->Position.y; }
		GLfloat GetPositionZ(void){ return this->Position.z; }	
		
		GLfloat GetViewDirX(void){ return this->ViewDir.x; }
		GLfloat GetViewDirY(void){ return this->ViewDir.y; }
		GLfloat GetViewDirZ(void){ return this->ViewDir.z; }
			
		GLfloat GetRotatedX(void){ return this->RotatedX; }
		GLfloat GetRotatedY(void){ return this->RotatedY; }
		GLfloat GetRotatedZ(void){ return this->RotatedZ; }
		
		GLfloat GetSpeed(void){ return this->Speed; }
	
		//For moviment
		void GetViewDir(void);
		void RenderCamera(void);	
		
		void RotateX(GLfloat);
		void RotateY(GLfloat);
		void RotateZ(GLfloat);
		
		void UpdateSpeed(GLfloat);
		void MoveForwardsBackwards(GLfloat);
		void MoveUpDown(GLfloat);
		void MoveLeftRight(GLfloat);
};


//---------------------------------------------------------------
//MMoviment
//---------------------------------------------------------------
class MMoviment
{
	//---------------------------------------------------------------
	//Variables
	//---------------------------------------------------------------	
	protected:		
		Vector3D Position;
		Vector3D ViewDir;		
		GLfloat RotatedX;
		GLfloat RotatedY;
		GLfloat RotatedZ;	
		GLfloat Speed;
	
	//---------------------------------------------------------------
	//Methods
	//---------------------------------------------------------------
	public: 
		//Constructor
		MMoviment();
		
		//Destructor
		~MMoviment();
		
		//Setters		 
		void SetPositionX(GLfloat _x){ this->Position.x = _x; }
		void SetPositionY(GLfloat _y){ this->Position.y = _y; }
		void SetPositionZ(GLfloat _z){ this->Position.z = _z; }
		void SetSpeed(GLfloat _Speed){ this->Speed = _Speed; }
		
		void SetRotatedX(GLfloat _RotatedX){ this->RotatedX = _RotatedX; }
		void SetRotatedY(GLfloat _RotatedY){ this->RotatedY = _RotatedY; }
		void SetRotatedZ(GLfloat _RotatedZ){ this->RotatedZ = _RotatedZ; }		
		void SetPosition(GLfloat, GLfloat, GLfloat);										
		void SetViewDir(GLfloat, GLfloat, GLfloat);										
		
		//Getters		
		GLfloat GetPositionX(void){ return this->Position.x; }
		GLfloat GetPositionY(void){ return this->Position.y; }
		GLfloat GetPositionZ(void){ return this->Position.z; }
		Vector3D GetPosition(void){ return this->Position; }		
		GLfloat GetViewDirX(void){ return this->ViewDir.x; }
		GLfloat GetViewDirY(void){ return this->ViewDir.y; }
		GLfloat GetViewDirZ(void){ return this->ViewDir.z; }				
		GLfloat GetRotatedX(void){ return this->RotatedX; }
		GLfloat GetRotatedY(void){ return this->RotatedY; }
		GLfloat GetRotatedZ(void){ return this->RotatedZ; }
		GLfloat GetSpeed(void){ return this->Speed; }
	
		//For moviment
		void GetViewDir(void);
		void RenderModel(void);	
		
		void RotateX(GLfloat);
		void RotateY(GLfloat);
		void RotateZ(GLfloat);
		
		void UpdateSpeed(GLfloat);
		void MoveForwards();
		void MoveUpDown(GLfloat);
		void MoveLeftRight(GLfloat);
};
#endif
