#ifndef __MODEL_H__
#define __MODEL_H__

#include <GL/glut.h>

#include <iostream>
#include <cstring> 
#include <cmath>
#include "moviment.h"
#include "glm.h"

#define PI 3.14159265

/*
Model movement:

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

class Model 
{
	//---------------------------------------------------------------
	//Variables
	//---------------------------------------------------------------	
	public:
		//Names
		char *ModelOBJ; //Name of .obj file. Ex.: box.obj
		char *ModelMAT; //Name of .mat file. Ex.: box.mat

		Texture modelTexture; //Holds all the texture information about the model
		GLuint texture; 
		GLMmodel *pmodel; //Pointer to where the obj structure will be loaded
	
		//For transformations
		GLfloat scale;

		//For lighting
		struct str_ambient{
			GLfloat R;
			GLfloat G;
			GLfloat B;
			GLfloat w;
		} ambient;
		struct str_diffuse{
			GLfloat R;
			GLfloat G;
			GLfloat B;
			GLfloat w;
		} diffuse;
		struct str_specular{
			GLfloat R;
			GLfloat G;
			GLfloat B;
			GLfloat w;
		} specular;
		
		GLfloat shininess;
		
		struct str_emission{
			GLfloat R;
			GLfloat G;
			GLfloat B;
			GLfloat w;
		} emission;
	
	//---------------------------------------------------------------
	//Methods
	//---------------------------------------------------------------
	public: 
		MMoviment moviment;
	
		//Constructors
		Model();
		
		//Destructor
		~Model();
		
		//Setters			
		void SetScale(GLfloat);
		
		//Getters		
		GLfloat GetScale(void){ return this->scale; }
		char *GetModelOBJ(void){ return this->ModelOBJ; }                      
		char *GetModelMAT(void){ return this->ModelMAT; } 	
		GLfloat GetAmbientR(void){ return this->ambient.R; }
		GLfloat GetAmbientG(void){ return this->ambient.G; }
		GLfloat GetAmbientB(void){ return this->ambient.B; }            
		GLfloat GetAmbientw(void){ return this->ambient.w; }    
		GLfloat GetDiffuseR(void){ return this->diffuse.R; }
		GLfloat GetDiffuseG(void){ return this->diffuse.G; }
		GLfloat GetDiffuseB(void){ return this->diffuse.B; }            
		GLfloat GetDiffusew(void){ return this->diffuse.w; }    
		GLfloat GetSpecularR(void){ return this->specular.R; }
		GLfloat GetSpecularG(void){ return this->specular.G; }
		GLfloat GetSpecularB(void){ return this->specular.B; }          
		GLfloat GetSpecularw(void){ return this->specular.w; }  
		GLfloat GetEmissionR(void){ return this->emission.R; }
		GLfloat GetEmissionG(void){ return this->emission.G; }
		GLfloat GetEmissionB(void){ return this->emission.B; }          
		GLfloat GetEmissionw(void){ return this->emission.w; }        		
		GLMmodel *GetPmodel(void){ return this->pmodel; }
		GLMgroup *GetPmodelGroups(void){ return this->pmodel->groups; }
		GLMmaterial *GetPmodelMaterials(void){ return this->pmodel->materials; }
	    GLuint GetNumMaterials(void){ return this->pmodel->nummaterials; }
   		BoundingBox GetPmodelBoundingBox(void){ return this->pmodel->groups->boundingBox; }		
		Vector3D GetPmodelPosition(void){ return this->moviment.GetPosition(); }
		
		//Loader for model's structure (.obj file)
		void LoadModel();
		
		//Initializes the model
		void InitModelFiles(char *, char *);
		
		//Initialization needed for lighting
		void InitModelLight(str_ambient, str_diffuse, str_specular, GLfloat, str_emission);
						 
		//Draw the model specified in the objects structure
		void DrawModel();
		
		//CollisionDetection
		void initBoundingBoxes(); 
		void UpdateBoundingBoxes();	
		bool CollisionDetection(BoundingBox);

};

#endif

