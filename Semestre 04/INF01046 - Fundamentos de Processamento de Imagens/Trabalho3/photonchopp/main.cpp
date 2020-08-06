#include <stdio.h>
#include <stdlib.h>
#include "photonchopp.h"

/* Terminal: photonchopp <img_open.jpg> */


/* Global variables */
extern int width, height, channel;

extern unsigned char *org_pixels, *mod_pixels, *aux_pixels;
extern char *org_filename;
extern IplImage *img;


int main( int argc, char *argv[] ) {

	if( argv[1] ) {

		initPhotonChopp( argv[1] );

		glutMainLoop();
	
		free(org_pixels);
		free(mod_pixels);
	}
	else {
		fprintf( stderr, "Must have 1 arguments.\n" );
		exit(1);
	}
	
	return 0;
}

