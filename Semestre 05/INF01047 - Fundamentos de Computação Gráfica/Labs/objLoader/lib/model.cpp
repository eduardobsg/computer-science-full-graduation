#include "model.h"

/* Constructor of an Model. 
*/
Model::Model() 
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->transx = 0.0; 
	this->transy = 0.0; 
	this->transz = 0.0;
	this->rotx = 0.0; 
	this->roty = 0.0; 
	this->rotz = 0.0;
	this->scalex = 1.0; 
	this->scaley = 1.0; 
	this->scalez = 1.0;
}


/* Destructor of the Model 
*/
Model::~Model()
{
	cout << "Model from " << this->ModelOBJ << " has been deleted." << endl;
}


/* Loads the texture of a model
*/
void Model::LoadTexture()
{	
	cout << "Loading " << this->ModelTGA << " -> ";
	if( LoadTGA(&(this->modelTexture), this->ModelTGA) )	
	{		
		glGenTextures(1, &(this->modelTexture.texID));
		glBindTexture(GL_TEXTURE_2D, this->modelTexture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, this->modelTexture.bpp / 8, this->modelTexture.width, this->modelTexture.height, 0, this->modelTexture.type, GL_UNSIGNED_BYTE, this->modelTexture.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
		if(this->modelTexture.imageData)		
		{
			free(this->modelTexture.imageData);				
		}
		cout << "Done." << endl;	
	}												
}


/* Loads the model
*/
void Model::LoadModel()
{
	cout << "Loading " << this->ModelOBJ << " -> ";
	if(!(this->pmodel)) 
    {
        this->pmodel = glmReadOBJ(this->ModelOBJ);     
        if(!(this->pmodel)) 
			exit(0);
        glmUnitize(this->pmodel);
        glmFacetNormals(this->pmodel);        
        glmVertexNormals(this->pmodel, 90.0);
    }
    cout << "Done.\n" << endl;	
}


/* Initializes the model
*/
void Model::InitModelFiles(char *_ModelOBJ, char *_ModelTGA, char *_ModelMAT)
{
	this->ModelOBJ = _ModelOBJ;
	this->ModelTGA = _ModelTGA;
	this->ModelMAT = _ModelMAT;
		
	cout << "ModelOBJ: " << this->ModelOBJ << endl; 
	cout << "ModelTGA: " << this->ModelTGA << endl;
	cout << "ModelMAT: " << this->ModelMAT << endl;
	
	LoadTexture();
	LoadModel();
}


/* Setups the Modelect attributes
*/
void Model::SetModel(GLfloat _transx, GLfloat _transy, GLfloat _transz, 
				     GLfloat _rotx, GLfloat _roty, GLfloat _rotz, 
				 	 GLfloat _scalex, GLfloat _scaley, GLfloat _scalez)
{
	this->transx = _transx;
	this->transy = _transy;
	this->transz = _transz;

	this->rotx = _rotx;
	this->roty = _roty;
	this->rotz = _rotz;

	this->scalex = _scalex;
	this->scaley = _scaley;
	this->scalez = _scalez;
}


/* Draw the model specified in the Modelects structure
*/
void Model::DrawModel()
{	
	cout << "Drawing Model " << this->ModelOBJ << " ->";
	//Sets the position of the Modelect in the world 
	glTranslatef(this->transx, this->transy, this->transz);
	
	//Do translation around the origin
	glRotatef(this->rotx, 1.0, 0.0, 0.0);						
	glRotatef(this->roty, 0.0, 1.0, 0.0);					
	glRotatef(this->rotz, 0.0, 0.0, 1.0);
	
	//Scale the Modelect according to the size passed as a parameter
    glScalef(this->scalex, this->scaley, this->scalez);
    
	//Binds the texture name (this->ModelTexture.texID) to the target (GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, this->modelTexture.texID);
	
	//Draws the model
    glmDraw(this->pmodel, GLM_SMOOTH | GLM_TEXTURE);  
    
    cout << "Done.\n" << endl;
}





















