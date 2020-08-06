#include <stdio.h>
#include <stdlib.h>
#include "pi.h"

extern int windows[4];

//dimensions of the modified image
extern unsigned int w; 
extern unsigned int h;
extern unsigned int c;

//dimensions of the original image
extern unsigned int org_w; 
extern unsigned int org_h;

extern unsigned int tones;
extern int bias;
extern float gain;

//zoomOut parameters
extern unsigned int w_factor;
extern unsigned int h_factor;

extern unsigned char *pixels;
extern unsigned char *newPixels;
extern unsigned char *aux;

extern char* fileName;
extern char newFileName[25];
extern float histogram[256];
extern float eq_histogram[256];
extern float kernel[3][3];

extern unsigned short int isGray;

extern IplImage* image;


int main(int argc, char *argv[]) {

	//To open PI, user should type > PI <image_name.jpg>
	if(argv[1]) {

		//fileName = strdup(argv[1]);
		
		loadFile(argv[1]);

		printf("%i x %i, #c:%i\n", w, h, c);
		
		setGlut();
		setGlui();	
					
		verMirror();
		memcpy(pixels, newPixels, org_w*org_h*c*sizeof(unsigned char));
		
		glutMainLoop(); 

		free(pixels);
		free(newPixels);

	}

//	else {
//		printf("You should type:\n");
//		printf("pi.exe <image_to_open>.jpg <image_to_save>.jpg\n");
//		printf("Press Enter...");
//		getchar();
//	}
	
	return 0;
}
