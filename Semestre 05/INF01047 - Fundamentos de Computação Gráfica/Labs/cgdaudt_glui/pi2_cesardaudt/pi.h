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

//int windows[4];
	
//int w; 
//int h;
//int c;

//unsigned int tones = 1;
// int bias = 0;
//float gain = 1;

//unsigned char *pixels;
//unsigned char *newPixels;
//unsigned char *aux;

//char newFileName[25];
//unsigned char histogram[256] = {0};
//float eq_histogram[256] = {0};

//unsigned short int isGray = 0;

//IplImage* image;

//Reshape function
void reshape(int w, int h);

//Display function for main Image
void displayMain();

//Display function for modified Image
void displayModified();

//
//void draw(void);

//
//void Inicializa (void);

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

//Calculates the image histogram and shows the grayscale version of the image, if it was coloured.
void calcHistogram();

//Equalizes the histogram of a coloured image
void equalizeColor();

//Calculates the image equalized histogram 
void equalizeHistogram();

//save a .jpg image
void saveFile();

unsigned char* loadFile(char* file_name, IplImage** image);

//Sets Glut's parameters
void setGlut();

//Sets Glui's parameters
void setGlui();


#endif
