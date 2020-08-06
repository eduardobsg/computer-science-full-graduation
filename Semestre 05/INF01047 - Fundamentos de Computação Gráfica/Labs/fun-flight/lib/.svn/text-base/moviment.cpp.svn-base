#include "moviment.h"


//---------------------------------------------------------------
//CMoviment
//---------------------------------------------------------------
CMoviment::CMoviment()
{
	this->Position.x = 0.0; 
	this->Position.y = 0.0;
	this->Position.z = 0.0;
	this->ViewDir.x = 0.0;
	this->ViewDir.y = 0.0;
	this->ViewDir.z = 0.0;
	this->RotatedX = this->RotatedY = this->RotatedZ = 0.0;
}


CMoviment::~CMoviment()
{
}


/* Set the gluLookAt attributes
*/
void CMoviment::SetPosition(GLfloat _x, GLfloat _y, GLfloat _z)
{
	this->Position.x = _x;
	this->Position.y = _y;		
	this->Position.z = _z;
}

void CMoviment::SetViewDir(GLfloat _x, GLfloat _y, GLfloat _z)
{
	this->ViewDir.x = _x;
	this->ViewDir.y = _y;		
	this->ViewDir.z = _z;
}

void CMoviment::RotateX(GLfloat Angle)
{
	if(fabs(this->ViewDir.x) > fabs(this->ViewDir.z))
	{
		if(this->ViewDir.x > 0)
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ -= Angle;
				
		if(this->ViewDir.x < 0)		
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ += Angle;

		if(this->RotatedZ > 90)
			this->RotatedZ = 90;
		else if(this->RotatedZ < -90)
			this->RotatedZ = -90;	
		this->GetViewDir();	
	}
	else
	{
		if(this->ViewDir.z > 0)
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX += Angle;
				
		if(this->ViewDir.z < 0)		
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX -= Angle;

		if(this->RotatedX > 90)
			this->RotatedX = 90;
		else if(this->RotatedX < -90)
			this->RotatedX = -90;	
		this->GetViewDir();	
	}
}

void CMoviment::RotateY(GLfloat Angle)
{
	if(this->RotatedY <= 360 && this->RotatedY >= 0)
	{
		this->RotatedY += Angle;
		if(this->RotatedY > 360)
			this->RotatedY = 5;
		else if(this->RotatedY < 0)
			this->RotatedY = 355;	
		this->GetViewDir();	
	}
}

void CMoviment::RotateZ(GLfloat Angle)
{
	if(fabs(this->ViewDir.x) > fabs(this->ViewDir.z))
	{
		if(this->ViewDir.x > 0)
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX += Angle;
				
		if(this->ViewDir.x < 0)		
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX -= Angle;

		if(this->RotatedX > 90)
			this->RotatedX = 90;
		else if(this->RotatedX < -90)
			this->RotatedX = -90;	
		this->GetViewDir();	
	}
	else
	{
		if(this->ViewDir.z > 0)
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ += Angle;
				
		if(this->ViewDir.z < 0)		
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ -= Angle;

		if(this->RotatedZ > 90)
			this->RotatedZ = 90;
		else if(this->RotatedZ < -90)
			this->RotatedZ = -90;	
		this->GetViewDir();	
	}
}


void CMoviment::GetViewDir(void)
{
	Vector3D Step1, Step2;

	//Rotate around Y-axis:
	Step1.x = sin((this->RotatedY) * PI/180);
	Step1.z = cos((this->RotatedY) * PI/180);

	//Rotate around X-axis:
	Step2.x = Step1.x * cos(this->RotatedX * PI/180);
	Step2.z = Step1.z * cos(this->RotatedX * PI/180);
	
	float cosY = cos(this->RotatedY * PI/180);
	Step2.y = sin(this->RotatedX * PI/180) * -fabs(cosY + 0.1) / (cosY + 0.1);
	
	//Rotation around Z-axis not yet implemented, so:
	this->ViewDir = Step2;
}

void CMoviment::RenderCamera(void)
{
	glRotatef(-this->RotatedX, 1.0, 0.0, 0.0);
	glRotatef(-this->RotatedY, 0.0, 1.0, 0.0);
	glRotatef(-this->RotatedZ, 0.0, 0.0, 1.0);
	glTranslatef(-this->Position.x, -this->Position.y, -this->Position.z);		
}


void CMoviment::UpdateSpeed(GLfloat _Speed)
{
	this->Speed += _Speed;
	if(this->Speed >= 0)
		this->Speed = 0;		
}


void CMoviment::MoveForwardsBackwards(GLfloat Distance)
{
	this->GetViewDir();
	if(Distance == 0.0)
	{
		this->Position.x += this->ViewDir.x * this->Speed;
		this->Position.y += this->ViewDir.y * this->Speed;
		this->Position.z += this->ViewDir.z * this->Speed;
	}
	else
	{
		this->Position.x += this->ViewDir.x * Distance;
		this->Position.y += this->ViewDir.y * Distance;
		this->Position.z += this->ViewDir.z * Distance;
	}
}


void CMoviment::MoveLeftRight(GLfloat Distance)
{
	this->GetViewDir();
	this->Position.z += -this->ViewDir.x * +Distance;
	this->Position.y += 0.0;
	this->Position.x += this->ViewDir.z * +Distance;
}

void CMoviment::MoveUpDown(GLfloat Distance)
{
	this->GetViewDir();
	this->Position.z += 0.0;
	this->Position.y += Distance;
	this->Position.x += 0.0;
}


//---------------------------------------------------------------
//MMoviment
//---------------------------------------------------------------
MMoviment::MMoviment()
{
	this->Position.x = 0.0;
	this->Position.y = 0.0;
	this->Position.z = 0.0;
	this->ViewDir.x = 0.0;
	this->ViewDir.y = 0.0;
	this->ViewDir.z = 0.0;
	this->RotatedX = this->RotatedY = this->RotatedZ = 0.0;
}


MMoviment::~MMoviment()
{
}


/* Set the gluLookAt attributes
*/
void MMoviment::SetPosition(GLfloat _x, GLfloat _y, GLfloat _z)
{
	this->Position.x = _x;
	this->Position.y = _y;		
	this->Position.z = _z;
}

void MMoviment::SetViewDir(GLfloat _x, GLfloat _y, GLfloat _z)
{
	this->ViewDir.x = _x;
	this->ViewDir.y = _y;		
	this->ViewDir.z = _z;
}


void MMoviment::GetViewDir(void)
{
	Vector3D Step1, Step2;

	//Rotate around Y-axis:
	Step1.x = sin((this->RotatedY) * PI/180);
	Step1.z = cos((this->RotatedY) * PI/180);

	//Rotate around X-axis:
	Step2.x = Step1.x * cos(this->RotatedX * PI/180);
	Step2.z = Step1.z * cos(this->RotatedX * PI/180);
	
	float cosY = cos(this->RotatedY * PI/180);
	Step2.y = sin(this->RotatedX * PI/180) * -fabs(cosY + 0.1) / (cosY + 0.1);
	
	//Rotation around Z-axis not yet implemented, so:
	this->ViewDir = Step2;
}


void MMoviment::RotateX(GLfloat Angle)
{
	if(fabs(this->ViewDir.x) > fabs(this->ViewDir.z))
	{
		if(this->ViewDir.x > 0)
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ += Angle;
				
		if(this->ViewDir.x < 0)		
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ -= Angle;

		if(this->RotatedZ > 90)
			this->RotatedZ = 90;
		else if(this->RotatedZ < -90)
			this->RotatedZ = -90;	
		this->GetViewDir();	
	}
	else
	{
		if(this->ViewDir.z > 0)
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX -= Angle;
				
		if(this->ViewDir.z < 0)		
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX += Angle;

		if(this->RotatedX > 90)
			this->RotatedX = 90;
		else if(this->RotatedX < -90)
			this->RotatedX = -90;	
		this->GetViewDir();	
	}
}

void MMoviment::RotateY(GLfloat Angle)
{
	if(this->RotatedY <= 180 && this->RotatedY >= -180)
	{
		this->RotatedY += Angle;
		if(this->RotatedY > 180)
			this->RotatedY = -175;
		else if(this->RotatedY < -180)
			this->RotatedY = 175;	
		this->GetViewDir();	
	}
}

void MMoviment::RotateZ(GLfloat Angle)
{
	if(fabs(this->ViewDir.x) > fabs(this->ViewDir.z))
	{
		if(this->ViewDir.x > 0)
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX -= Angle;
				
		if(this->ViewDir.x < 0)		
			if(this->RotatedX <= 90 && this->RotatedX >= -90)
				this->RotatedX += Angle;

		if(this->RotatedX > 90)
			this->RotatedX = 90;
		else if(this->RotatedX < -90)
			this->RotatedX = -90;	
		this->GetViewDir();	
	}
	else
	{
		if(this->ViewDir.z > 0)
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ -= Angle;
				
		if(this->ViewDir.z < 0)		
			if(this->RotatedZ <= 90 && this->RotatedZ >= -90)
				this->RotatedZ += Angle;

		if(this->RotatedZ > 90)
			this->RotatedZ = 90;
		else if(this->RotatedZ < -90)
			this->RotatedZ = -90;	
		this->GetViewDir();	
	}
}

void MMoviment::RenderModel(void)
{
	glTranslatef(this->Position.x, this->Position.y,this->Position.z);

	glRotatef(this->RotatedZ, 0.0, 0.0, 1.0);
	glRotatef(this->RotatedX, 1.0, 0.0, 0.0);
	glRotatef(this->RotatedY, 0.0, 1.0, 0.0);
}


void MMoviment::UpdateSpeed(GLfloat _Speed)
{
	this->Speed += _Speed;
	if(this->Speed >= 0)
		this->Speed = 0;		
}

void MMoviment::MoveForwards()
{
	this->GetViewDir();
	this->Position.x += -this->ViewDir.x * this->Speed;
	this->Position.y += -this->ViewDir.y * this->Speed;
	this->Position.z += -this->ViewDir.z * this->Speed;
}


void MMoviment::MoveLeftRight(GLfloat Distance)
{
	this->GetViewDir();
	this->Position.z += this->ViewDir.x * + Distance;
	this->Position.y += 0.0;
	this->Position.x += -this->ViewDir.z * + Distance;
}

void MMoviment::MoveUpDown(GLfloat Distance)
{
	this->GetViewDir();
	this->Position.z += 0.0;
	this->Position.y += Distance;
	this->Position.x += 0.0;
}
