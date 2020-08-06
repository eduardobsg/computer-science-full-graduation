#include "photonchopp.h"

/* GLUT windows */
#define ORIGINAL		0
#define MODIFIED 		1

/* Global Variables */
/* handler for GLUT windows */
int windows[2];

/* dimensions of the original image */
int width, height, channel;

/* for quantization */
int tones = 10;

unsigned char *org_pixels, *mod_pixels, *aux_pixels;
char *org_filename;
char mod_filename[30]; 
IplImage *img;


/* 
Function: 
	loadImage( char* filename, IplImage** img )
Description: 
	loads an image
Parameters:
	@filename: the name of the file we want to load
	@img: pointer of pointer of type IplImage structure. Used 
	to store image information to a pointer from main.cpp
Global Variables:
	@width, @height, @channel: image information
Return: 
	returns the field imageData of the IplImage structure, that
	represents the aligned image data
*/
unsigned char* loadImage( char* filename, IplImage** img ) {
	
	/* data structure for the image */
	*img = NULL;

	/* loads the image */
	*img = cvLoadImage(filename);

	/* always check */	
	if( *img == NULL ) {
		fprintf( stderr, "Cannot load file %s!\n", filename );
		exit(1);
	}
	
	/* width */
	width = (*img)->width;
	/* height */
	height = (*img)->height;
	/* #channels */
	channel = (*img)->nChannels;
	
	/* the field imageData of the IplImg struct contains the 
	image pixels in an unsigned char pointer */
	return (unsigned char*)(*img)->imageData;
}


/*
Function: 
	showImage( IplImage* image )
Description: 
	shows the image in a window
Parameters:
	@image: pointer of type IplImage structure. Used to store
	image information
Global Variables:
	none
Return: 
	void
*/
void showImage( IplImage* img ) {
	
	/* always check */	
	if( img == NULL ) {
		fprintf( stderr, "pointer img is empty!\n" );
		exit(1);
	}

	/* create a window */
	cvNamedWindow( "image", CV_WINDOW_AUTOSIZE );

	/* display the image */
	cvShowImage( "image", img );

	/* wait until the user presses a key */
	cvWaitKey(0);

	/* free memory */
	cvDestroyWindow( "image" );
}


/*
Function: 
	saveImage()
Description: 
	saves the image described by img with the name filename
Parameters:
	none
Global Variables:
	@img: pointer of type IplImage structure with image 
	information
	@mod_filename: the name of the image we are going to save
Return: 
	void
*/
void saveImage() {
	
	/* always check */	
	if( img == NULL ) {
		fprintf( stderr, "pointer *img is empty!\n" );
		exit(1);
	}

	/* always check */	
	if( strlen(mod_filename) == 0 ) {
		fprintf( stderr, "filename is empty! Choose a valid string name.\n" );
		exit(1);
	}
	
	/* before saving we have to flip vertically the image */
	verticalFlip();

	/* saving the image */
	cvSaveImage( mod_filename, img );

	/* the image has been saved, so we have to reflip vertically to get its 
	current state */
	verticalFlip();
}


/* 
Function: 
	reloadImage()
Description: 
	reloads the modified image as the same as the original image
Parameters:
	none
Global Variables:
	@mod_pixels: pointer to represent the modified image
	@org_pixels: pointer to represent the original image
	@width, @height, @channel: image information
Return: 
	void
*/
void reloadImage() {

	/* initilizes the pointer to the modified image */
	memcpy( mod_pixels, org_pixels, width * height * channel );

	//glutReshapeWindow(width, height);
	
	glutPostRedisplay();
}


/* 
Function: 
	initPhotonChopp( char *filename )
Description: 
	makes a series of initialization. Global variables, and glui & glut
Parameters:
	@filename: the first argument of the program, the original image filename
Global Variables:
	@mod_pixels: pointer to represent the modified image
	@org_pixels: pointer to represent the original image
	@org_filename: original image filename
Return: 
	void
*/
void initPhotonChopp( char *filename ) {

	/* initilizes filenames */
	org_filename = (char *) malloc( sizeof(char *) * strlen(filename) );		
	memcpy( org_filename, filename, strlen(filename) );

	//printf("org_filename: %s\n", org_filename);
	//getchar();

	/* initilizes the pointer to the original image */
	mod_pixels = loadImage( org_filename, &img );

	/* setting Glui and Glut */
	setGlut();
	setGlui();	

	/* executes a vertical flip, so the original and modified images won't be upside down 
	at first drawn*/
	verticalFlip();

	/* initilizes the pointer to the original image */
	org_pixels = (unsigned char *) malloc( sizeof(unsigned char *) * width * height * channel );
	memcpy( org_pixels, mod_pixels, width * height * channel );	
}


/*
Function: 
	horizontalFlip()
Description: 
	flips the image in x-assys
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	void
*/
void horizontalFlip() {

	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char *) malloc(width * height * channel * sizeof(unsigned char));
		
	if( aux_pixels ) {
		for( int i = 0; i < height; i++ ) {
			for( int j = 0; j < width; j++ ) {
				/* aux_pixels is a contiguous representation of a 3-dimensional matrix */
				memcpy( aux_pixels + (i * width + j) * channel,
						mod_pixels + ((i * width) + (width - 1 - j)) * channel, 
						channel );
			}
		}
	}

	/* copies the content of aux_pixels to mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* frees the memory for aux_pixels, because we won't use its value again */
	free( aux_pixels );

	glutPostRedisplay();
}


/*
Function: 
	verticalFlip()
Description: 
	flips the image in y-assys
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	void
*/
void verticalFlip() {
	
	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char *) malloc(width * height * channel * sizeof(unsigned char));
	
	if( aux_pixels ) {
		for( int i = 0; i < height; i++) 
			memcpy( aux_pixels + (i * width * channel), 
					mod_pixels + ((height - 1) * width * channel) - (i * width * channel), 
					width * channel );
	}
	
	/* copies the content of aux_pixels to mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* frees the memory for aux_pixels, because we won't use its value again */
	free( aux_pixels );

	glutPostRedisplay();
}


/*
Function: 
	grayScale()
Description: 
	transform the color of the image to tones of gray
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	void
*/
void grayScale() {
	
	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width * height * channel * sizeof(unsigned char*) );
	
	/* reloads the image - initilizes the pointer to the modified image */
	memcpy( mod_pixels, org_pixels, width * height * channel );	

	if(aux_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				*(aux_pixels + (i * width + j) * channel) = 0.299 * (*(mod_pixels + (i * width + j) * channel) + 2) + //R
															0.587 * (*(mod_pixels + (i * width + j) * channel) + 1) + //G	
															0.114 * (*(mod_pixels + (i * width + j) * channel));	  //B		
				*(aux_pixels + (i * width + j) * channel + 1) = *(aux_pixels + (i * width + j) * channel);
				*(aux_pixels + (i * width + j) * channel + 2) = *(aux_pixels + (i * width + j) * channel);
			}
		}
	}
	
	/* updating mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* frees the memory for aux_pixels, because we won't use its value again */
	free( aux_pixels );

	glutPostRedisplay();
}	


/*
Function: 
	quantizeGray()
Description: 
	quantize the numbers of tones of gray in the image
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@tones: number of tones to quantize
Return: 
	void
*/
void quantizeGray() {
	
	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width * height * channel * sizeof(unsigned char*) );
	
	/* reloads the image - initilizes the pointer to the modified image */
	memcpy( mod_pixels, org_pixels, width * height * channel );	

	/* applying gray scale */
	if(aux_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				*(aux_pixels + (i * width + j) * channel) = 0.299 * (*(mod_pixels + (i * width + j) * channel) + 2) + //R
															0.587 * (*(mod_pixels + (i * width + j) * channel) + 1) + //G	
															0.114 * (*(mod_pixels + (i * width + j) * channel));	  //B		
				*(aux_pixels + (i * width + j) * channel + 1) = *(aux_pixels + (i * width + j) * channel);
				*(aux_pixels + (i * width + j) * channel + 2) = *(aux_pixels + (i * width + j) * channel);
			}
		}
	}

	/* updating mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* setting variables to initialize quantization */
	int size = 256 / tones;
	int mean = (size - 1) / 2;	

	if(aux_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width * channel; j++) {
				*(aux_pixels + ((i * width * channel) + j)) = ((*(mod_pixels + ((i * width * channel) + j))) / size) * size + mean;
			}
		}
	}
	
	/* updating mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* frees the memory for aux_pixels, because we won't use its value again */
	free( aux_pixels );

	glutPostRedisplay();
}


/*
Function: 
	quantizeRGB()
Description: 
	quantize the numbers of tones of RGB in the image
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@tones: number of tones to quantize
Return: 
	void
*/
void quantizeRGB() {

	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width * height * channel * sizeof(unsigned char*) );
	
	/* reloads the image - initilizes the pointer to the modified image */
	memcpy( mod_pixels, org_pixels, width * height * channel );

	/* setting variables to initialize quantization */
	int size = 256 / tones;
	int mean = (size - 1) / 2;	

	if(aux_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				*(aux_pixels + (i * width + j) * channel	) = ((*(mod_pixels + ((i * width + j) * channel))) / size) * size + mean;		//B
				*(aux_pixels + (i * width + j) * channel + 1) = ((*(mod_pixels + ((i * width + j) * channel + 1))) / size) * size + mean;	//G
				*(aux_pixels + (i * width + j) * channel + 2) = ((*(mod_pixels + ((i * width + j) * channel + 2))) / size) * size + mean;	//R
			}
		}
	}
	
	/* updating mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* frees the memory for aux_pixels, because we won't use its value again */
	free( aux_pixels );

	glutPostRedisplay();
}


/*
Function: 
	monochrome()
Description: 
	converts the image to monochrome (black & white)
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	void
*/

void monochrome() {

	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width * height * channel * sizeof(unsigned char*) );
	
	/* reloads the image - initilizes the pointer to the modified image */
	memcpy( mod_pixels, org_pixels, width * height * channel );	

	/* applying gray scale */
	if(aux_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				*(aux_pixels + (i * width + j) * channel) = 0.299 * (*(mod_pixels + (i * width + j) * channel) + 2) + //R
															0.587 * (*(mod_pixels + (i * width + j) * channel) + 1) + //G	
															0.114 * (*(mod_pixels + (i * width + j) * channel));	  //B		
				*(aux_pixels + (i * width + j) * channel + 1) = *(aux_pixels + (i * width + j) * channel);
				*(aux_pixels + (i * width + j) * channel + 2) = *(aux_pixels + (i * width + j) * channel);
			}
		}
	}	

	/* updating mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* applying monochrome */	
	if(aux_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width * channel; j++) {
				int color = *(mod_pixels + ((i * width * channel) + j));
				if(color < 128)
					*(aux_pixels + ((i * width * channel) + j)) = 0;
				else
					*(aux_pixels + ((i * width * channel) + j)) = 255;						
			}
		}
	}

	/* updating mod_pixels */
	memcpy( mod_pixels, aux_pixels, width * height * channel );

	/* frees the memory for aux_pixels, because we won't use its value again */
	free( aux_pixels );

	glutPostRedisplay();
}

// -----------------------------------------------------------------------------
// GLUI & GLUT functions
// -----------------------------------------------------------------------------

/*
Function: 
	originalReshape()
Description: 
	event routine treatment, alters the window size
Parameters:
	@width, @height: image screen size information
Global Variables:
	none
Return: 
	void
*/
void originalReshape(int width, int height) { 
	glViewport( 0, 0, (GLsizei) width, (GLsizei) height ); 
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	gluOrtho2D( 0.0, width, 0.0, height ); 
	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity(); 

	/* Resize the window => still needs to resize the content of the window... */
	//glutSetWindow(windows[ORIGINAL]);
    //glutReshapeWindow(300, 400);
}


/*
Function: 
	modifiedReshape()
Description: 
	event routine treatment, alters the window size
Parameters:
	@width, @height: image screen size information
Global Variables:
	none
Return: 
	void
*/
void modifiedReshape(int width, int height) { 
	glViewport( 0, 0, (GLsizei) width, (GLsizei) height ); 
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	gluOrtho2D( 0.0, width, 0.0, height ); 
	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity(); 
}


/*
Function: 
	originalDisplay()
Description: 
	event routine treatment, draws the image on the window
Parameters:
	none
Global Variables:
	@width, @height: image screen size information
	@org_pixels: pointer to represent the pixels of the original image
Return: 
	void
*/
void originalDisplay() { 
	glClear( GL_COLOR_BUFFER_BIT ); 
	glRasterPos2i( 0, 0 ); 
	glDrawPixels( width, height, GL_BGR, GL_UNSIGNED_BYTE, org_pixels ); 
	glutSwapBuffers(); 
}


/*
Function: 
	modifiedDisplay()
Description: 
	event routine treatment, draws the image on the window
Parameters:
	none
Global Variables:
	@width, @height: image screen size information
	@mod_pixels: pointer to represent the pixels of the modified image
Return: 
	void
*/
void modifiedDisplay() { 
	glClear( GL_COLOR_BUFFER_BIT ); 
	glRasterPos2i( 0, 0 ); 
	glDrawPixels( width, height, GL_BGR, GL_UNSIGNED_BYTE, mod_pixels ); 
	glutSwapBuffers(); 
}


/*
Function: 
	setGlut()
Description: 
	intializes GLUT in the default way
Parameters:
	none
Global Variables:
	@width, @height: image screen size information
	@windows: integer array to handle the glut windows
Return: 
	void
*/
void setGlut() {
	
	/* aux and aux2 are passed to glutInit to make it initialize 
	glut in default way */
	char *aux = NULL; int aux2 = 1;
	glutInit( &aux2, &aux );

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB ); 
	glutInitWindowPosition( 0, 0 ); 
	glutInitWindowSize( width, height ); 
	windows[ORIGINAL] = glutCreateWindow( "Original Image" ); 
	glutDisplayFunc( originalDisplay ); 
	glutReshapeFunc( originalReshape ); 
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glClearColor( 0.0, 0.0, 0.0, 0 );
	
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB ); 
	glutInitWindowPosition( width, 0 ); 
	glutInitWindowSize( width, height ); 
	windows[MODIFIED] = glutCreateWindow( "Modified Image" ); 
	glutDisplayFunc( modifiedDisplay ); 
	glutReshapeFunc( modifiedReshape ); 
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glClearColor( 0.0, 0.0, 0.0, 0 );
}


/*
Function: 
	setGlui()
Description: 
	intializes Glui
Parameters:
	none
Global Variables:
	@mod_filename: name of the modified object
	@windows: integer array handle for glut windows
	@width: width of the original image
Return: 
	void
*/
void setGlui() {
	GLUI *glui = GLUI_Master.create_glui( "Menu", 0, 2 * width, 0 );

	GLUI_Panel *obj_panel = glui->add_panel( "File" );
	GLUI_EditText *edittext = glui->add_edittext_to_panel(obj_panel, "Modified image name:", GLUI_EDITTEXT_TEXT, mod_filename);			
	glui->add_button_to_panel(obj_panel, "Save", -1, (GLUI_Update_CB)saveImage);
	glui->add_button_to_panel(obj_panel, "Reload Original Image", -1, (GLUI_Update_CB)reloadImage);

	glui->add_separator();

	GLUI_Panel *obj_panel2 = glui->add_panel( "Flip" );
	glui->add_button_to_panel( obj_panel2, "Hozirontal", -1, (GLUI_Update_CB)horizontalFlip );
	glui->add_button_to_panel( obj_panel2, "Vertical", -1, (GLUI_Update_CB)verticalFlip );

	glui->add_separator();
	
	GLUI_Panel *obj_panel4 = glui->add_panel ("Color");
	GLUI_Spinner *segment_spinner = glui->add_spinner_to_panel(obj_panel4, "Quantization - # of colors:", GLUI_SPINNER_INT, &tones);
	segment_spinner->set_int_limits(1, 256, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel4, "Quantize Gray", -1, (GLUI_Update_CB)quantizeGray);
	glui->add_button_to_panel(obj_panel4, "Quantize RGB", -1, (GLUI_Update_CB)quantizeRGB);
	glui->add_button_to_panel(obj_panel4, "Gray Scale", -1, (GLUI_Update_CB)grayScale);
	glui->add_button_to_panel(obj_panel4, "Monochrome", -1, (GLUI_Update_CB)monochrome);	

	glui->set_main_gfx_window(windows[MODIFIED]);
	GLUI_Master.set_glutIdleFunc(NULL);
}
