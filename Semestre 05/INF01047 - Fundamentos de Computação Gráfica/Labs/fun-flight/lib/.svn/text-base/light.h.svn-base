#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <GL/glut.h>

#include <iostream>

//enum LightsIndex {SUN = 0};

using namespace std;

class Light  
{
	//---------------------------------------------------------------
	//Variables
	//---------------------------------------------------------------	
	protected:
		//Name
		char* name;
	
		//Parameters
		struct str_ambient{
			GLfloat R;
			GLfloat G;
			GLfloat B;
			GLfloat w;
		}ambient;
		struct str_diffuse{//color
			GLfloat R;
			GLfloat G;
			GLfloat B;
			GLfloat w;
		}diffuse;
		struct str_specular{//brightness
			GLfloat R;
			GLfloat G;
			GLfloat B;
			GLfloat w;

		}specular;
		struct str_position{
			GLfloat	x;		
			GLfloat y;
			GLfloat z;
			GLfloat w;			
		}position;

		//For transformations
		GLfloat transx;
		GLfloat transy;
		GLfloat transz;
		GLfloat rotx;
		GLfloat roty;
		GLfloat rotz;
		GLfloat scalex;
		GLfloat scaley;
		GLfloat scalez;

	
	//---------------------------------------------------------------
	//Methods
	//---------------------------------------------------------------
	public: 
		//Constructors
		Light();
		
		//Destructor
		~Light();
		
		//Setters
		//void SetAmbient(str_ambient _ambient){ this->ambient = _ambient; }
		//void SetDiffuse(str_diffuse _diffuse){ this->diffuse = _diffuse; }
		//void SetSpecular(str_specular _specular){ this->specular = _specular; }					
		//void SetPosition(str_position _position){ this->position = _position; }	
		void SetTranslateX(GLfloat _transx){ this->transx = _transx; }
		void SetTranslateY(GLfloat _transy){ this->transy = _transy; }
		void SetTranslateZ(GLfloat _transz){ this->transz = _transz; }			
		void SetRotateX(GLfloat _rotx){ this->rotx = _rotx; }
		void SetRotateY(GLfloat _roty){ this->roty = _roty; }
		void SetRotateZ(GLfloat _rotz){ this->rotz = _rotz; }				
		void SetScaleX(GLfloat _scalex){ this->scalex = _scalex; }
		void SetScaleY(GLfloat _scaley){ this->scaley = _scaley; }
		void SetScaleZ(GLfloat _scalez){ this->scalez = _scalez; }		
		
		//Getters	
		str_ambient GetAmbient(void){ return this->ambient; }
		GLfloat GetAmbientR(void){ return this->ambient.R; }
		GLfloat GetAmbientG(void){ return this->ambient.G; }
		GLfloat GetAmbientB(void){ return this->ambient.B; }
		GLfloat GetAmbientw(void){ return this->ambient.w; }
		str_diffuse GetDiffuse(void){ return this->diffuse; }
		GLfloat GetDiffuseR(void){ return this->diffuse.R; }
		GLfloat GetDiffuseG(void){ return this->diffuse.G; }
		GLfloat GetDiffuseB(void){ return this->diffuse.B; }
		GLfloat GetDiffusew(void){ return this->diffuse.w; }
		str_specular GetSpecular(void){ return this->specular; }
		GLfloat GetSpecularR(void){ return this->specular.R; }
		GLfloat GetSpecularG(void){ return this->specular.G; }
		GLfloat GetSpecularB(void){ return this->specular.B; }
		GLfloat GetSpecularw(void){ return this->specular.w; }					
		str_position GetPosition(void){ return this->position; }
		GLfloat GetPositionx(void){ return this->position.x; }
		GLfloat GetPositiony(void){ return this->position.y; }
		GLfloat GetPositionz(void){ return this->position.z; }
		GLfloat GetPositionw(void){ return this->position.w; }	
		GLfloat GetTranslateX(void){ return this->transx; }
		GLfloat GetTranslateY(void){ return this->transy; }
		GLfloat GetTranslateZ(void){ return this->transz; }				
		GLfloat GetRotateX(void){ return this->rotx; }
		GLfloat GetRotateY(void){ return this->roty; }
		GLfloat GetRotateZ(void){ return this->rotz; }				
		GLfloat GetScaleX(void){ return this->scalex; }
		GLfloat GetScaleY(void){ return this->scaley; }
		GLfloat GetScaleZ(void){ return this->scalez; }			

		
		//Initializes the light
		void InitLight(char* _name,
                      str_ambient _ambient, 
		      str_diffuse _diffuse, 
		      str_specular specular, 
		      str_position position);
		
		//Setup the light's attributes
		void SetLight(GLfloat _transx, GLfloat _transy, GLfloat _transz, 
				     GLfloat _rotx, GLfloat _roty, GLfloat _rotz);
						 
		//Draw the model specified in the objects structure
		void PlaceLight();
		
	    //Sets lighting parameters
		void lighting();
};

#endif

