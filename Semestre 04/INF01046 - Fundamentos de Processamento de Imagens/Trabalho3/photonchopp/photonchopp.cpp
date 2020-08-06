#include "photonchopp.h"

/* GLUT windows */
#define ORIGINAL			0
#define MODIFIED			1
#define HISTOGRAM			2
#define EQUALIZED_HISTOGRAM 3 

#define HISTROGRAM_WINDOW_SIZE 256

/* Global Variables */

/* handler for GLUT windows */
int windows[4];

/* dimensions of the original image */
int width, original_width;
int height, original_height;
int channel;

/* for quantization, bright and contrast */
int tones = 10;
int bias = 0;
float gain = 1;
int grayScaleFlag = 0; //The grayScale flag equal zero tells the functions that the gray scale HAVEN'T been done yet.

/* pointers to the matrix images */
unsigned char *org_pixels;
unsigned char *mod_pixels;
unsigned char *aux_pixels;

/* zoomOut parameters */
int w_factor = 2;
int h_factor = 2;

/* convolution */
float kernel[3][3] = {0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625};
GLUI_Spinner *segment_spinner6, *segment_spinner7, *segment_spinner8, *segment_spinner9,
*segment_spinner10, *segment_spinner11, *segment_spinner12, *segment_spinner13, *segment_spinner14;


float histogram[256] = {0};
float equalizedHistogram[256] = {0};

char *org_filename;
char mod_filename[30]; 
IplImage *img;


/*
Function: 
	getPixel(int x, int y, int channel, unsigned char * imageArray, int width)
Description: 
	given some parameters, returns a pointer to a pixel 
Parameters:
	@x: pixel x position
	@y: pixel y position
	@channel: number of channels of the image
	@imageArray: the array of the image
	@width: width of the image
Global Variables:
	none
Return: 
	a pointer to a pixel of the image
*/
unsigned char * getPixel( int x, int y, int channel, unsigned char * imageArray, int width ) {
	return (imageArray + (channel * (x * width + y)));
}


/*
Function: 
	drawLine()
Description: 
	draws a line of the histogram in a window of 256x256 resolution
	
	OpenGL uses values from -1 to 1 for coordinates variation
	One given pixel has a value from 0 to w*h (for its frequency in the histogram)
	So, we have to normalize these values
	Algorithm:
		x axis: x = (tone_color/255)*2 - 1 -> this -1 is because of the offset (variation from -1 to 1!)
		y axis: y = (tone_frequency/w*h)*2 - 1
Parameters:
	@quant: the quantity of tones of a certain tone
	@lineNum: the number of the line that is gonna be drawn
Global Variables:
	@width, @height: image screen size information
Return: 
	void
*/
void drawLine(float quant, float lineNum) {

	glBegin(GL_LINES);
		glColor3f(0,0,1);
		glVertex2f((lineNum/255.0f)*2 - 1.0f, (quant/((float)width *(float)height)*255 - 1.0f));	
		glVertex2f((lineNum/255.0f)*2 - 1.0f, -1.0f);	
	glEnd();

}


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
	original_width = width;

	/* height */
	height = (*img)->height;
	original_height = height;

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
	@grayScaleFlag: flag for gray scale. If its equal 1, then the gray scale has been already done.
Return: 
	void
*/
void reloadImage() {

	grayScaleFlag = 0;

	height = original_height;
	width = original_width;
	glutReshapeWindow(width, height);

	/* initilizes the pointer to the modified image */
	memcpy( mod_pixels, org_pixels, width * height * channel );

	glutPostRedisplay();

	/* clears the histogram windows */
	memset(histogram, '\0', sizeof(histogram));
	glutSetWindow(windows[HISTOGRAM]);
	glutShowWindow();
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	memset(equalizedHistogram, '\0', sizeof(equalizedHistogram));
	glutSetWindow(windows[EQUALIZED_HISTOGRAM]);
	glutShowWindow();
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
void initPhotonChopp( char *org_filename ) {
	
	/* org_filename has been initilized */
	//printf("org_filename: %s\n", org_filename);

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
		for( int i = 0; i < height; i++ ) 
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
	rotateRight()
Description: 
	Executes 90 degree rotation right
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	void
*/
void rotateRight() {

	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char *) malloc(width * height * channel * sizeof(unsigned char));
	
	/* copies the content of aux_pixels to mod_pixels */
	memcpy( aux_pixels, mod_pixels, (width * height * channel * sizeof(unsigned char)) );
	
	/* unsigned char * getPixel( int x, int y, int channel, unsigned char * imageArray, int width ) { */
	
	/* for all the lines of the image */
	for( int i = 0; i < height; i++ ) {		
		for( int j = 0; j < width; j++ ) {
			memcpy(getPixel(width - j - 1, i, channel, mod_pixels, height), getPixel(i, j , channel, aux_pixels, width), channel * sizeof(unsigned char));
		}
	}
	
	/* We've got to refresh the image resolution */
	unsigned int aux = width;
	width = height;
	height = aux;
	
	/* redefine the size of the modified image window */
	glutReshapeWindow(width, height);	
	glutPostRedisplay();

	/* frees the memory for aux_pixels, because we won't use its value again */
	free(aux_pixels);
}


/*
Function: 
	rotateLeft()
Description: 
	Executes 90 degree rotation left
Parameters: 
	none
Global Variable:
	none (see rotateRight())
Return: 
	void
*/
void rotateLeft() {
	rotateRight();
	horizontalFlip();
	verticalFlip();
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
	
	/* sets the gayScale flag. Used for monochrome. */
	grayScaleFlag = 1; 
	
	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width * height * channel * sizeof(unsigned char*) );
	
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
	@org_pixels: pointer to represent the original image
	@aux_pixels: auxiliar pointer to represent a contiguous set of pixels
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@tones: number of tones to quantize
Return: 
	void
*/
void quantizeGray() {
	
	reloadImage();
	
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
	monochrome()
Description: 
	converts the modified image to monochrome (black & white)
Parameters: 
	none
Global Variable:
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@grayScaleFlag: flag for gray scale. If its equal 1, then the gray scale has been already done.
Return: 
	void
*/
void monochrome() {

	/* applying gray scale */
	if(!grayScaleFlag) { //Gray Scale is done if the flag is equal 0
		grayScale();
	}

	/* applying monochrome */	
	if(mod_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width * channel; j++) {
				int color = *(mod_pixels + ((i * width * channel) + j));
				if(color < 128)
					*(mod_pixels + ((i * width * channel) + j)) = 0;
				else
					*(mod_pixels + ((i * width * channel) + j)) = 255;						
			}
		}
	}

	glutPostRedisplay();
}


/*
Function: 
	negative()
Description: 
	converts the modified to its negative
Parameters: 
	none
Global Variable:
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	void
*/
void negative() {

	/* applying negative */
	if(mod_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				for(int k = 0; k < channel; k++) {
					*(mod_pixels + (i * width + j) * channel + k) = 255 - *(mod_pixels + (i * width + j) * channel + k);
				}
			}
		}
	}	

	glutPostRedisplay();
}


/*
Function: 
	bright()
Description: 
	applies bright ajust to the modified image window
Parameters: 
	none
Global Variable:
	@mod_pixels: pointer to represent the modified image
	@bias: holds the value to the brightening
	@width, @height, @channel: image information
Return: 
	void
*/
void bright() {

	/* applying bright ajust */
	if(mod_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				for(int k = 0; k < channel; k++) {
					int sum = *(mod_pixels + (i * width + j) * channel + k) + bias;

					if( sum < 0 )
						 *(mod_pixels + (i * width + j) * channel + k) = 0;
					else if( sum > 255 )
						 *(mod_pixels + (i * width + j) * channel + k) = 255;						
					else
						 *(mod_pixels + (i * width + j) * channel + k) = sum;
				}
			}
		}
	}	

	glutPostRedisplay();
}


/*
Function: 
	contrast()
Description: 
	applies contrast ajust to the modified image window
Parameters: 
	none
Global Variable:
	@mod_pixels: pointer to represent the modified image
	@gain: holds the value to the constrast gain
	@width, @height, @channel: image information
Return: 
	void
*/
void contrast() {

	/* applying brightening */
	if(mod_pixels) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				for(int k = 0; k < channel; k++) {
					int mult = *(mod_pixels + (i * width + j) * channel + k) * gain;

					if( mult > 255 )
						 *(mod_pixels + (i * width + j) * channel + k) = 255;
					else
						 *(mod_pixels + (i * width + j) * channel + k) = mult;
				}
			}
		}
	}	

	glutPostRedisplay();
}


/*
Function: 
	calcHistogram()
Description: 
	calculates the histogram of the original image
Parameters: 
	none
Global Variable:
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@histogram: vector with the histogram values
Return: 
	void
*/
void calcHistogram() {

	/* Testes if the gray scale has already been done */
	/*
	if( !grayScaleFlag ) {
		grayScale();	
	} */
		
	/* erases the histogram vector */		
	memset(histogram, 0, sizeof(histogram));
	
	/* calculates the histogram */
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			histogram[ *(mod_pixels + (i * width + j) * channel) ] += 1;
		}
	}
	
	glutPostRedisplay();
	histogramDisplay();
}


/*
Function: 
	calcEqualizedHistogram()
Description: 
	calculates the equalized histogram of the original image
Parameters: 
	none
Global Variable:
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@histogram: vector with the histogram values
Return: 
	void
*/
void calcEqualizedHistogram() {
	
	float alfa = 255.0 / ( (float)width * (float)height );
	
	/* calculates the histogram */
	calcHistogram();
	
	/* erases the histogram vector */		
	memset(equalizedHistogram, 0, sizeof(equalizedHistogram));
	
	equalizedHistogram[0] = alfa * histogram[0];

	for(int i = 1; i < 256; i++){
		equalizedHistogram[i] = equalizedHistogram[i-1] + alfa * histogram[i];
	}
	
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < channel; k++) {
				*(mod_pixels + (i * width + j) * channel + k) = equalizedHistogram[*(mod_pixels + (i * width + j) * channel + k)];
			}
		}
	}

	glutPostRedisplay();
	equalizedHistogramDisplay();
}


/*
Function: 
	zoomIn()
Description: 
	Makes Zoom in on the image (2 x 2)
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	void
*/
void zoomIn() {

	int width2 = 2 * width - 1;
	int height2 = 2 * height - 1;	

	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width2 * height2 * channel * sizeof(unsigned char*) );
	
	/* now we copy the image to the bigger array */
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			memcpy(getPixel(2*i, 2*j, channel, aux_pixels, width2), getPixel(i, j, channel, mod_pixels, width), channel);
		}
	}

	/* first, we interpolate through the even lines, the odd ones stay blank */
	for(int i = 0; i < height2; i += 2) {
		for(int j = 1; j < width2; j += 2) {
			for(int k = 0; k < channel; k++) {
				*(getPixel(i, j, channel, aux_pixels, width2) + k) = 
					0.5 * ( *(getPixel(i, j + 1, channel, aux_pixels, width2) + k) +
					 		*(getPixel(i, j - 1, channel, aux_pixels, width2) + k) 
					 	  );
			}
		}
	}
	
	/* second, we interpolate through all columns (j) and just in the odd lines */
	for(int i = 1; i < height2; i += 2) {
		for(int j = 0; j < width2; j++) {
			for(int k = 0; k < channel; k++) {
				*(getPixel(i, j, channel, aux_pixels, width2) + k) = 
					0.5 * ( *(getPixel(i - 1, j, channel, aux_pixels, width2) + k) +
							*(getPixel(i + 1, j, channel, aux_pixels, width2) + k) 
						  );
			}		
		}
	}

	/* frees the memory for mod_pixels, because we have to alloc space again with the new height and width */
	//free(mod_pixels); //gives error...
	
	/* allocates memory for the array of the modified image */
	mod_pixels = (unsigned char*) malloc(width2 * height2 * channel * sizeof(unsigned char));

	/* updating mod_pixels */
	memcpy(mod_pixels, aux_pixels, width2 * height2 * channel * sizeof(unsigned char));

	/* frees the memory for mod_pixels, because we aren't using it anymore for now */
	free(aux_pixels);
	
	/* updates global variables */
	height = height2;
	width = width2;
	
	/* draws the modified image windows with the new width and height */
	glutReshapeWindow(width, height);	
	glutPostRedisplay();
}


/*
Function: 
	zoomOut(int i, int j, int ch)
Description: 
	Makes Zoom out on the image (n x m)
Parameters: 
	@i: x position on the image matrix
	@j: y poition on the image matrix
	@ch: the channel of the image
Global Variable:
	@width, @height, @channel: image information
	@w_factor, h_factor: variables for zoom out scaling in x and y coordinates
Return: 
	void
*/
int meanZoomOut(int i, int j, int ch) {
	
	int mean = 0;
	int values = 0;
	
	for(int x = 0; x < h_factor; x++) {
		for(int y = 0; y < w_factor; y++) {
			/* we should test if the image indexes are not out of bounds */
			if((i * h_factor + x < height) && (j * w_factor + y < width)) {
				mean += *(getPixel(i * h_factor + x, j * w_factor + y, channel, mod_pixels, width) + ch);
				values++;
			}
		}
	}
	return mean / values;
}


/*
Function: 
	zoomOut()
Description: 
	Makes Zoom out on the image (n x m)
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@w_factor, h_factor: variables for zoom out scaling in x and y coordinates
Return: 
	void
*/
void zoomOut() {

	int width2 = (width / w_factor + (width % w_factor ? 1 : 0));
	int height2 = (height / h_factor + (height % h_factor ? 1 : 0));
	
	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width2 * height2 * channel * sizeof(unsigned char*) );
	
	/* select the pixels for the zoom out */
	for(int i = 1; i < height2; i++) {
		for(int j = 0; j < width2; j++) {
			for(int k = 0; k < channel; k++) {
				*(getPixel(i, j, channel, aux_pixels, width2) + k) = (unsigned char)meanZoomOut(i, j, k);
			}
		}
	}	
	
	/* frees the memory for mod_pixels, because we have to alloc space again with the new height and width */
	//free(mod_pixels); //gives error...
	
	/* allocates memory for the array of the modified image */
	mod_pixels = (unsigned char*) malloc(width2 * height2 * channel * sizeof(unsigned char));
	
	/* updating mod_pixels */
	memcpy(mod_pixels, aux_pixels, width2 * height2 * channel * sizeof(unsigned char));
	
	/* frees the memory for mod_pixels, because we aren't using it anymore for now */
	free(aux_pixels);
	
	/* updates global variables */
	height = height2;
	width = width2;
	
	/* draws the modified image windows with the new width and height */
	glutReshapeWindow(width, height);		
	glutPostRedisplay();
}


/*
Function: 
	returnConvolution(int i, int j, int ch)
Description: 
	does the convolution in one pixel
Parameters: 
	@i: the x pixel position on the image
	@j: the y pixel position on the image
	@ch: the channel of the pixel
Global Variable:
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
	@kernel: the kernel with the values of the filter
Return: 
	the value of the convolution
*/
float returnConvolution(int i, int j, int ch) {
	
	float accum = 0;
	
	for(int x = -1; x < 2; x++) {
		for(int y = -1; y < 2; y++) {
			/* if the index is out of the image bounds, we use zero */
			if(	0 < (x + i) && (x + i) < height &&
				0 < (y + j) && (y + j) < width ) {
					accum += kernel[1 - x][1 - y] * (float) *(getPixel(i + x, j + y, channel, mod_pixels, width) + ch);				
			}
		}
	}
		
	/* we should test if the value of accum can be stored in an unsigned char */
	if(accum < 0) {
		return 0.0;
	} else if(accum > 255) {
		return 255.0;	
	} else {
		return accum;
	}
}

/*
Function: 
	convolution()
Description: 
	does the convolution in one pixel
Parameters: 
	none
Global Variable:
	@aux_pixels: auxiliar pointer
	@mod_pixels: pointer to represent the modified image
	@width, @height, @channel: image information
Return: 
	none
*/
void convolution() { 
	
	/* allocates memory for the auxiliar representation of pixels */
	aux_pixels = (unsigned char*) malloc( width * height * channel * sizeof(unsigned char*) );
		
	for(int i = 0; i < height; i++) {
		for(int j = 1; j < width; j++) {
			for(int k = 0; k < channel; k++) {
				*(getPixel(i, j, channel, aux_pixels, width) + k) = (unsigned char)returnConvolution(i, j, k);
			}
		}
	}
	
	/* updating mod_pixels */
	memcpy(mod_pixels, aux_pixels, width * height * channel * sizeof(unsigned char));
	
	/* frees the memory for mod_pixels, because we aren't using it anymore for now */
	free(aux_pixels);
	
	glutPostRedisplay();
}


void setGLUIKernel() {
	segment_spinner6->set_float_val(kernel[0][0]);
	segment_spinner7->set_float_val(kernel[1][0]);
	segment_spinner8->set_float_val(kernel[2][0]);
	segment_spinner9->set_float_val(kernel[0][1]);
	segment_spinner10->set_float_val(kernel[1][1]);
	segment_spinner11->set_float_val(kernel[2][1]);
	segment_spinner12->set_float_val(kernel[0][2]);
	segment_spinner13->set_float_val(kernel[1][2]);
	segment_spinner14->set_float_val(kernel[2][2]);
}

/* Filters */
void Gaussian() {
	kernel[0][0] = 0.0625; kernel[0][1] = 0.1250; kernel[0][2] = 0.0625;
	kernel[1][0] = 0.1250; kernel[1][1] = 0.2500; kernel[1][2] = 0.1250;
	kernel[2][0] = 0.0625; kernel[2][1] = 0.1250; kernel[2][2] = 0.0625;
	setGLUIKernel();
}

void Laplacian() {
	kernel[0][0] = 0.0;  kernel[0][1] = -1.0; kernel[0][2] = 0.0;
	kernel[1][0] = -1.0; kernel[1][1] = 4.0;  kernel[1][2] = -1.0;
	kernel[2][0] = 0.0;  kernel[2][1] = -1.0; kernel[2][2] = 0.0;
	setGLUIKernel();
}

void HighPass() {
	kernel[0][0] = -1.0; kernel[0][1] = -1.0; kernel[0][2] = -1.0;
	kernel[1][0] = -1.0; kernel[1][1] = 8.0;  kernel[1][2] = -1.0;
	kernel[2][0] = -1.0; kernel[2][1] = -1.0; kernel[2][2] = -1.0;
	setGLUIKernel();
}

void PrewittX() {
	kernel[0][0] = -1.0; kernel[0][1] = 0.0; kernel[0][2] = 1.0;
	kernel[1][0] = -1.0; kernel[1][1] = 0.0; kernel[1][2] = 1.0;
	kernel[2][0] = -1.0; kernel[2][1] = 0.0; kernel[2][2] = 1.0;
	setGLUIKernel();
}

void PrewittY() {
	kernel[0][0] = -1.0; kernel[0][1] = -1.0; kernel[0][2] = -1.0;
	kernel[1][0] = 0.0;  kernel[1][1] = 0.0;  kernel[1][2] = 0.0;
	kernel[2][0] = 1.0;  kernel[2][1] = 1.0;  kernel[2][2] = 1.0;
	setGLUIKernel();
}

void SobelX() {
	kernel[0][0] = -1.0; kernel[0][1] = 0.0; kernel[0][2] = 1.0;
	kernel[1][0] = -2.0; kernel[1][1] = 0.0; kernel[1][2] = 2.0;
	kernel[2][0] = -1.0; kernel[2][1] = 0.0; kernel[2][2] = 1.0;
	setGLUIKernel();
}

void SobelY() {
	kernel[0][0] = -1.0; kernel[0][1] = -2.0; kernel[0][2] = -1.0;
	kernel[1][0] = 0.0;  kernel[1][1] = 0.0;  kernel[1][2] = 0.0;
	kernel[2][0] = 1.0;  kernel[2][1] = 2.0;  kernel[2][2] = 1.0;
	setGLUIKernel();
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
	HistogramDisplay()
Description: 
	event routine treatment, draws the histogram of the original image
Parameters:
	none
Global Variables:
	@width, @height: image screen size information
	@mod_pixels: pointer to represent the pixels of the modified image
Return: 
	void
*/
void histogramDisplay() { 
	
	if(glutGetWindow() != windows[HISTOGRAM]) {
		glutSetWindow(windows[HISTOGRAM]);
		glutShowWindow();
	}
	
	glMatrixMode (GL_PROJECTION);
    glViewport(0,0, 256,256);
    glLoadIdentity();
    gluOrtho2D(0, 0, 256, 256);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	for( int i = 0; i < 256; i++ ) {
		drawLine( histogram[i], (float)i );
	}
	
	glutSwapBuffers(); 
}


/*
Function: 
	equalizedHistogramDisplay()
Description: 
	event routine treatment, draws the equalized histogram of the original image
Parameters:
	none
Global Variables:
	@width, @height: image screen size information
	@mod_pixels: pointer to represent the pixels of the modified image
Return: 
	void
*/
void equalizedHistogramDisplay() { 
	
	if(glutGetWindow() != windows[EQUALIZED_HISTOGRAM]) {
		glutSetWindow(windows[EQUALIZED_HISTOGRAM]);
		glutShowWindow();
	}
	
	glMatrixMode (GL_PROJECTION);
    glViewport(0,0, 256,256);
    glLoadIdentity();
    gluOrtho2D(0, 0, 256, 256);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for( int i = 0; i < 256; i++ ) {
		drawLine( equalizedHistogram[i], (float)i );
	}
	
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
	glutInitWindowPosition( 0, height + 50 ); 
	glutInitWindowSize( width, height ); 
	windows[MODIFIED] = glutCreateWindow( "Modified Image" ); 
	glutDisplayFunc( modifiedDisplay ); 
	glutReshapeFunc( modifiedReshape ); 
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glClearColor( 0.0, 0.0, 0.0, 0 );
	
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB ); 
	glutInitWindowPosition( width + 10, 0 ); 
	glutInitWindowSize( HISTROGRAM_WINDOW_SIZE, HISTROGRAM_WINDOW_SIZE ); 
	windows[HISTOGRAM] = glutCreateWindow( "Histogram" ); 
	glutDisplayFunc( histogramDisplay ); 
	glutReshapeFunc( originalReshape ); 
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glClearColor( 0.0, 0.0, 0.0, 0 );
	glutHideWindow();
	
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB ); 
	glutInitWindowPosition( width + 10, HISTROGRAM_WINDOW_SIZE + 50 ); 
	glutInitWindowSize( HISTROGRAM_WINDOW_SIZE, HISTROGRAM_WINDOW_SIZE ); 
	windows[EQUALIZED_HISTOGRAM] = glutCreateWindow( "Equalized Histogram" ); 
	glutDisplayFunc( equalizedHistogramDisplay ); 
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glClearColor( 0.0, 0.0, 0.0, 0 );
	glutHideWindow();
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
	GLUI *glui = GLUI_Master.create_glui("Menu", 0, width + HISTROGRAM_WINDOW_SIZE + 20, 0);

	GLUI_Panel *obj_panel = glui->add_panel("File");
	GLUI_EditText *edittext = glui->add_edittext_to_panel(obj_panel, "Modified image name:", GLUI_EDITTEXT_TEXT, mod_filename);			
	glui->add_button_to_panel(obj_panel, "Save", -1, (GLUI_Update_CB)saveImage);
	glui->add_button_to_panel(obj_panel, "Reload Original Image", -1, (GLUI_Update_CB)reloadImage);

	glui->add_separator();

	GLUI_Panel *obj_panel2 = glui->add_panel("Effects");
	glui->add_button_to_panel( obj_panel2, "Hozirontal Flip", -1, (GLUI_Update_CB)horizontalFlip );
	glui->add_button_to_panel( obj_panel2, "Vertical Flip", -1, (GLUI_Update_CB)verticalFlip );
	glui->add_button_to_panel( obj_panel2, "Rotate Left", NULL, (GLUI_Update_CB)rotateLeft );
	glui->add_button_to_panel( obj_panel2, "Rotate Right", NULL, (GLUI_Update_CB)rotateRight );
	GLUI_Spinner *segment_spinner2 = glui->add_spinner_to_panel(obj_panel2, "Bias (bright):", GLUI_SPINNER_INT, &bias);
	segment_spinner2->set_int_limits(-255, 255, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel2, "Bright Ajust", -1, (GLUI_Update_CB)bright);
	GLUI_Spinner *segment_spinner3 = glui->add_spinner_to_panel(obj_panel2, "Gain (contrast):", GLUI_SPINNER_FLOAT, &gain);
	segment_spinner3->set_float_limits(0, 10, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel2, "Contrast Ajust", -1, (GLUI_Update_CB)contrast);
	GLUI_Spinner *segment_spinner1 = glui->add_spinner_to_panel(obj_panel2, "Quantization - # of colors:", GLUI_SPINNER_INT, &tones);
	segment_spinner1->set_int_limits(1, 256, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel2, "Quantize Gray", -1, (GLUI_Update_CB)quantizeGray);
	
	glui->add_button_to_panel(obj_panel2, "Gray Scale", -1, (GLUI_Update_CB)grayScale);
	glui->add_button_to_panel(obj_panel2, "Monochrome", -1, (GLUI_Update_CB)monochrome);	
	glui->add_button_to_panel(obj_panel2, "Negative", -1, (GLUI_Update_CB)negative);
	
	glui->add_separator();
		
	GLUI_Panel *obj_panel3 = glui->add_panel("Histogram");
	glui->add_button_to_panel(obj_panel3, "Histogram", -1, (GLUI_Update_CB)calcHistogram);
	glui->add_button_to_panel(obj_panel3, "Equalized Histogram", -1, (GLUI_Update_CB)calcEqualizedHistogram);

	glui->add_column(true);
	
	GLUI_Panel *obj_panel4 = glui->add_panel("Zoom");
	glui->add_button_to_panel(obj_panel4, "Zoom in 2x2", NULL, (GLUI_Update_CB)zoomIn);
	GLUI_Spinner *segment_spinner4 = glui->add_spinner_to_panel(obj_panel4, "Width factor:", GLUI_SPINNER_INT, &w_factor);
	segment_spinner4->set_int_limits(1, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner5 = glui->add_spinner_to_panel(obj_panel4, "Height factor:", GLUI_SPINNER_INT, &h_factor);
	segment_spinner4->set_int_limits(1, 2000, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel4, "Zoom Out", NULL, (GLUI_Update_CB)zoomOut);

	glui->add_separator();
	
	GLUI_Panel *obj_panel5 = glui->add_panel("Convolution");
	glui->add_button_to_panel(obj_panel5, "Gaussian", NULL, (GLUI_Update_CB)Gaussian);
	glui->add_button_to_panel(obj_panel5, "Laplacian", NULL, (GLUI_Update_CB)Laplacian);
	glui->add_button_to_panel(obj_panel5, "High-Pass", NULL, (GLUI_Update_CB)HighPass);
	glui->add_button_to_panel(obj_panel5, "Prewitt-X", NULL, (GLUI_Update_CB)PrewittX);
	glui->add_button_to_panel(obj_panel5, "Prewitt-Y", NULL, (GLUI_Update_CB)PrewittY);
	glui->add_button_to_panel(obj_panel5, "Sobel-X", NULL, (GLUI_Update_CB)SobelX);
	glui->add_button_to_panel(obj_panel5, "Sobel-Y", NULL, (GLUI_Update_CB)SobelY);
	glui->add_button("Convolution", NULL, (GLUI_Update_CB)convolution);

	GLUI *glui2 = GLUI_Master.create_glui ("Convolution Kernel", 0, width + 10, 2 * HISTROGRAM_WINDOW_SIZE + 75);
	
	segment_spinner6 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[0][0]);
	segment_spinner6->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);
	segment_spinner7 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[1][0]);
	segment_spinner7->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);
	segment_spinner8 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[2][0]);
	segment_spinner8->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);

	glui2->add_column(false);
	
	segment_spinner9 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[0][1]);
	segment_spinner9->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);
	segment_spinner10 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[1][1]);
	segment_spinner10->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);
	segment_spinner11 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[2][1]);
	segment_spinner11->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);

	glui2->add_column(false);

	segment_spinner12 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[0][2]);
	segment_spinner12->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);
	segment_spinner13 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[1][2]);
	segment_spinner13->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);
	segment_spinner14 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[2][2]);
	segment_spinner14->set_float_limits(-10.0, 10.0, GLUI_LIMIT_WRAP);

	glui->set_main_gfx_window(windows[MODIFIED]);
	GLUI_Master.set_glutIdleFunc(NULL);
}
