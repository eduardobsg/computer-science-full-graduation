#ifndef __PI_H
#define __PI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

// -----------------------------------------------------------------------------
// Auxiliar functions
// -----------------------------------------------------------------------------

/* Given some parameters, returns a pointer to a pixel  */
unsigned char * getPixel( int x, int y, int channel, unsigned char * imageArray, int width );

/* Draws a line of the histogram in a window of 256x256 resolution */
void drawLine(float quant, float lineNum);

/* Helps to make Zoom Out. It takes a group of pixels and select one of then */
int meanZoomOut(int i, int j, int ch);

/* Does the convolution in one pixel */
float returnConvolution(int i, int j, int ch);
	
/* Sets the GLUI Kernel */
void setGLUIKernel();

/* Filters */
void Gaussian();
void Laplacian();
void HighPass();
void PrewittX();
void PrewittY();
void SobelX();
void SobelY();

// -----------------------------------------------------------------------------
// Image manipulation functions
// -----------------------------------------------------------------------------

/* Load an image */
unsigned char* loadImage( char* filename, IplImage** img );

/* Show an image */
void showImage( IplImage* img );

/* Save an image */
void saveImage();

/* Realods the modified image */
void reloadImage();

/* Makes a series of initializations */
void initPhotonChopp( char *filename );

/* Executes an image horizontal flip */
void horizontalFlip();

/* Executes an image vertical flip */
void verticalFlip();

/* Executes 90 degree rotation left */
void rotateLeft(); 

/* Executes 90 degree rotation right */
void rotateRight();

/* Converts the image to gray scale - Luminancy */
void grayScale();

/* Quantize the number of tones of gray */
void quantizeGray();

/* Converts the modified image to monochrome (black & white) */
void monochrome();

/* Converts the modified image to its negative */
void negative();

/* Applies bright ajust to the modified image window */
void bright();

/* Applies contrast ajust to the modified image window */
void contrast();

/* Calculates the histogram and normalizes it */
void calcHistogram();

/* Calculates the histogram and normalizes it */
void calcEqualizedHistogram();

/* Makes Zoom in on the image (2 x 2) */
void zoomIn();

/* Makes Zoom out on the image (n x m) */
void zoomOut();

/* Applies convolution on an image */
void convolution();

// -----------------------------------------------------------------------------
// GUI & GLUT functions
// -----------------------------------------------------------------------------

/* callback function - reshapes window size */
void originalReshape(int width, int height);
void modifiedReshape(int width, int height);

/* callback function - draws image on the window */
void originalDisplay();
void modifiedDisplay();
void histogramDisplay();
void equalizedHistogramDisplay();

/* Sets GLUT's parameters */
void setGlut();

/* Sets GLUI's parameters */
void setGlui();

#endif
