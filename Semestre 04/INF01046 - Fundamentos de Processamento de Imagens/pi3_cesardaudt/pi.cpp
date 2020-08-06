#include "pi.h"

//returns a pointer to the required pixel of array
#define getPix(x, y, c, array, width, height) \
				(array) + (c)*((x)*(width) + (y))
				
#define printImg(c, array, width, height) \
				for(int i=0; i<width; i++) { \
					for(int i=0; i<height; i++) { \
						printf("%i ", *(getPix(i,j,c,array,width,height))); \
					} \
					printf("\n"); \
				} \


int windows[4];

//dimensions of the modified image
unsigned int w; 
unsigned int h;
unsigned int c;

//dimensions of the original image
unsigned int org_w; 
unsigned int org_h;

unsigned int tones = 1;
int bias = -5;
float gain = 1.5;

//zoomOut parameters
unsigned int w_factor = 3;
unsigned int h_factor = 2;

unsigned char *pixels = NULL;
unsigned char *newPixels = NULL;
unsigned char *aux = NULL;

char* fileName;
char newFileName[25];
float histogram[256] = {0};
float eq_histogram[256] = {0};
float kernel[3][3] = {0};

unsigned short int isGray = 0;

IplImage* image = NULL;

void orgReshape(int org_w, int org_h) { 
	glViewport(0, 0, (GLsizei) org_w, (GLsizei) org_h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0.0, org_w, 0.0, org_h); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
}

void modReshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void displayMain() { 
	glClear(GL_COLOR_BUFFER_BIT); 
	glRasterPos2i(0,0); 
	glDrawPixels(org_w, org_h, GL_BGR, GL_UNSIGNED_BYTE, pixels); 
	glutSwapBuffers(); 
}

void displayModified() { 
	glClear(GL_COLOR_BUFFER_BIT); 
	glRasterPos2i(0,0); 
	glDrawPixels(w, h, GL_BGR, GL_UNSIGNED_BYTE, newPixels); 
	glutSwapBuffers(); 
}

//Função callback chamada para fazer o desenho
//void draw(void) {
//	//Limpa a janela de visualização com a cor de fundo especificada 
//	glClear(GL_COLOR_BUFFER_BIT);

//	//Executa os comandos OpenGL 
//	glFlush();
//}

// Inicializa parâmetros de rendering
//void Inicializa (void) {   
//    // Define a cor de fundo da janela de visualização como preta
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//}

void drawLine(float size, float lineNum) {
//	The histogram window is 256x256 resolution
//	OpenGL uses values from -1 to 1 for coordinates variation
//	One given pixel has a value from 0 to w*h (for its frequency in the histogram)
//	So, we have to normalize these values
//	
//	Algorithm:
//		x axis: x = (tone_color/255)*2 - 1 -> this -1 is because of the offset (variation from -1 to 1!)
//		y axis: y = (tone_frequency/w*h)*2 - 1

	glBegin(GL_LINES);
	glColor3f(0,0,1);

	glVertex2f((lineNum/255.0f)*2 - 1.0f, (size/((float)w*(float)h)*255 - 1.0f));	
	glVertex2f((lineNum/255.0f)*2 - 1.0f, -1.0f);	
	
	glEnd();

}

void drawHistogram() {
	unsigned int i;
	
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
			
	for(i=0; i<256; i++) {
		//drawLine(histogram[i], (float)i);
	}
	
	glutSwapBuffers(); 
	glutPostRedisplay();
}

void drawEqHistogram() {
	unsigned int i;
	
	if(glutGetWindow() != windows[EQ_HISTOGRAM]) {
		glutSetWindow(windows[EQ_HISTOGRAM]);
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
			
	for(i=0; i<256; i++) {
		drawLine(eq_histogram[i], (float)i);
	}
	
	glutSwapBuffers(); 
	glutPostRedisplay();
}

void quantizeGray() {
	unsigned int i;
	unsigned int j;
	
	aux = (unsigned char*) malloc(w*h*sizeof(unsigned char*));
	
	unsigned int size = 256/tones;
	unsigned int mean = (size-1)/2;
	if(aux) {
		for(i=0; i<h; i++) {
			for(j=0; j<w*c; j++) { 
				*(aux+((i*w*c)+j)) = ((*(newPixels+((i*w*c)+j)))/(size))*size+mean;
			}
		}
	}
	
	memcpy(newPixels,aux,w*h*c);
	free(aux);
	glutPostRedisplay();
}

void grayScaleHide() {
	unsigned int i;
	unsigned int j;
	
	aux = (unsigned char*) malloc(w*h*c*sizeof(unsigned char*));
	
	if(aux) {
		for(i=0; i<h; i++) {
			for(j=0; j<w; j++) {
				*(aux+(i*w+j)*c) = 	0.299*(*(newPixels+(i*w+j)*c)+2)+	
									0.587*(*(newPixels+(i*w+j)*c)+1)+	
									0.114*(*(newPixels+(i*w+j)*c));		
				*(aux+(i*w+j)*c+1) = *(aux+(i*w+j)*c);
				*(aux+(i*w+j)*c+2) = *(aux+(i*w+j)*c);
			}
		}
	}
	//aux pointer is freed in equalizeColor
}

void grayScale() {
	unsigned int i;
	unsigned int j;
	
	aux = (unsigned char*) malloc(w*h*c*sizeof(unsigned char*));
	
	if(aux) {
		for(i=0; i<h; i++) {
			for(j=0; j<w; j++) {
				*(aux+(i*w+j)*c) = 	0.299*(*(newPixels+(i*w+j)*c)+2)+	
									0.587*(*(newPixels+(i*w+j)*c)+1)+	
									0.114*(*(newPixels+(i*w+j)*c));		
				*(aux+(i*w+j)*c+1) = *(aux+(i*w+j)*c);
				*(aux+(i*w+j)*c+2) = *(aux+(i*w+j)*c);
			}
		}
	}
	
	memcpy(newPixels,aux,w*h*c);
	free(aux);
	isGray = 1;
	glutPostRedisplay();
}

void horMirror() {
	unsigned int i;
	unsigned int j;
	
	aux = (unsigned char*) malloc(w*h*c*sizeof(unsigned char));
	
	if(aux) {
		for(i=0; i<h; i++) {
			for(j=0; j<w; j++) {
				memcpy(aux+(i*w+j)*c,newPixels+((i*w)+(w-1-j))*c, c);
			}
		}
	}
	
	memcpy(newPixels,aux,w*h*c);
	free(aux);
	glutPostRedisplay();
}

void verMirror() {
	unsigned int i;
	
	aux = (unsigned char*) malloc(w*h*c*sizeof(unsigned char));
	
	if(aux) {
		for(i=0; i<h; i++) 
			memcpy(aux+(i*w*c), newPixels+((h-1)*w*c)-(i*w*c), w*c);
	}
	
	memcpy(newPixels,aux,w*h*c);
	free(aux);
	glutPostRedisplay();
}

void brightAdjust() {
	unsigned int i;
	unsigned int j;
	unsigned int k;
	
	//contains the sums of a pixel (or channel) value and the bias parameter
	int sum;
	
	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			for(k=0; k<c; k++) {
				sum = *(newPixels+(i*w+j)*c+k)+bias;
				if(sum < 256 && sum >= 0) {
					*(newPixels+(i*w+j)*c+k) = sum;				
				}
				else {
					//if the sums is grater than 255 or less than zero, we have to saturate it
					if (sum > 255) {
						*(newPixels+(i*w+j)*c+k) = 255;	
					}
					else {
						*(newPixels+(i*w+j)*c+k) = 0;
					}
				}
			}
		}
	}	

	glutPostRedisplay();
}

void contrastAdjust() {
	unsigned int i;
	unsigned int j;
	unsigned int k;
	
	//contains the product of a pixel (or channel) value and the gain parameter
	unsigned int prod;

	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			for(k=0; k<c; k++) {
				prod = *(newPixels+(i*w+j)*c+k)*gain;
				printf("org: %d\n", *(newPixels+(i*w+j)*c+k));
				printf("mult: %d\n", prod);
				
				if(prod < 256) {
					*(newPixels+(i*w+j)*c+k) = prod;				
				}
				else {
					//if the sums is grater than 255, we have to saturate it
					*(newPixels+(i*w+j)*c+k) = 255;
				}
				printf("%d,%d,%d: %d\n\n", i, j, k, *(newPixels+(i*w+j)*c+k));
			}
		}
	}	
	
	glutPostRedisplay();
}

void negative() {
	unsigned int i;
	unsigned int j;
	unsigned int k;

	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			for(k=0; k<c; k++) {
				*(newPixels+(i*w+j)*c+k) = 255 - *(newPixels+(i*w+j)*c+k);
			}			
		}
	}	
	
	glutPostRedisplay();
}

//clears the histogram array to perform the histogram calculus
void clearHistogram() {
	unsigned short int i = 0;
	
	for(i=0; i<256; i++) {
		histogram[i] = 0;	
	}

}

//Function used to calculate the histogram of a coloured image, without showing the grayscale version of it
void calcHistogramHide() {
	unsigned int i;
	unsigned int j;
	
	clearHistogram();
	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			histogram[*(aux+(i*w+j)*c)] += 1;
		}
	}
	glutPostRedisplay();
	drawHistogram();

}

void calcHistogram() {
	unsigned int i;
	unsigned int j;
	
	if(!isGray) {
		grayScale();	
	}
	
	clearHistogram();
	for(i=0; i<h; i++) {


		for(j=0; j<w; j++) {
			histogram[*(newPixels+(i*w+j)*c)] += 1;
		}





	}
	glutPostRedisplay();
	drawHistogram();
}

void equalizeColor() {
	grayScaleHide();
	calcHistogramHide();
	free(aux);
}

void equalizeHistogram() {
	unsigned int i;
	unsigned int j;
	unsigned int k;
	
	float alfa = 255.0/((float)w*(float)h);
	
	if (!isGray) {
		equalizeColor();	
	}
	
	eq_histogram[0] = alfa * histogram[0];

	for(i=1; i<256; i++){
		eq_histogram[i] = eq_histogram[i-1] + alfa*histogram[i];
	}
	
	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			for(k=0; k<c; k++) {
				*(newPixels+(i*w+j)*c+k) = eq_histogram[*(newPixels+(i*w+j)*c+k)];
			}
		}
	}
	glutPostRedisplay();
	drawEqHistogram();
}

void rotateRight() {

	unsigned int i;

	unsigned int j;
	unsigned int dummy;
	
		
	aux = (unsigned char*) malloc(w*h*c*sizeof(unsigned char));
	memcpy(aux, newPixels,(w*h*c*sizeof(unsigned char)));
	
	//for all the lines of the image
	for(i=0; i<h; i++) {		
		for(j=0; j<w; j++) {
			memcpy(getPix(w-j-1,i,c,newPixels,h,w), getPix(i,j,c,aux,w,h), c*sizeof(unsigned char));
		}
	}
	
	//We've got to refresh the image resolution
	dummy = w;
	w = h;
	h = dummy;
	
	//redefine the size of the modified image window
	glutReshapeWindow(w, h);	
	glutPostRedisplay();

	free(aux);
}

void rotateLeft() {
	rotateRight();
	horMirror();
	verMirror();

}

void saveFile() {
	verMirror();
	//OpenCV uses the BGR sequence to represent the image
	//GLUT uses RGB
	//so, we need to convert it
	//cvCvtColor(image, image, CV_RGB2BGR);
	memcpy(image->imageData, (char*)pixels, w*h*c*sizeof(unsigned char*));
	cvSaveImage(newFileName, image);
	verMirror();
	//cvCvtColor(image, image, CV_BGR2RGB);
	glutPostRedisplay();

}

void loadFile(char* file_name) {
	image = cvLoadImage(file_name);
	
	//OpenCV uses the BGR sequence to represent the image
	//GLUT uses RGB
	//so, we need to convert it
	//cvCvtColor(*image, *image, CV_BGR2RGB);
	
	//width
	w = org_w = image->width;
	//height
	h = org_h = image->height;
	//#channels
	c = image->nChannels;
	
	pixels = (unsigned char*)malloc(org_w*org_h*c*sizeof(unsigned char*));
	newPixels = (unsigned char*)malloc(w*h*c*sizeof(unsigned char*));
	//the field imageData of the IplImg struct contains the image pixels in a char pointer
	memcpy(newPixels,(unsigned char*) image->imageData, w*h*c);
	
}

void reloadFile() {

//FIXME: Sometimes it's necessary to reload the image 2 times. Why?
//		 Does not work after using zoomOut
for(unsigned short int i=0; i<2; i++) {
	memcpy(newPixels,(unsigned char*) image->imageData, w*h*c);
	verMirror();
	
	isGray = 0;

//	//width
	w = org_w;
//	//height
	h = org_h;
//	//#channels
	c = image->nChannels;
	
//	memcpy(pixels, newPixels, w*h*c*sizeof(unsigned char));
	
	glutReshapeWindow(w, h);
	
	glutPostRedisplay();
}
}

int meanZoomOut(int i, int j, int ch) {
	
	unsigned int x;
	unsigned int y;
	unsigned int mean = 0;
	unsigned int values = 0;
	
	for(x=0; x<h_factor; x++) {
		for(y=0; y<w_factor; y++) {
			//we should test if the image indexes are not out of bounds
			if((i*h_factor+x<h)&&(j*w_factor+y<w)) {
				mean += *(getPix(i*h_factor+x, j*w_factor+y, c, newPixels, w, h)+ch);
				values++;
			}
		}
	}
	return mean/values;
}

void zoomOut() {

	unsigned int i;
	unsigned int j;
	unsigned short int k;
	
	unsigned int _new_w = (w/w_factor + (w%w_factor ? 1 : 0));
	unsigned int _new_h = (h/h_factor + (h%h_factor ? 1 : 0));
	
	
	aux = (unsigned char*) malloc (_new_w * _new_h * c * sizeof(unsigned char));
	
	for(i=0; i<_new_h; i++) {
		for(j=0; j<_new_w; j++) {
			for(k=0; k<c; k++) {
				*(getPix(i, j, c, aux, _new_w, _new_h)+k) = (unsigned char)meanZoomOut(i,j,k);
			}
		}
	}	
	
	free(newPixels);
	newPixels = (unsigned char*) malloc (_new_w * _new_h * c * sizeof(unsigned char));
	memcpy(newPixels, aux, _new_w * _new_h * c * sizeof(unsigned char));
	free(aux);
	
	h = _new_h;
	w = _new_w;
	
	glutReshapeWindow(w, h);	
	glutPostRedisplay();
}


void zoomIn() {

	unsigned int i;
	unsigned int j;
	unsigned short int k;

	unsigned int _new_w = w+w-1;
	unsigned int _new_h = h+h-1;	

	aux = (unsigned char*) malloc(_new_w * _new_h * c * sizeof(unsigned char));

	//now we copy the image to the bigger array
	//Later, we interpolate the values to have the zoom in image

	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			memcpy(getPix(2*i, 2*j, c, aux, _new_w, _new_h), getPix(i, j, c, newPixels, w, h), c);
		}
	}

	//first, we interpolate through the lines 	-> just the even ones
	//											-> just the blank pixels: the odd ones
	for(i=0; i<_new_h; i+=2) {
		for(j=1; j<_new_w; j+=2) {
			for(k=0; k<c; k++) {
				*(getPix(i, j, c, aux, _new_w, _new_h)+k) = 0.5 * ( *(getPix(i, j+1, c, aux, _new_w, _new_h)+k) +
															 	 	*(getPix(i, j-1, c, aux, _new_w, _new_h)+k) );
			}
		}
	}
	
	//then, we interpolate through the columns 	->just in the odd lines
	for(i=1; i<_new_h; i+=2) {
		for(j=0; j<_new_w; j++) {
			for(k=0; k<c; k++){
				*(getPix(i, j, c, aux, _new_w, _new_h)+k) = 0.5 * ( *(getPix(i-1, j, c, aux, _new_w, _new_h)+k) +
															 	 	*(getPix(i+1, j, c, aux, _new_w, _new_h)+k) );
			}		
		}
	}

	free(newPixels);
	newPixels = (unsigned char*) malloc (_new_w * _new_h * c * sizeof(unsigned char));
	memcpy(newPixels, aux, _new_w * _new_h * c * sizeof(unsigned char));
	free(aux);
	
	h = _new_h;
	w = _new_w;
	
	glutReshapeWindow(w, h);	
	glutPostRedisplay();
}

float retConv(int i, int j, int ch) {
	
	short int x;
	short int y;
	
	float accum = 0;
	
	for(x=-1; x<2; x++) {
		for(y=-1; y<2; y++){
			//if the index is out of the image bounds, we use zero
			if(	0 < (x+i) && (x+i) < h &&
				0 < (y+j) && (y+j) < w ) {
					accum += kernel[1-x][1-y] * (float) *(getPix(i+x, j+y, c, newPixels, w, h)+ch);				
				}
		}
	}
	
	
	//we should test if the value of accum can be stored in an unsigned char
	if(accum < 0) {
		return 0.0;
	}
	else if(accum > 255) {
		return 255.0;	
	}
	else {
		return accum;
	}
}


void convolution() { 

	unsigned int i;
	unsigned int j;
	unsigned short int k;
	
	aux = (unsigned char*) malloc(w*h*sizeof(unsigned char*));
		
	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			for(k=0; k<c; k++) {
				*(getPix(i, j, c, aux, w, h)+k) = (unsigned char)retConv(i, j, k);
			}
		}
	}
	
	memcpy(newPixels, aux, w*h*sizeof(unsigned char*));
	free(aux);
	glutPostRedisplay();
}

void setGlut() {
	//intialize GLUT in the default way
	//aux and aux2 are passed to glutInit to make it initialize glut in default way
	char *aux = "";
	int aux2 = 1;
	glutInit(&aux2, &aux);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(0, 0); 
	glutInitWindowSize(w,h); 
	windows[MAIN] = glutCreateWindow("PI - Original"); 
	glutDisplayFunc(displayMain); 
	glutReshapeFunc(orgReshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(w, 0); 
	glutInitWindowSize(w,h); 
	windows[MODIFIED] = glutCreateWindow("PI - Modified"); 
	glutDisplayFunc(displayModified); 
	glutReshapeFunc(modReshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(0, h); 
	glutInitWindowSize(256,256); 
	windows[HISTOGRAM] = glutCreateWindow("Histogram"); 
	glutDisplayFunc(drawHistogram); 
	glutReshapeFunc(orgReshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	glutHideWindow();
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(256, h); 
	glutInitWindowSize(256,256); 
	windows[EQ_HISTOGRAM] = glutCreateWindow("Equalized Histogram"); 
	glutDisplayFunc(drawEqHistogram); 
	glutReshapeFunc(orgReshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	glutHideWindow();
		
	//glutSetWindow(windows[MODIFIED]);
}

void setGlui() {
	GLUI *glui = GLUI_Master.create_glui ("OPTIONS", 0, 2*w, 0);

	GLUI_Panel *obj_panel = glui->add_panel ("File");			
	GLUI_EditText *edittext = glui->add_edittext_to_panel(obj_panel, "Modified image name:", GLUI_EDITTEXT_TEXT, newFileName);
	glui->add_button_to_panel(obj_panel, "Save!", -1, (GLUI_Update_CB)saveFile);
	glui->add_button_to_panel(obj_panel, "Reload Original Image", -1, (GLUI_Update_CB)reloadFile);

	glui->add_separator();

	GLUI_Panel *obj_panel2 = glui->add_panel ("Flip");
	glui->add_button_to_panel(obj_panel2, "Hozirontal", -1, (GLUI_Update_CB)horMirror);
	glui->add_button_to_panel(obj_panel2, "Vertical", NULL, (GLUI_Update_CB)verMirror);

	glui->add_button_to_panel(obj_panel2, "90 degrees left", NULL, (GLUI_Update_CB)rotateLeft);
	glui->add_button_to_panel(obj_panel2, "90 degrees right", NULL, (GLUI_Update_CB)rotateRight);
	
	glui->add_column(true);
		
	GLUI_Panel *obj_panel3 = glui->add_panel ("Histogram");
	glui->add_button_to_panel(obj_panel3, "Calculate", NULL, (GLUI_Update_CB)calcHistogram);
	glui->add_button_to_panel(obj_panel3, "Equalize", NULL, (GLUI_Update_CB)equalizeHistogram);

	glui->add_separator();
	
	GLUI_Panel *obj_panel4 = glui->add_panel ("Color");
	GLUI_Spinner *segment_spinner = glui->add_spinner_to_panel(obj_panel4, "Quantization - # of colors:", GLUI_SPINNER_INT, &tones);
	segment_spinner->set_int_limits(1, 256, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel4, "Quantize!", NULL, (GLUI_Update_CB)quantizeGray);
	glui->add_button_to_panel(obj_panel4, "Gray Scale", NULL, (GLUI_Update_CB)grayScale);
	glui->add_button_to_panel(obj_panel4, "Negative", NULL, (GLUI_Update_CB)negative);
	
	glui->add_separator();
	
	glui->add_button("Convolution !", NULL, (GLUI_Update_CB)convolution);

	glui->add_column(true);
	
	GLUI_Panel *obj_panel5 = glui->add_panel ("Adjusts");
	GLUI_Spinner *segment_spinner2 = glui->add_spinner_to_panel(obj_panel5, "Bias (bright):", GLUI_SPINNER_INT, &bias);
	segment_spinner2->set_int_limits(-255, 255, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel5, "Bright !", NULL, (GLUI_Update_CB)brightAdjust);
	GLUI_Spinner *segment_spinner3 = glui->add_spinner_to_panel(obj_panel5, "Gain (contrast):", GLUI_SPINNER_FLOAT, &gain);
	segment_spinner3->set_float_limits(0, 2000, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel5, "Contrast !", NULL, (GLUI_Update_CB)contrastAdjust);
	
	glui->add_separator();

	GLUI_Panel *obj_panel6 = glui->add_panel ("Zoom");
	glui->add_button_to_panel(obj_panel6, "Zoom in 2x2", NULL, (GLUI_Update_CB)zoomIn);
	GLUI_Spinner *segment_spinner4 = glui->add_spinner_to_panel(obj_panel6, "Width factor:", GLUI_SPINNER_INT, &w_factor);
	segment_spinner4->set_int_limits(1, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner5 = glui->add_spinner_to_panel(obj_panel6, "Height factor:", GLUI_SPINNER_INT, &h_factor);
	segment_spinner4->set_int_limits(1, 2000, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel6, "Zoom Out !", NULL, (GLUI_Update_CB)zoomOut);

	
	GLUI *glui2 = GLUI_Master.create_glui ("Convolution Kernel", 0, 2*w, 0);
	
	GLUI_Spinner *segment_spinner6 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[0][0]);
	segment_spinner4->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner7 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[1][0]);
	segment_spinner5->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner8 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[2][0]);
	segment_spinner5->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);

	glui2->add_column(false);
	
	GLUI_Spinner *segment_spinner9 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[0][1]);
	segment_spinner4->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner10 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[1][1]);
	segment_spinner5->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner11 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[2][1]);
	segment_spinner5->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);

	glui2->add_column(false);

	GLUI_Spinner *segment_spinner12 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[0][2]);
	segment_spinner4->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner13 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[1][2]);
	segment_spinner5->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);
	GLUI_Spinner *segment_spinner14 = glui2->add_spinner("", GLUI_SPINNER_FLOAT, &kernel[2][2]);
	segment_spinner5->set_float_limits(-2000, 2000, GLUI_LIMIT_WRAP);
		
	glui->set_main_gfx_window(windows[MODIFIED]);
	GLUI_Master.set_glutIdleFunc (NULL);
}
