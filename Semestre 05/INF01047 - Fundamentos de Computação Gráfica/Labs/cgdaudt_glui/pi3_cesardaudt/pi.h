#ifndef __PI_H
#define __PI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define MAIN 			0
#define MODIFIED 		1
#define HISTOGRAM 		2
#define EQ_HISTOGRAM	3

//These globals are defined to work easier with GLUT and GLUI functions
//You can find them in the pi.cpp file
//To use them in your files, don't forget to "redeclare" them as extern variables

#include "pi.h"

//returns a pointer to the required pixel of array
//#define getPix(x, y, c, array, width, height)

//prints the pixels of the image (just 1 channel)				
//#define printImg(c, array, width, height)


//int windows[4];

////dimensions of the modified image
//unsigned int w; 
//unsigned int h;
//unsigned int c;

////dimensions of the original image
//unsigned int org_w; 
//unsigned int org_h;

//unsigned int tones = 1;
//int bias = -5;
//float gain = 1.5;

////zoomOut parameters
//unsigned int w_factor = 3;
//unsigned int h_factor = 2;

//unsigned char *pixels = NULL;
//unsigned char *newPixels = NULL;
//unsigned char *aux = NULL;

//char* fileName;
//char newFileName[25];
//float histogram[256] = {0};
//float eq_histogram[256] = {0};
//float kernel[3][3] = {0};

//unsigned short int isGray = 0;

//IplImage* image = NULL;


//Reshape functions
void orgReshape(int org_w, int org_h);

void modReshape(int w, int h);

//Display function for main Image
void displayMain();

//Display function for modified Image
void displayModified();

/*Not used functions
//void draw(void);

//void Inicializa (void);
*/

//Draw a line in the histogram window
void drawLine(int size, int lineNum);

//Draw the image histogram
void drawHistogram();

//Draw the image equalized histogram
void drawEqHistogram();

//Quantize a gray scale image to "tones" colors
void quantizeGray();

//Function used to equalize the histogram of a coloured image
void grayScaleHide();

//Converts an image to gray scale
void grayScale();

//Mirror effect, considering an vertical axis
void horMirror();

//Mirror effect, considering an horizontal axis
void verMirror();

//Adjusts the image bright
void brightAdjust();

//Adjusts the image contrast
void contrastAdjust();

//Calculates the image negative
void negative();

//clears the histogram array to perform the histogram calculus
void clearHistogram();

//Function used to calculate the histogram of a coloured image, without showing the grayscale version of it
void calcHistogramHide();

//Calculates the image histogram and shows the grayscale version of the image, if it was coloured.
void calcHistogram();

//Equalizes the histogram of a coloured image
void equalizeColor();

//Calculates the image equalized histogram 
void equalizeHistogram();

//Clockwise rotating
void rotateRight();

//Analogous with the above function
void rotateLeft();

//saves a .jpg image
void saveFile();

//Loads a .jpg image
void loadFile(char* file_namec);

//Reloads a .jpg image.
void reloadFile();

//Aux function to calc. the Zoom out operation
int meanZoomOut(int i, int j, int ch);

//Given two factors, makes the image smaller
void zoomOut();

//Makes the image 2 times wider and larger
void zoomIn();

//Aux function to the Convolution procedure
float retConv(int i, int j, int ch);

//Given a kernel, does a convolution in the image
void convolution();

//Sets Glut's parameters
void setGlut();

//Sets Glui's parameters
void setGlui();

#endif
