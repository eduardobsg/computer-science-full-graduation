#include "model.h"

/* Constructor of an Model. 
*/
Model::Model() 
{
	this->scale = 1.0;  
}


/* Destructor of the Model 
*/
Model::~Model()
{
	cout << "Model from " << this->ModelOBJ << " has been deleted." << endl;
}

/* Loads the model
*/
void Model::LoadModel()
{
	if(!(this->pmodel)) 
    {
        this->pmodel = glmReadOBJ(this->ModelOBJ);     
        if(!(this->pmodel)) 
			exit(0);
        glmUnitize(this->pmodel);
        glmFacetNormals(this->pmodel);        
        glmVertexNormals(this->pmodel, 90.0);
    }
    
}


/* Initializes the model
*/
void Model::InitModelFiles(char *_ModelOBJ, char *_ModelMAT)
{
	this->ModelOBJ = _ModelOBJ;
	this->ModelMAT = _ModelMAT;
	printf("Loading model %s.\n",_ModelOBJ);
	LoadModel();
	printf("Model %s loaded.\n",_ModelOBJ);
			
	this->initBoundingBoxes();
}


/* Initializes the model lighting properties
*/
void Model::InitModelLight(str_ambient _ambient = (str_ambient) {0.0, 0.0, 0.0, 1.0}, 
				str_diffuse _diffuse = (str_diffuse) {0.0, 0.0, 0.0, 1.0}, 
				str_specular _specular = (str_specular) {0.0, 0.0, 0.0, 1.0}, GLfloat _shininess = 100.0, 
				str_emission _emission = (str_emission) {0.0, 0.0, 0.0, 1.0})
{
	this->ambient = _ambient;
	this->diffuse = _diffuse;
	this->specular = _specular;
	this->shininess = _shininess;
	this->emission = _emission;
}

/* Draw the model specified in the Modelects structure
*/
void Model::DrawModel()
{	
	//printf("Drawing model %s.\n",this->ModelOBJ);
	this->moviment.RenderModel();
    
	//Material's reaction to lighting properties, only applied to material's front face
   	glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat[4]) { this->GetAmbientR(), 
   		this->GetAmbientB(), this->GetAmbientB(), this->GetAmbientw() } );
   	glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat[4]) { this->GetDiffuseR(), 
   		this->GetDiffuseB(), this->GetDiffuseB(), this->GetDiffusew() });
   	glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat[4]) { this->GetSpecularR(),
   		this->GetSpecularB(), this->GetSpecularB(), this->GetSpecularw() });
   	glMaterialfv(GL_FRONT, GL_SHININESS, (GLfloat[1]) { this->shininess });
   	glMaterialfv(GL_FRONT, GL_EMISSION, (GLfloat[4]) { this->GetEmissionR(), this->GetEmissionB(), 
   		this->GetEmissionB(), this->GetEmissionw() });
	
	//Draws the model
    glmDraw(this->pmodel, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);  
}

//------------------------------------------------------------------------------
// Function: void SetScale()
// Sets and scale the vertices of the model
//------------------------------------------------------------------------------
void Model::SetScale(GLfloat _scale)
{
	this->scale = _scale;
	glmScale(this->pmodel, this->scale);
}


//---------------------------------------------------------------
// Collision Detection
// Reference: http://www.3dcodingtutorial.com/Collision-Detection/Collision-Boxes.html
//---------------------------------------------------------------

//------------------------------------------------------------------------------
// Function: void initBoundingBoxes()
// Initializes the bounding box of each group (object) from the model (the project 
// model with all the objects - groups)
//------------------------------------------------------------------------------
void Model::initBoundingBoxes()
{
    GLMgroup *group;

	// A GLMmodel has a chained list of groups, each group representing an object. 
	// So, for each group (object), first we initialize the bounding box.
    group = this->pmodel->groups;    
   	
    //printf("Numgroups: %d\n", this->pmodel->numgroups);	
    //printf("%d, pathname: %s\n", i+1, this->pmodel->pathname);
	//printf("mtllibname: %s\n", this->pmodel->mtllibname);			
    
    int i = 0;
	while(group && i < this->pmodel->numgroups - 1)
	{	
		group->boundingBox.min.x = 100000;
		group->boundingBox.min.y = 100000;
		group->boundingBox.min.z = 100000;

		group->boundingBox.max.x = -100000;
		group->boundingBox.max.y = -100000;
		group->boundingBox.max.z = -100000;

		//printf("max.x: %f, max.y: %f, max.z: %f\n", group->boundingBox.max.x, group->boundingBox.max.y, group->boundingBox.max.z);
		//printf("min.x: %f, min.y: %f, min.z: %f\n", group->boundingBox.min.x, group->boundingBox.min.y, group->boundingBox.min.z);	
		
		group = group->next;	
		i++;
	}
	
	this->UpdateBoundingBoxes();
}


//------------------------------------------------------------------------------
// Function: void UpdateBoundingBoxes()
// Calculates the coordinates of the bounding boxes, based on the coordinates of 
// the triangles of each object in the model, and considering the Position of the 
// model.
//------------------------------------------------------------------------------
void Model::UpdateBoundingBoxes()
{
	GLMgroup *group;
    group = this->pmodel->groups; 
    Vector3D Position = this->GetPmodelPosition();
    int i = 0;
    
    while(group && i < this->pmodel->numgroups - 1)
    {
		//printf("\n%d\n", i+1);
		    
    	for(int i = 0; i < group->numtriangles; i++) 
		{ 
			// for each vertex of the triangle pmodel->triangles[group->triangles[i]]
			// calculate min and max
			for(int j = 0; j < 3; j++)
			{
				GLuint index = this->pmodel->triangles[group->triangles[i]].vindices[j];
				
				GLfloat x = this->pmodel->vertices[index*3 + 0];
				GLfloat y = this->pmodel->vertices[index*3 + 1];
				GLfloat z = this->pmodel->vertices[index*3 + 2];

				// Sets the actually position an scale of the triangles if this object
				// in the world coordinate system					
				x += Position.x;
				y += Position.y;				
				z += Position.z;				

				if(group->boundingBox.min.x > x)
					group->boundingBox.min.x = x;
				if(group->boundingBox.min.y > y)
					group->boundingBox.min.y = y;
				if(group->boundingBox.min.z > z)
					group->boundingBox.min.z = z;

				if(group->boundingBox.max.x < x)
					group->boundingBox.max.x = x;
				if(group->boundingBox.max.y < y)
					group->boundingBox.max.y = y;
				if(group->boundingBox.max.z < z)
					group->boundingBox.max.z = z;
				
				//printf("max.x: %f, max.y: %f, max.z: %f\n", group->boundingBox.max.x, group->boundingBox.max.y, group->boundingBox.max.z);
				//printf("min.x: %f, min.y: %f, min.z: %f\n", group->boundingBox.min.x, group->boundingBox.min.y, group->boundingBox.min.z);	
				//printf("x: %f, y: %f, z: %f\n", x, y, z); 
			} 
		}
		//printf("final -> max.x: %f, max.y: %f, max.z: %f\n", group->boundingBox.max.x, group->boundingBox.max.y, group->boundingBox.max.z);
		//printf("final -> min.x: %f, min.y: %f, min.z: %f\n", group->boundingBox.min.x, group->boundingBox.min.y, group->boundingBox.min.z);	
		
		group = group->next;	
 
		//printf("%d\n", i+1);
		//printf("numtriangles: %d\n", group->numtriangles);
		//printf("max.x: %f, max.y: %f, max.z: %f\n", group->boundingBox.max.x, group->boundingBox.max.y, group->boundingBox.max.z);
		//printf("min.x: %f, min.y: %f, min.z: %f\n", group->boundingBox.min.x, group->boundingBox.min.y, group->boundingBox.min.z);				
		//getchar();
					
		i++;	
   	}
	
	//getchar();
}


//------------------------------------------------------------------------------
// Function: bool CollisionDetection(BoundingBox boundingbox, Vector3D objectPosition)
// Given a objects bounding box, and its position in the space, this function tests 
// if this boundingbox collides with any other bounding box from the model. 
//
// Ex.: model[CITY].CollisionDetection(model[AIRPLANE].GetPmodelBoundingBox())
// In this case the bounding box of the airplane will be tested against the 
// bounding boxes of each object in the model CITY.
//
// IMPORTANT: before calling model[AIRPLANE].GetPmodelBoundingBox(), the bounding box
// of this object must the already updated with model[AIRPLANE].UpdateBoundingBoxes()
//
// Returns 
// * true: the bounding boxes have collided
// * false: no collision detection
//------------------------------------------------------------------------------
bool Model::CollisionDetection(BoundingBox boundingBox)
{	
	GLMgroup* group;	
	group = this->pmodel->groups; 
	
	this->UpdateBoundingBoxes(); // updates the bounding boxes of the objects of the model
	
	int i = 0;
	while(group && i < this->pmodel->numgroups - 1)
	{		
		//printf("City: BoundingBox %d\n", i+1);
		//printf("max.x: %f, max.y: %f, max.z: %f\n", group->boundingBox.max.x, group->boundingBox.max.y, group->boundingBox.max.z);
		//printf("min.x: %f, min.y: %f, min.z: %f\n", group->boundingBox.min.x, group->boundingBox.min.y, group->boundingBox.min.z);	
		
		// Tests if the min boundingBox coordinate is inside the other bounding box
		/*
		printf("test1: %d, %d, %d, %d, %d, %d\n", !(boundingBox.min.x <= group->boundingBox.max.x), !(boundingBox.min.x >= group->boundingBox.min.x),
		!(boundingBox.min.y <= group->boundingBox.max.y), !(boundingBox.min.y >= group->boundingBox.min.y),
		!(boundingBox.min.z <= group->boundingBox.max.z), !(boundingBox.min.z >= group->boundingBox.min.z));		*/
		if((boundingBox.min.x <= group->boundingBox.max.x) && 
		   (boundingBox.min.x >= group->boundingBox.min.x) && 
		   (boundingBox.min.y <= group->boundingBox.max.y) && 
		   (boundingBox.min.y >= group->boundingBox.min.y) &&
		   (boundingBox.min.z <= group->boundingBox.max.z) && 
		   (boundingBox.min.z >= group->boundingBox.min.z))			 
		{
			// if any condition turned out to be true, then we have a collision
			//printf("coll1\n");
			return true;
		}	
		
		// Tests if the max boundingBox coordinate is inside the other bounding box
		if((boundingBox.max.x <= group->boundingBox.max.x) && 
		   (boundingBox.max.x >= group->boundingBox.min.x) && 
		   (boundingBox.max.y <= group->boundingBox.max.y) && 
		   (boundingBox.max.y >= group->boundingBox.min.y) &&
		   (boundingBox.max.z <= group->boundingBox.max.z) && 
		   (boundingBox.max.z >= group->boundingBox.min.z))			 	 
		{
			// if any condition turned out to be true, then we have a collision.
			//printf("coll2\n");			
			return true;
		}		   
		
		// No collision detected for this object of the model, lets test another one.
		group = group->next;	
		i++;
	}
}
















