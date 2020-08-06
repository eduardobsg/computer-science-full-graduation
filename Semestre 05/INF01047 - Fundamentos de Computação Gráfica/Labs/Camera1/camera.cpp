#include "camera.h"
#include <cmath>
#include <iostream>

using namespace std;

Camera::Camera()
{
	//Init with standard OGL values:
	this->Position = ReturnVector3D(0.0, 0.0, 0.0);
	this->ViewDir = ReturnVector3D(0.0,	0.0, -1.0);
	this->ViewDirChanged = false;

	//Only to be sure:
	this->RotatedX = this->RotatedY = this->RotatedZ = 0.0;
}

void Camera::GetViewDir(void)
{
	Vector3D Step1, Step2;

	//Rotate around Y-axis:
	Step1.x = cos((this->RotatedY + 90.0) * PI/180);
	Step1.z = -sin((this->RotatedY + 90.0) * PI/180);

	//Rotate around X-axis:
	double cosX = cos(this->RotatedX * PI/180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(this->RotatedX * PI/180);

	//Rotation around Z-axis not yet implemented, so:
	this->ViewDir = Step2;
}
void Camera::Move(Vector3D Direction)
{
	this->AddVector3DToVector3D(&Position, &Direction);
}

void Camera::RotateX(GLfloat Angle)
{
	this->RotatedX += Angle;
	this->ViewDirChanged = true;
}

void Camera::RotateY(GLfloat Angle)
{
	this->RotatedY += Angle;
	this->ViewDirChanged = true;
}

void Camera::RotateZ(GLfloat Angle)
{
	this->RotatedZ += Angle;
	this->ViewDirChanged = true;
}


void Camera::Render(void)
{
	glRotatef(-this->RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-this->RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-this->RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef(-this->Position.x, -this->Position.y, -this->Position.z);	
}

void Camera::MoveForwards(GLfloat Distance)
{
	if(this->ViewDirChanged) 
		this->GetViewDir();
	Vector3D MoveVector;
	MoveVector.x = this->ViewDir.x * -Distance;
	MoveVector.y = this->ViewDir.y * -Distance;
	MoveVector.z = this->ViewDir.z * -Distance;
	this->AddVector3DToVector3D(&Position, &MoveVector);
}

void Camera::StrafeRight(GLfloat Distance)
{
	if(this->ViewDirChanged) 
		this->GetViewDir();
	Vector3D MoveVector;
	MoveVector.z = -this->ViewDir.x * -Distance;
	MoveVector.y = 0.0;
	MoveVector.x = this->ViewDir.z * -Distance;
	this->AddVector3DToVector3D(&Position, &MoveVector);
}

Vector3D Camera::ReturnVector3D(GLfloat x, GLfloat y, GLfloat z)
{
	Vector3D tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

void Camera::AddVector3DToVector3D(Vector3D *Dst, Vector3D *V)
{
	Dst->x += V->x;
	Dst->y += V->y;
	Dst->z += V->z;
}
