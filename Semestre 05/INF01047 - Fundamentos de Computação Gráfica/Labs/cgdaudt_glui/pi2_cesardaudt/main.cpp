#include <stdio.h>
#include <stdlib.h>
#include "pi.h"

extern int windows[2];
	
extern int w; 
extern int h;
extern int c;

extern unsigned int tones;
extern int bias;
extern float gain;

extern unsigned char *pixels;
extern unsigned char *newPixels;
extern unsigned char *aux;

extern char newFileName[25];
extern float histogram[256];
extern float eq_histogram[256];

extern unsigned short int isGray;

extern IplImage* image;

int main(int argc, char *argv[]) {

	if(argv[1] && argv[2]) {
		
		newPixels = NULL;
		newPixels = loadFile(argv[1], &image);		
		
		//TO-DO: How to discover that the image was not loaded???
		if(newPixels) {
			setGlut();
			setGlui();
			
			//if this is not done, the image is not going to be drawn correctly
			verMirror();
			
			pixels = (unsigned char*)malloc(w*h*c*sizeof(unsigned char*));
			
			//the mirror effects are available just for the modified image (newPixels)
			//after this, pixels contains the correct original image to draw
			memcpy(pixels, newPixels, w*h*c);
			
			//newFileName contains the name of the file to be saved after modifications		
			memcpy(newFileName, argv[2], sizeof(argv[2]));
			
			glutMainLoop(); 
	
			free(pixels);
			free(newPixels);
		}
		else {
			printf("You shold type the name of a valid file\n");
		}
	}

	else {
		printf("You should type:\n");
		printf("pi.exe <image_to_open>.jpg <image_to_save>.jpg\n");
		printf("Press Enter...");
		getchar();
	}
	
	return 0;
}
