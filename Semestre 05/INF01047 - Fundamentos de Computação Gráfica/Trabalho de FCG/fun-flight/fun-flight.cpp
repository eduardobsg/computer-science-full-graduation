//Help: http://www.3dcodingtutorial.com/Working-with-3D-models/Importing-the-model-in-C++.html

#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>

#include "lib/model.h"
#include "lib/camera.h"
#include "lib/light.h"
#include "lib/EasyBMP.h"

//Lights
#define NUMBER_LIGHTS 1
Light SUN;

//Models
#define GROUND_SQUARE_SIZE 4
#define GROUND_SIZE (10 * GROUND_SQUARE_SIZE)
#define NUMBER_MODELS 3
#define GROUND 		0
#define SKY 		1
#define AIRPLANE	2
BoundingBox boundingBox[NUMBER_MODELS]; 
#define NUMBER_TGA_MODELS 4
#define CITY1 		0
#define CITY2		1
#define AIRPLANE1 	2
#define AIRPORT 	3
Model model[NUMBER_TGA_MODELS];
int aircraft = AIRPLANE1; //the aircraft we are using

//Cameras
#define NUMBER_CAMERAS 2
Camera camera[NUMBER_CAMERAS]; //camera[0]: perspective, camera[1]: orthographic

//Textures
#define NUMBER_BMP_TEXTURES 2
#define SKY_TEXTURE 0
#define GROUND_TEXTURE 1
GLuint textureName[NUMBER_BMP_TEXTURES];
#define SKY_TEXTURE_SIZE 256
#define GROUND_TEXTURE_SIZE 256
GLubyte SkyTexture[SKY_TEXTURE_SIZE][SKY_TEXTURE_SIZE][3];
GLubyte GroundTexture[GROUND_TEXTURE_SIZE][GROUND_TEXTURE_SIZE][3];

//Viewmodes
#define VIEWMODE1 1
#define VIEWMODE2 2
#define VIEWMODE3 3
#define VIEWMODE4 4
int viewmode = VIEWMODE2;


//------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------

/*
void DrawTopViewSquare()
{
	GLsizei width = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei height = glutGet(GLUT_WINDOW_HEIGHT);
	glLineWidth(1.0f);
	glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.75*width, 0, 0.75*height);
        glVertex3f(0.25*width, 0, 0.75*height);
        glVertex3f(0.25*width, 0, 0.25*height);
        glVertex3f(0.25*width, 0, 0.75*height);
    glEnd();	   	
}
*/

void DrawSky(void)
{
    glBindTexture(GL_TEXTURE_2D, textureName[SKY_TEXTURE]);

	GLUquadricObj *sphere = gluNewQuadric();
	
 	gluQuadricTexture(sphere, GL_TRUE);
 	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricOrientation(sphere, GLU_INSIDE);
	gluQuadricDrawStyle(sphere, GLU_FILL);
 
	glTranslatef(GROUND_SIZE/2, 0.0, GROUND_SIZE/2);
 	gluSphere(sphere, sqrt(2)*GROUND_SIZE/2, 100, 100); //Draws the sphere based on the ground size
    gluDeleteQuadric(sphere);
}

//------------------------------------------------------------------------------
// Function: void initLights(void) 
// Initialization function - called from init(). Initializes the lights
//------------------------------------------------------------------------------
void initLights(void)
{
	//Enables lighting
	glEnable(GL_LIGHTING);

	//SUN light will be light0
	SUN.InitLight("SUN",
		      {0.0,0.0,0.0,1.0},
		      {1.0,1.0,1.0,1.0},
		      {1.0,1.0,1.0,1.0},
		      {GROUND_SIZE/2,0.0,GROUND_SIZE/2,0.0});
	SUN.SetLight(0.0,0.0,0.0,0.0,0.0,0.0);

	//Defining light0 (sun) parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT, (GLfloat[4]) {SUN.GetAmbientR(), 
			  SUN.GetAmbientG(), SUN.GetAmbientB(), SUN.GetAmbientw()} ); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, (GLfloat[4]) {SUN.GetDiffuseR(), 
			  SUN.GetDiffuseG(), SUN.GetDiffuseB(), SUN.GetDiffusew()} );
	glLightfv(GL_LIGHT0, GL_SPECULAR, (GLfloat[4]) {SUN.GetSpecularR(), 
			  SUN.GetSpecularG(), SUN.GetSpecularB(), SUN.GetSpecularw()} );
	glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat[4]) {SUN.GetPositionx(), 
			  SUN.GetPositiony(), SUN.GetPositionz(), SUN.GetPositionw()} );

	//Sets ambient light for all lights
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat[4]) { 0.5, 0.5, 0.5, 1.0 } );

	//Sets viewpoint as infinite, simplifying calculations
   	//glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE );
	//Enables sun light
	glEnable(GL_LIGHT0); 
}

//------------------------------------------------------------------------------
// Function: void initModels(void) 
// Initialization function - called from init(). Initializes the Models
//------------------------------------------------------------------------------
void initModels(void)
{
	//Airplane1 - boeing
	//y = 0.4 -> airplane at ground
	model[AIRPLANE1].moviment.SetPosition(9.5, 0.2, 36.0);
	model[AIRPLANE1].moviment.SetViewDir(-0.190809, 0.0, -0.981627);
	model[AIRPLANE1].moviment.SetRotatedY(-171.0);
	model[AIRPLANE1].InitModelFiles("obj/airplane1.obj", "obj/airplane1.mat");	
	model[AIRPLANE1].InitModelLight({ 0.7, 0.7, 0.7, 1.0 },{ 1.0, 1.0, 1.8, 1.0 },
									{ 1.0, 1.0, 1.0, 1.0 },{ 100.0 }, {0.0, 0.0, 0.0, 0.0});
	model[AIRPLANE1].SetScale(0.3); 										
	
	//City1
	model[CITY1].moviment.SetPosition(GROUND_SIZE/2, 1.5, GROUND_SIZE/2 - GROUND_SIZE/4);
	model[CITY1].moviment.SetViewDir(0.0, 0.0, 1.0);	
	model[CITY1].InitModelFiles("obj/city3.obj", "obj/city3.mat"); 	
	model[CITY1].InitModelLight({ 0.7, 0.7, 0.7, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 100.0 },{0.0, 0.0, 0.0, 0.0});
	model[CITY1].SetScale(9.0); 
	
	//City2
	model[CITY2].moviment.SetPosition(GROUND_SIZE/2, 1.5, GROUND_SIZE/2 + GROUND_SIZE/4);
	model[CITY2].moviment.SetViewDir(0.0, 0.0, 1.0);	
	model[CITY2].InitModelFiles("obj/city3.obj", "obj/city3.mat"); 	
	model[CITY2].InitModelLight({ 0.7, 0.7, 0.7, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 100.0 },{0.0, 0.0, 0.0, 0.0});
	model[CITY2].SetScale(9.0); 
	
	//Airport
	model[AIRPORT].moviment.SetPosition(5.5, 1.5, 30.0);
	model[AIRPORT].moviment.SetViewDir(0.0, 0.0, 1.0);	
	model[AIRPORT].InitModelFiles("obj/airport2.obj", "obj/airport2.mat"); 	
	model[AIRPORT].InitModelLight({ 0.7, 0.7, 0.7, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 1.0, 1.0, 1.0, 1.0 },{ 100.0 },{0.0, 0.0, 0.0, 0.0});
	model[AIRPORT].SetScale(7.0);
	model[AIRPORT].moviment.SetRotatedY(-30.0);
	
}

//------------------------------------------------------------------------------
// Function: void initCameras(void) 
// Initialization function - called from init(). Initializes the cameras
//------------------------------------------------------------------------------
void initCameras(void)
{
	//Perpective
	camera[PERSPECTIVE].SetCameraView(true);
	camera[PERSPECTIVE].moviment.SetPosition(10.0, 0.5, 39.0);
	camera[PERSPECTIVE].moviment.SetViewDir(0.139173, 0.0, 0.990268);
	camera[PERSPECTIVE].moviment.SetRotatedY(8.0);

	//Orthographic
	camera[ORTHOGRAPHIC].SetCameraView(false);
}

//------------------------------------------------------------------------------
// Function: void LoadBMPTextures(void) 
// Called from initTextures(). Loads singleg textures
//------------------------------------------------------------------------------
void LoadBMPTextures(void)
{
    BMP LoadedTexture;

    //Sky Texture
    LoadedTexture.ReadFromFile("texture/sky.bmp");
    for(int i = 0; i < SKY_TEXTURE_SIZE; i++)
    {
		for(int j = 0; j < SKY_TEXTURE_SIZE; j++)
		{
            SkyTexture[i][j][0] = (GLubyte) LoadedTexture(i,j)->Red;
            SkyTexture[i][j][1] = (GLubyte) LoadedTexture(i,j)->Green;
            SkyTexture[i][j][2] = (GLubyte) LoadedTexture(i,j)->Blue;
        }
    }
    
    //Ground Texture
    LoadedTexture.ReadFromFile("texture/ground_grass1.bmp");
    for(int i = 0; i < GROUND_TEXTURE_SIZE; i++)
    {
		for(int j = 0; j < GROUND_TEXTURE_SIZE; j++)
		{
            GroundTexture[i][j][0] = (GLubyte) LoadedTexture(i,j)->Red;
            GroundTexture[i][j][1] = (GLubyte) LoadedTexture(i,j)->Green;
            GroundTexture[i][j][2] = (GLubyte) LoadedTexture(i,j)->Blue;
        }
    }
}

//------------------------------------------------------------------------------
// Function: void initBMPTextures(void) 
// Initialization function - called from init(). Initializes the textures
//------------------------------------------------------------------------------
void initBMPTextures()
{
	LoadBMPTextures();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(NUMBER_BMP_TEXTURES, textureName);

	//Sky texture
    glBindTexture(GL_TEXTURE_2D, textureName[SKY_TEXTURE]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, SKY_TEXTURE_SIZE, SKY_TEXTURE_SIZE, 
    			 0, GL_RGB, GL_UNSIGNED_BYTE, &SkyTexture[0][0][0]);    			 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//Ground texture
    glBindTexture(GL_TEXTURE_2D, textureName[GROUND_TEXTURE]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, GROUND_TEXTURE_SIZE, GROUND_TEXTURE_SIZE, 
    			 0, GL_RGB, GL_UNSIGNED_BYTE, &GroundTexture[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glEnable(GL_TEXTURE_2D);
}

//------------------------------------------------------------------------------
// Function: void initTGATextures() 
// Texture loading function for all the TGA images of a model
//------------------------------------------------------------------------------
void initTGATextures()
{	
	static GLMgroup* group;
	static GLMmaterial* materials;
	static GLMmaterial* material;
	GLMmodel *eachModel;
	int totalTextures=0;
	
	printf("Loading TGA textures.\n");    
    
    for(int i = 0; i < NUMBER_TGA_MODELS-1; i++)
    {	
		group = model[i].GetPmodelGroups();
		materials = model[i].GetPmodelMaterials();
		for(int j=0; j < model[i].GetNumMaterials(); j++) 
		{
			material = &(materials[j]); 
			if( material->imageName != NULL &&
				LoadTGA( &(material->modelTexture), material->imageName) )	
			{			
				printf("\t\tOpening image %s. It's the %dth image.\n", material->imageName, totalTextures);
				totalTextures++;
			}	
		}		
    }
    
	printf("\tGenerating %d textures.\n",totalTextures);
	GLuint* texs[totalTextures];
	GLuint generatedTexs[totalTextures];
	
	int k=0;
    for(int i = 0; i < NUMBER_TGA_MODELS-1; i++)
    {	
		group = model[i].GetPmodelGroups();
		materials = model[i].GetPmodelMaterials();
		for(int j = 0; j < model[i].GetNumMaterials(); j++) 
		{
			material = &(materials[j]); 
			if( material->imageName != NULL &&
				LoadTGA( &(material->modelTexture), material->imageName) )	
			{			
				texs[k] = &(material->modelTexture.texID);
				k++;
			}	
		}		
    }
	glGenTextures(totalTextures, &generatedTexs[0]);
	for(int k=0; k<totalTextures; k++)
		*(texs[k]) = generatedTexs[k];  
	
	//FILE *report;
	//report = fopen("first.txt","w");
	int j = 0;
	for(int i = 0; i<NUMBER_TGA_MODELS-1; i++)
    {	
		group = model[i].GetPmodelGroups();
		materials = model[i].GetPmodelMaterials();
		while (group) 
		{
			material = &(materials[group->material]); 
			if( material->imageName != NULL && 
			    LoadTGAPossible(&(material->modelTexture), material->imageName))
			{			
				//fprintf(report,"\tname=%s,",materials[group->material].imageName);
				//fprintf(report,"info=%d,end=%d\n",materials[group->material].modelTexture.texID,&(materials[group->material].modelTexture.texID));
				j++;
			}	
			group = group->next;
		}		
    }	
	//fclose(report);

	printf("\tBuilding %d textures.\n",totalTextures);

	for(int i = 0; i<NUMBER_TGA_MODELS-1; i++)
    {	
		group = model[i].GetPmodelGroups();
		materials = model[i].GetPmodelMaterials();
		for(int j=0; j<model[i].GetNumMaterials(); j++) 
		{
			material = &(materials[j]); 
			if( material->imageName != NULL &&
				LoadTGA(&(material->modelTexture), material->imageName) )	
			{			
		
				printf("\t\tBuilding texture from image %s.\n",material->imageName);
				glBindTexture(GL_TEXTURE_2D, material->modelTexture.texID);
				glTexImage2D(GL_TEXTURE_2D, 0, material->modelTexture.bpp / 8, material->modelTexture.width, material->modelTexture.height, 0, material->modelTexture.type, GL_UNSIGNED_BYTE, material->modelTexture.imageData);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				if(material->modelTexture.imageData)		
				{
					free(material->modelTexture.imageData);				
				}
			}	
		}		
    }
	glEnable(GL_TEXTURE_2D);	
	printf("Textures loaded.\n");
}

//------------------------------------------------------------------------------
// Function: void initBMPModelsBoundingBoxes()
// Creates the bounding boxes for the BMP models, sky and ground (for now).
//------------------------------------------------------------------------------
void initBMPModelsBoundingBoxes()
{
	//Sky 
	boundingBox[SKY].max.x = GROUND_SIZE/2 + sqrt(2)*GROUND_SIZE/2;
	boundingBox[SKY].max.y = sqrt(2)*GROUND_SIZE/2;
	boundingBox[SKY].max.z = GROUND_SIZE/2 + sqrt(2)*GROUND_SIZE/2;		
	boundingBox[SKY].min.x = GROUND_SIZE/2 - sqrt(2)*GROUND_SIZE/2;
	boundingBox[SKY].min.y = -sqrt(2)*GROUND_SIZE/2;
	boundingBox[SKY].min.z = GROUND_SIZE/2 - sqrt(2)*GROUND_SIZE/2;	
	
	//Ground
	boundingBox[GROUND].max.x = GROUND_SIZE;
	boundingBox[GROUND].max.y = 0;
	boundingBox[GROUND].max.z = GROUND_SIZE;		
	boundingBox[GROUND].min.x = 0;
	boundingBox[GROUND].min.y = 0;
	boundingBox[GROUND].min.z = 0;
	
	//Airplane
	GLMmodel *pmodel;
	GLMgroup *group;
	pmodel = model[aircraft].GetPmodel(); 
    group = model[aircraft].GetPmodelGroups();    
    int i = 0;
    
    boundingBox[AIRPLANE].max.x = -100000;
	boundingBox[AIRPLANE].max.y = -100000;
	boundingBox[AIRPLANE].max.z = -100000;		
	boundingBox[AIRPLANE].min.x = 100000;
	boundingBox[AIRPLANE].min.y = 100000;
	boundingBox[AIRPLANE].min.z = 100000;
    
    while(group && i < pmodel->numgroups - 1)
    {		    
    	for(int i = 0; i < group->numtriangles; i++) 
			for(int j = 0; j < 3; j++)
			{
				GLuint index = pmodel->triangles[group->triangles[i]].vindices[j];
				
				GLfloat x = pmodel->vertices[index*3 + 0];
				GLfloat y = pmodel->vertices[index*3 + 1];
				GLfloat z = pmodel->vertices[index*3 + 2];		

				if(boundingBox[AIRPLANE].min.x > x)
					boundingBox[AIRPLANE].min.x = x;
				if(boundingBox[AIRPLANE].min.y > y)
					boundingBox[AIRPLANE].min.y = y;
				if(boundingBox[AIRPLANE].min.z > z)
					boundingBox[AIRPLANE].min.z = z;

				if(boundingBox[AIRPLANE].max.x < x)
					boundingBox[AIRPLANE].max.x = x;
				if(boundingBox[AIRPLANE].max.y < y)
					boundingBox[AIRPLANE].max.y = y;
				if(boundingBox[AIRPLANE].max.z < z)
					boundingBox[AIRPLANE].max.z = z;
			} 
		group = group->next;					
		i++;	
 	}
 	//printf("max.x: %f, max.y: %f, max.z: %f\n", boundingBox[AIRPLANE].max.x, boundingBox[AIRPLANE].max.y, boundingBox[AIRPLANE].max.z);
	//printf("min.x: %f, min.y: %f, min.z: %f\n", boundingBox[AIRPLANE].min.x, boundingBox[AIRPLANE].min.y, boundingBox[AIRPLANE].min.z);	
	//getchar();
}

//------------------------------------------------------------------------------
// Function: bool TestCollisions()
// Look up for collisions betwwen the airplane and the scenario
// Returns:
// * true -> collision detected
// * false -> no collision detected
//------------------------------------------------------------------------------
bool TestCollisions()
{
	//printf("Airplane: BoundingBox %d\n", i+1);
	
	// For collision detection
	BoundingBox boundingBox1;
	Vector3D Position = model[aircraft].GetPmodelPosition();
	
	boundingBox1.max.x = boundingBox[AIRPLANE].max.x + Position.x;
	boundingBox1.max.y = boundingBox[AIRPLANE].max.y + Position.y;
	boundingBox1.max.z = boundingBox[AIRPLANE].max.z + Position.z;
	boundingBox1.min.x = boundingBox[AIRPLANE].min.x + Position.x;
	boundingBox1.min.y = boundingBox[AIRPLANE].min.y + Position.y;
	boundingBox1.min.z = boundingBox[AIRPLANE].min.z + Position.z;

	//printf("max.x: %f, max.y: %f, max.z: %f\n", boundingBox1.max.x, boundingBox1.max.y, boundingBox1.max.z);
	//printf("min.x: %f, min.y: %f, min.z: %f\n", boundingBox1.min.x, boundingBox1.min.y, boundingBox1.min.z);	
	//getchar();

	//Tests collision with the ground
	if((boundingBox1.min.x <= boundingBox[GROUND].max.x) && 
	   (boundingBox1.min.x >= boundingBox[GROUND].min.x) &&
	   (boundingBox1.min.y <= boundingBox[GROUND].max.y) && 
	   (boundingBox1.min.y <= boundingBox[GROUND].min.y) &&
	   (boundingBox1.min.z <= boundingBox[GROUND].max.z) && 
	   (boundingBox1.min.z >= boundingBox[GROUND].min.z))			 
	{
		printf("Collision with ground1\n");
		return true;
	}
	if((boundingBox1.max.x <= boundingBox[GROUND].max.x) && 
	   (boundingBox1.max.x >= boundingBox[GROUND].min.x) &&
	   (boundingBox1.max.y <= boundingBox[GROUND].max.y) && 
	   (boundingBox1.max.y <= boundingBox[GROUND].min.y) &&
	   (boundingBox1.max.z <= boundingBox[GROUND].max.z) && 
	   (boundingBox1.max.z >= boundingBox[GROUND].min.z))			 
	{
		printf("Collision with ground2\n");		
		return true;
	}
	//printf("No collision with ground\n");		

	//Tests if the airplane is outside the sphere		
	if((boundingBox1.max.x >= boundingBox[SKY].max.x) ||
	   (boundingBox1.max.x <= boundingBox[SKY].min.x) ||
	   (boundingBox1.max.y >= boundingBox[SKY].max.y) || 
	   (boundingBox1.max.y <= boundingBox[SKY].min.y) ||
	   (boundingBox1.max.z >= boundingBox[SKY].max.z) || 
	   (boundingBox1.max.z <= boundingBox[SKY].min.z) ||
	   (boundingBox1.min.x >= boundingBox[SKY].max.x) ||
	   (boundingBox1.min.x <= boundingBox[SKY].min.x) ||
	   (boundingBox1.min.y >= boundingBox[SKY].max.y) || 
	   (boundingBox1.min.y <= boundingBox[SKY].min.y) ||
	   (boundingBox1.min.z >= boundingBox[SKY].max.z) || 
	   (boundingBox1.min.z <= boundingBox[SKY].min.z))
	{
		printf("Collision with sky\n");				   
		return true;
	}
	//printf("No collision with sky\n");
		
	//Tests collision with the city
	if(model[CITY1].CollisionDetection(boundingBox[AIRPLANE]))
	{
		printf("Collision with city\n");
		return true;
	}
	if(model[CITY2].CollisionDetection(boundingBox[AIRPLANE]))
	{
		printf("Collision with city\n");
		return true;
	}

	
	//printf("No collision with city\n");

	/*
	printf("ground boundingbox: \n");
	printf("max.x: %f, max.y: %f, max.z: %f\n", boundingBox[GROUND].max.x, boundingBox[GROUND].max.y, boundingBox[GROUND].max.z);
	printf("min.x: %f, min.y: %f, min.z: %f\n", boundingBox[GROUND].min.x, boundingBox[GROUND].min.y, boundingBox[GROUND].min.z);	

	printf("bool: %d, %d, %d, %d, %d, %d\n", !(boundingbox.min.x <= boundingBox[GROUND].max.x), !(boundingbox.min.x >= boundingBox[GROUND].min.x),
		!(boundingbox.min.y <= boundingBox[GROUND].max.y), !(boundingbox.min.y >= boundingBox[GROUND].min.y),
		!(boundingbox.min.z <= boundingBox[GROUND].max.z), !(boundingbox.min.z >= boundingBox[GROUND].min.z));
	*/
			
	return false;
}


//------------------------------------------------------------------------------
// Function: void init(void) 
// Initialization function
//------------------------------------------------------------------------------
void init(void) 
{
	//Sets black color without any transparency
   	glClearColor((float)185/255, (float)211/255, (float)238/255, 0.0);   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Enables Z buffer	
   	glEnable(GL_DEPTH_TEST);
	
	initModels();
	initBMPTextures();
	initTGATextures();
	initCameras();	
	initLights();
	initBMPModelsBoundingBoxes();
}


//------------------------------------------------------------------------------
// Function: void DrawScene()
// Draws the objects of the scene
//------------------------------------------------------------------------------
void DrawScene(bool topview = false)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	
	//Draw ground
	glBindTexture(GL_TEXTURE_2D, textureName[GROUND_TEXTURE]);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0.0, 0.0); 
        glVertex3f(0, 0, 0);
        glTexCoord2f(0.0, GROUND_SQUARE_SIZE); 
        glVertex3f(0, 0, GROUND_SIZE);
        glTexCoord2f(GROUND_SQUARE_SIZE, GROUND_SQUARE_SIZE); 
        glVertex3f(GROUND_SIZE, 0, GROUND_SIZE);
        glTexCoord2f(GROUND_SQUARE_SIZE, 0.0); 
        glVertex3f(GROUND_SIZE, 0, 0);
    glEnd();
	
	//Draw the city
	glPushMatrix();	
		model[CITY1].DrawModel();
	glPopMatrix();
	glPushMatrix();	
		model[CITY2].DrawModel();
	glPopMatrix();	
	
	//Draw the airport
	glPushMatrix();	
		model[AIRPORT].DrawModel();
	glPopMatrix();

	//Draw airplane1
	glPushMatrix();
		model[AIRPLANE1].DrawModel();
		cout << "Model" << endl;
		cout << "Rotated X: " << model[AIRPLANE1].moviment.GetRotatedX() << ", sin rotX: " << sin(model[AIRPLANE1].moviment.GetRotatedX() * PI/180) << ", cos rotX: " << cos(model[AIRPLANE1].moviment.GetRotatedX() * PI/180) << endl;
        cout << "Rotated Y: " << model[AIRPLANE1].moviment.GetRotatedY() << ", sin rotY: " << sin(model[AIRPLANE1].moviment.GetRotatedY() * PI/180) << ", cos rotY: " << cos(model[AIRPLANE1].moviment.GetRotatedY() * PI/180) << endl;
        cout << "Rotated Z: " << model[AIRPLANE1].moviment.GetRotatedZ() << ", sin rotZ: " << sin(model[AIRPLANE1].moviment.GetRotatedZ() * PI/180) << ", cos rotZ: " << cos(model[AIRPLANE1].moviment.GetRotatedZ() * PI/180) << endl;
        cout << "Position.x: " << model[AIRPLANE1].moviment.GetPositionX() << endl;     
        cout << "Position.y: " << model[AIRPLANE1].moviment.GetPositionY() << endl;
        cout << "Position.z: " << model[AIRPLANE1].moviment.GetPositionZ() << endl;     
        cout << "ViewDir.x: " << model[AIRPLANE1].moviment.GetViewDirX() << endl;       
        cout << "ViewDir.y: " << model[AIRPLANE1].moviment.GetViewDirY() << endl;
        cout << "ViewDir.z: " << model[AIRPLANE1].moviment.GetViewDirZ() << endl << endl;
        
        cout << "Camera" << endl;
		cout << "Rotated X: " << camera[PERSPECTIVE].moviment.GetRotatedX() << ", sin rotX: " << sin(camera[PERSPECTIVE].moviment.GetRotatedX() * PI/180) << ", cos rotX: " << cos(camera[PERSPECTIVE].moviment.GetRotatedX() * PI/180) << endl;
        cout << "Rotated Y: " << camera[PERSPECTIVE].moviment.GetRotatedY() << ", sin rotY: " << sin(camera[PERSPECTIVE].moviment.GetRotatedY() * PI/180) << ", cos rotY: " << cos(camera[PERSPECTIVE].moviment.GetRotatedY() * PI/180) << endl;
        cout << "Rotated Z: " << camera[PERSPECTIVE].moviment.GetRotatedZ() << ", sin rotZ: " << sin(camera[PERSPECTIVE].moviment.GetRotatedZ() * PI/180) << ", cos rotZ: " << cos(camera[PERSPECTIVE].moviment.GetRotatedZ() * PI/180) << endl;
        cout << "Position.x: " << camera[PERSPECTIVE].moviment.GetPositionX() << endl;  
        cout << "Position.y: " << camera[PERSPECTIVE].moviment.GetPositionY() << endl;
        cout << "Position.z: " << camera[PERSPECTIVE].moviment.GetPositionZ() << endl;  
        cout << "ViewDir.x: " << camera[PERSPECTIVE].moviment.GetViewDirX() << endl;    
        cout << "ViewDir.y: " << camera[PERSPECTIVE].moviment.GetViewDirY() << endl;
        cout << "ViewDir.z: " << camera[PERSPECTIVE].moviment.GetViewDirZ() << endl << endl;        
	glPopMatrix();

	//Draw Sky
	if(topview == false)
	{
		glPushMatrix();
			DrawSky();
		glPopMatrix();
	}		  
}


//------------------------------------------------------------------------------
// Function: void PerspectiveViewport()
// Called when viewmode is selected to a perspective viewing. 
// Uses as global variable camera[ORTHOGRAPHIC], initialized when the 
// perspective viewing is selected
//------------------------------------------------------------------------------ 
void PerspectiveViewport(void)
{	
	GLsizei width = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei height = glutGet(GLUT_WINDOW_HEIGHT);

	camera[PERSPECTIVE].SetPerspAspect( (GLfloat)width / (GLfloat)height );
	
	//Speficies the manipulation of the projection matrix
	glMatrixMode(GL_PROJECTION);
	
	//Initializes projection matrix with the identity matrix
	glLoadIdentity();

	//Specifies perspective projection
    //void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar); 
	gluPerspective(camera[PERSPECTIVE].GetPerspAngle(),
				   camera[PERSPECTIVE].GetPerspAspect(), 
				   camera[PERSPECTIVE].GetPerspNear(),
				   camera[PERSPECTIVE].GetPerspFar());

	//Sets the viewport
	glMatrixMode(GL_MODELVIEW); 
	glViewport(0, 0, width, height);	  
}


//------------------------------------------------------------------------------
// Function: void OrthoViewport()
// Called when viewmode is selected to a orthographic viewing in the main screen,
// viewmode == VIEWMODE4
// Global variables: camera[ORTHOGRAPHIC]
//------------------------------------------------------------------------------
void OrthoViewport()
{
	GLsizei width = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei height = glutGet(GLUT_WINDOW_HEIGHT);
 	
    //Speficies the manipulation of the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 
 	//The topview viewport will now always follow the plane
	camera[ORTHOGRAPHIC].SetEyeX(model[aircraft].moviment.GetPositionX());
	camera[ORTHOGRAPHIC].SetEyeY(model[aircraft].moviment.GetPositionY()+3.0);
	camera[ORTHOGRAPHIC].SetEyeZ(model[aircraft].moviment.GetPositionZ());
	camera[ORTHOGRAPHIC].SetAtX(model[aircraft].moviment.GetPositionX());
	camera[ORTHOGRAPHIC].SetAtY(model[aircraft].moviment.GetPositionY());
	camera[ORTHOGRAPHIC].SetAtZ(model[aircraft].moviment.GetPositionZ());
 
 	//Sets the viewport 
 	glOrtho(camera[ORTHOGRAPHIC].GetOrthoMinX() - camera[ORTHOGRAPHIC].GetOrthoInc(),
            camera[ORTHOGRAPHIC].GetOrthoMaxX() + camera[ORTHOGRAPHIC].GetOrthoInc(),
            camera[ORTHOGRAPHIC].GetOrthoMinY() - camera[ORTHOGRAPHIC].GetOrthoInc(),
            camera[ORTHOGRAPHIC].GetOrthoMaxY() - camera[ORTHOGRAPHIC].GetOrthoInc(),
            camera[ORTHOGRAPHIC].GetOrthoNearPlane(), 
            camera[ORTHOGRAPHIC].GetOrthoFarPlane()); //Sets the camera viewport and orthographic visualization    

	gluLookAt(camera[ORTHOGRAPHIC].GetEyeX(), camera[ORTHOGRAPHIC].GetEyeY(), 
			  camera[ORTHOGRAPHIC].GetEyeZ(), camera[ORTHOGRAPHIC].GetAtX(), 
			  camera[ORTHOGRAPHIC].GetAtY(), camera[ORTHOGRAPHIC].GetAtZ(), 
			  camera[ORTHOGRAPHIC].GetUpX(), camera[ORTHOGRAPHIC].GetUpY(), 
			  camera[ORTHOGRAPHIC].GetUpZ());

	glMatrixMode(GL_MODELVIEW); 
	glViewport(0, 0, width, height); 
}


//------------------------------------------------------------------------------
// Function: void OrthoViewport2()
// Called when secundary viewport needs to be draw, top view on right upper part
// of the screen
// Global variables: camera[ORTHOGRAPHIC]
//------------------------------------------------------------------------------
void OrthoViewport2()
{
	GLsizei width = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei height = glutGet(GLUT_WINDOW_HEIGHT);
 	
    //Speficies the manipulation of the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//The topview viewport will now always follow the plane
	camera[ORTHOGRAPHIC].SetEyeX(model[aircraft].moviment.GetPositionX());
	camera[ORTHOGRAPHIC].SetEyeY(model[aircraft].moviment.GetPositionY()+3.0);
	camera[ORTHOGRAPHIC].SetEyeZ(model[aircraft].moviment.GetPositionZ());
	camera[ORTHOGRAPHIC].SetAtX(model[aircraft].moviment.GetPositionX());
	camera[ORTHOGRAPHIC].SetAtY(model[aircraft].moviment.GetPositionY());
	camera[ORTHOGRAPHIC].SetAtZ(model[aircraft].moviment.GetPositionZ());
	
	glOrtho(camera[ORTHOGRAPHIC].GetOrthoMinX(), camera[ORTHOGRAPHIC].GetOrthoMaxX(),
           	camera[ORTHOGRAPHIC].GetOrthoMinY(), camera[ORTHOGRAPHIC].GetOrthoMaxY(),
 	        camera[ORTHOGRAPHIC].GetOrthoNearPlane(), 
 	        camera[ORTHOGRAPHIC].GetOrthoFarPlane());

	gluLookAt(camera[ORTHOGRAPHIC].GetEyeX(), camera[ORTHOGRAPHIC].GetEyeY(), 
			  camera[ORTHOGRAPHIC].GetEyeZ(), camera[ORTHOGRAPHIC].GetAtX(), 
			  camera[ORTHOGRAPHIC].GetAtY(), camera[ORTHOGRAPHIC].GetAtZ(), 
			  camera[ORTHOGRAPHIC].GetUpX(), camera[ORTHOGRAPHIC].GetUpY(), 
			  camera[ORTHOGRAPHIC].GetUpZ());

	glMatrixMode(GL_MODELVIEW);   	
	glLoadIdentity();
	glViewport(0.75*width, 0.75*height, 0.25*width, 0.25*height);
}

//------------------------------------------------------------------------------
// Function: void display(void)
// Callback function for glutDisplayFunc()
// Draw the models on the scene.
//------------------------------------------------------------------------------
void display(void)
{ 	
	//Clears the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

	if(viewmode == VIEWMODE3)
		camera[PERSPECTIVE].moviment.MoveForwardsBackwards(0.0);			
	
	model[aircraft].moviment.MoveForwards();	
	
	if(TestCollisions())
	{
		printf("\n\nThe airplane collided.\n\n"); 
		exit(0);
	}
	
	switch(viewmode)
	{
		//VIEWMODE1: perspective viewing, 3rd person view, camera motion
		case VIEWMODE1: 
		//VIEWMODE2: perspective viewing, 3rd person view, airplane motion
		case VIEWMODE2:
        //VIEWMODE3: perspective viewing, 1rd person view, camera and airplane motion, together, birds eye view
		case VIEWMODE3:	
			glLoadIdentity();
			camera[PERSPECTIVE].moviment.RenderCamera();
			PerspectiveViewport();						
			SUN.lighting();
			DrawScene();
			break;

		//VIEWMODE4: orthographic viewing, 3rd person view, top view	
		case VIEWMODE4:
			OrthoViewport();	
			SUN.lighting();
			DrawScene(true);			
			break;				
	}
	
	//Right-Up viewport with top viewing
	if(viewmode != VIEWMODE4)
	{
		OrthoViewport2();	
		DrawScene(true);
		//DrawTopViewSquare();
	}
	
	usleep(2000);

	glFlush();
	//Garantees the execution of the drawing commands
	glutSwapBuffers();  
}

//------------------------------------------------------------------------------
// Function: void keyboard(unsigned char key, int x, int y)
// Callback function for glutKeyboardFunc().
// Handles the pressed keys of the keyboard
//------------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	float rotationInc = 2.0;
	float translationInc = 0.01;

	switch(key) 
	{
		case 27: //ESC key
			exit(0);
         	break;

        //Selects VIEWMODE1: perspective viewing, 3rd person view, camera motion
        case '1':
	        viewmode = VIEWMODE1;
	        //camera[PERSPECTIVE].SetCameraPosition(0.0, 1.5, 10.0);
        	break;

        //Selects VIEWMODE2: perspective viewing, 3rd person view, airplane motion
        case '2':
        	viewmode = VIEWMODE2;
        	//camera[PERSPECTIVE].SetCameraPosition(0.0, 1.5, 10.0);
        	break;
        	
        //Selects VIEWMODE3: perspective viewing, 1rd person view, camera and airplane motion, together, birds eye view
        case '3':
	        viewmode = VIEWMODE3;
	        camera[PERSPECTIVE].moviment.SetPosition(model[aircraft].moviment.GetPositionX(), 
									    		  	 model[aircraft].moviment.GetPositionY(), 
											 	  	 model[aircraft].moviment.GetPositionZ());

			camera[PERSPECTIVE].moviment.SetViewDir(model[aircraft].moviment.GetViewDirX(), 
												  	model[aircraft].moviment.GetViewDirY(), 
											 	  	model[aircraft].moviment.GetViewDirZ());

			camera[PERSPECTIVE].moviment.SetRotatedX(0.0);
			camera[PERSPECTIVE].moviment.RotateX(-model[aircraft].moviment.GetRotatedX());
			camera[PERSPECTIVE].moviment.SetRotatedY(180.0);
			camera[PERSPECTIVE].moviment.RotateY(model[aircraft].moviment.GetRotatedY());
			camera[PERSPECTIVE].moviment.SetRotatedZ(0.0);
			camera[PERSPECTIVE].moviment.RotateZ(-model[aircraft].moviment.GetRotatedZ());
	        
			if(model[aircraft].moviment.GetSpeed() == 0)	
				camera[PERSPECTIVE].moviment.SetSpeed(-model[aircraft].moviment.GetSpeed());
			else
				camera[PERSPECTIVE].moviment.SetSpeed(model[aircraft].moviment.GetSpeed());

			
        	break;        	

		//Selects VIEWMODE4: orthographic viewing, 3rd person view, top view	             	
        case '4':
        	viewmode = VIEWMODE4;
        	glMatrixMode(GL_MODELVIEW); 
        	glLoadIdentity();
        	break;	
        	
        //Rotation for the light 	
	  	case 'b':  
		  	SUN.SetRotateX(rotationInc + SUN.GetRotateX());
				if(SUN.GetRotateX() > 360.0) 
					SUN.SetRotateX(0.0);
         	break;
	  	case 'n':  
		  	SUN.SetRotateY(rotationInc + SUN.GetRotateY());
				if(SUN.GetRotateY() > 360.0) 
					SUN.SetRotateY(0.0);
         	break;
	 	case 'm':         
			SUN.SetRotateZ(rotationInc + SUN.GetRotateZ());
				if(SUN.GetRotateZ() > 360.0) 
					SUN.SetRotateZ(0.0);
         	break;			
	}
	
	if(viewmode == VIEWMODE1 || viewmode == VIEWMODE3)
	{
		switch(key)
		{
			//Camera
			//X axis - rotation and translation
			case 't':		
				if(viewmode == VIEWMODE1)
					camera[PERSPECTIVE].moviment.RotateX(rotationInc);
				break;
			case 'g':		
				if(viewmode == VIEWMODE1)			
					camera[PERSPECTIVE].moviment.RotateX(-rotationInc);
				break;
			case 'a':		
				if(viewmode == VIEWMODE1)			
					camera[PERSPECTIVE].moviment.MoveLeftRight(-10*translationInc);
				else
					camera[PERSPECTIVE].moviment.MoveLeftRight(-translationInc);
				break;
			case 'd':	
				if(viewmode == VIEWMODE1)			
					camera[PERSPECTIVE].moviment.MoveLeftRight(10*translationInc);
				else	
					camera[PERSPECTIVE].moviment.MoveLeftRight(translationInc);			
				break;				
				
			//Y axis - rotation and translation
			case 'q':		
				camera[PERSPECTIVE].moviment.RotateY(rotationInc);
				break;
			case 'e':		
				camera[PERSPECTIVE].moviment.RotateY(-rotationInc);
				break;
			case 'r':			
				if(viewmode == VIEWMODE3)			
					camera[PERSPECTIVE].moviment.RotateX(rotationInc);
				if(viewmode == VIEWMODE1)
					camera[PERSPECTIVE].moviment.MoveUpDown(10*translationInc);
				else
					camera[PERSPECTIVE].moviment.MoveUpDown(translationInc);
				break;
			case 'f':
				if(viewmode == VIEWMODE3)			
					camera[PERSPECTIVE].moviment.RotateX(-rotationInc);
				if(viewmode == VIEWMODE1)
					camera[PERSPECTIVE].moviment.MoveUpDown(10*-translationInc);
				else					
					camera[PERSPECTIVE].moviment.MoveUpDown(-translationInc);
				break;

			//Z axis - rotation and translation
			case 'z':		
				camera[PERSPECTIVE].moviment.RotateZ(rotationInc);
				break;
			case 'x':		
				camera[PERSPECTIVE].moviment.RotateZ(-rotationInc);
				break;
			case 'w':		
				if(viewmode == VIEWMODE3)
					camera[PERSPECTIVE].moviment.UpdateSpeed(-translationInc);
				else
					camera[PERSPECTIVE].moviment.MoveForwardsBackwards(-10*translationInc);
				break;
			case 's':		
				if(viewmode == VIEWMODE3)
					camera[PERSPECTIVE].moviment.UpdateSpeed(translationInc);			
				else
					camera[PERSPECTIVE].moviment.MoveForwardsBackwards(10*translationInc);
				break;
		}
	}

	if(viewmode == VIEWMODE2 || viewmode == VIEWMODE3 || viewmode == VIEWMODE4)	
	{
		switch(key)
		{
			//Airplane
			//X axis - rotation and translation
			case 'a':		
				model[aircraft].moviment.MoveLeftRight(-translationInc);
				break;
			case 'd':		
				model[aircraft].moviment.MoveLeftRight(translationInc);			
				break;				
				
			//Y axis - rotation and translation
			case 'q':		
				model[aircraft].moviment.RotateY(rotationInc);
				break;
			case 'e':		
				model[aircraft].moviment.RotateY(-rotationInc);
				break;
			case 'r':
				model[aircraft].moviment.MoveUpDown(translationInc);
				model[aircraft].moviment.RotateX(rotationInc);				
				break;
			case 'f':
				model[aircraft].moviment.MoveUpDown(-translationInc);
				model[aircraft].moviment.RotateX(-rotationInc);				
				break;

			//Z axis - rotation and translation
			case 'x':		
				model[aircraft].moviment.RotateZ(-rotationInc);
				break;
			case 'z':		
				model[aircraft].moviment.RotateZ(rotationInc);
				break;
			case 'w':		
				model[aircraft].moviment.UpdateSpeed(-translationInc);
				break;
			case 's':		
				model[aircraft].moviment.UpdateSpeed(translationInc);
				break;	   		    	
		}	
	}
	
	glutPostRedisplay();
}



//------------------------------------------------------------------------------
// Function: handleMouse(int button, int state, int x, int y)
// Callback function for glutMouseFunc().
// Handles the pressed keys of the mouse
//------------------------------------------------------------------------------
void handleMouse(int button, int state, int x, int y)
{
	int increment = 5;	
	
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			//Zoom-in
            if(camera[PERSPECTIVE].GetPerspAngle() >= 10.0)
				camera[PERSPECTIVE].SetPerspAngle( camera[PERSPECTIVE].GetPerspAngle() - increment );
            camera[ORTHOGRAPHIC].SetOrthoInc( camera[ORTHOGRAPHIC].GetOrthoInc() - increment/5 ); 
    		}
		}

	if(button == GLUT_RIGHT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			//Zoom-out
			if(camera[PERSPECTIVE].GetPerspAngle() <= 150.0)
				camera[PERSPECTIVE].SetPerspAngle( camera[PERSPECTIVE].GetPerspAngle() + increment );
            camera[ORTHOGRAPHIC].SetOrthoInc( camera[ORTHOGRAPHIC].GetOrthoInc() + increment/5 );  
		}
	}
	
	glutPostRedisplay();
}


//------------------------------------------------------------------------------
// Main 
//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
   	cout << "Initializing..." << endl;	
   	
	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   	
   	//------------------------------------------------------------
	//First Window - Bird's eye view and 3rd persons airplane view
	//------------------------------------------------------------	
	
	//Set the position of the window
	glutInitWindowPosition(0, 450); 	

	//Set the windows size in pixels
	glutInitWindowSize(1280/2, 720/2);
	glutCreateWindow("Main Window");
	
	//GLUT functions
   	glutDisplayFunc(display); 
   	glutIdleFunc(display);
   	glutKeyboardFunc(keyboard);
   	glutMouseFunc(handleMouse);
   	
 	init();
   	
   	glutMainLoop();
   	
   	return 0;
}

