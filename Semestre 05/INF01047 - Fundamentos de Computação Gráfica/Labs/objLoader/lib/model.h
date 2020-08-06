#ifndef __MODEL_H__
#define __MODEL_H__

#include <GL/glut.h>

#include <iostream>
#include <cstring>
#include "texture.h"
#include "glm.h"

enum ModelsIndex {BOX = 0, GROUND = 1};

using namespace std;

class Model 
{
	//---------------------------------------------------------------
	//Variables
	//---------------------------------------------------------------	
	protected:
		//Names
		char *ModelOBJ; //Name of .obj file. Ex.: box.obj
		char *ModelTGA; //Name of .tga file. Ex.: box.tga
		char *ModelMAT; //Name of .mat file. Ex.: box.mat

		Texture modelTexture; //Holds all the texture information about the model
		GLuint texture; 
		GLMmodel *pmodel; //Pointer to where the obj structure will be loaded
		
		//Object position in the space
		GLfloat x;
		GLfloat y;
		GLfloat z;
	
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

		//For box determination
		GLint maxx;
		GLint minx;
		GLint maxy;
		GLint miny;
		GLint maxz;
		GLint minz;
	
	//---------------------------------------------------------------
	//Methods
	//---------------------------------------------------------------
	public: 
		//Constructors
		Model();
		
		//Destructor
		~Model();
		
		//Setters
		void SetWorldX(GLfloat _x){ this->x = _x; }
		void SetWorldY(GLfloat _y){ this->y = _y; }
		void SetWorldZ(GLfloat _z){ this->z = _z; }					
		void SetTranslateX(GLfloat _transx){ this->transx = _transx; }
		void SetTranslateY(GLfloat _transy){ this->transy = _transy; }
		void SetTranslateZ(GLfloat _transz){ this->transz = _transz; }			
		void SetRotateX(GLfloat _rotx){ this->rotx = _rotx; }
		void SetRotateY(GLfloat _roty){ this->roty = _roty; }
		void SetRotateZ(GLfloat _rotz){ this->rotz = _rotz; }				
		void SetScaleX(GLfloat _scalex){ this->scalex = _scalex; }
		void SetScaleY(GLfloat _scaley){ this->scaley = _scaley; }
		void SetScaleZ(GLfloat _scalez){ this->scalez = _scalez; }			
		void SetModelOBJ(char *_ModelOBJ){ memcpy(this->ModelOBJ, _ModelOBJ, strlen(_ModelOBJ)+1); }
		void SetModelTGA(char *_ModelTGA){ memcpy(this->ModelTGA, _ModelTGA, strlen(_ModelTGA)+1); }
		void SetModelMAT(char *_ModelMAT){ memcpy(this->ModelMAT, _ModelMAT, strlen(_ModelMAT)+1); }		
		
		//Getters	
		GLfloat GetWorldX(void){ return this->x; }
		GLfloat GetWorldY(void){ return this->y; }
		GLfloat GetWorldZ(void){ return this->z; }					
		GLfloat GetTranslateX(void){ return this->transx; }
		GLfloat GetTranslateY(void){ return this->transy; }
		GLfloat GetTranslateZ(void){ return this->transz; }				
		GLfloat GetRotateX(void){ return this->rotx; }
		GLfloat GetRotateY(void){ return this->roty; }
		GLfloat GetRotateZ(void){ return this->rotz; }				
		GLfloat GetScaleX(void){ return this->scalex; }
		GLfloat GetScaleY(void){ return this->scaley; }
		GLfloat GetScaleZ(void){ return this->scalez; }		
		char * GetModelOBJ(void){ return this->ModelOBJ; }	
		char * GetModelTGA(void){ return this->ModelTGA; }			
		char * GetModelMAT(void){ return this->ModelMAT; }			

		//Loader for model's texture
		void LoadTexture();
		
		//Loader for model's structure (.obj file)
		void LoadModel();
		
		//Initializes the model
		void InitModelFiles(char *, char *, char *);
		
		//Setup the model attributes
		void SetModel(GLfloat, GLfloat, GLfloat, 
				   	  GLfloat, GLfloat, GLfloat,
					  GLfloat, GLfloat, GLfloat);
						 
		//Draw the model specified in the objects structure
		void DrawModel();
		
		//With the model loaded this function calculates the box around our model
		//void DetermineBox();

};

#endif

