#include "pi.h"

int windows[4];
	
unsigned int w; 
unsigned int h;
unsigned int c;

unsigned int tones = 1;
int bias = -5;
float gain = 1.5;

unsigned char *pixels;
unsigned char *newPixels;
unsigned char *aux;

char newFileName[25];
float histogram[256] = {0};
float eq_histogram[256] = {0};

unsigned short int isGray = 0;

IplImage* image;

void reshape(int w, int h) { 
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0.0, w, 0.0, h); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
}

void displayMain() { 
	glClear(GL_COLOR_BUFFER_BIT); 
	glRasterPos2i(0, 0); 
	glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels); 
	glutSwapBuffers(); 
}

void displayModified() { 
	glClear(GL_COLOR_BUFFER_BIT); 
	glRasterPos2i(0, 0); 
	glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, newPixels); 
	glutSwapBuffers(); 
}

//Função callback chamada para fazer o desenho
//void draw(void) {
//	//Limpa a janela de visualização com a cor de fundo especificada 
//	glClear(GL_COLOR_BUFFER_BIT);

//	//Executa os comandos OpenGL 
//	glFlush();
//}

//// Inicializa parâmetros de rendering
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
		drawLine(histogram[i], (float)i);
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
				*(aux+(i*w+j)*c) = 	0.299*(*(newPixels+(i*w+j)*c))+	
									0.587*(*(newPixels+(i*w+j)*c)+2)+	
									0.114*(*(newPixels+(i*w+j)*c)+3);		
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
				*(aux+(i*w+j)*c) = 	0.299*(*(newPixels+(i*w+j)*c))+	
									0.587*(*(newPixels+(i*w+j)*c)+2)+	
									0.114*(*(newPixels+(i*w+j)*c)+3);		
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
				if(prod < 256) {
					*(newPixels+(i*w+j)*c+k) = prod;				
				}
				else {
					//if the sums is grater than 255, we have to saturate it
					*(newPixels+(i*w+j)*c+k) = 255;
				}
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

void saveFile() {
	verMirror();
	//OpenCV uses the BGR sequence to represent the image
	//GLUT uses RGB
	//so, we need to convert it
	cvCvtColor(image, image, CV_RGB2BGR);
	cvSaveImage(newFileName, image);
	verMirror();
	cvCvtColor(image, image, CV_BGR2RGB);
	glutPostRedisplay();

}

unsigned char* loadFile(char* file_name, IplImage** image) {
	*image = NULL;
	*image = cvLoadImage(file_name);
	
	//OpenCV uses the BGR sequence to represent the image
	//GLUT uses RGB
	//so, we need to convert it
	cvCvtColor(*image, *image, CV_BGR2RGB);
	
	//width
	w = (*image)->width;
	//height
	h = (*image)->height;
	//#channels
	c = (*image)->nChannels;
	
	//the field imageData of the IplImg struct contains the image pixels in an unsigned char pointer
	return (unsigned char*)(*image)->imageData;
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
	glutReshapeFunc(reshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(w, 0); 
	glutInitWindowSize(w,h); 
	windows[MODIFIED] = glutCreateWindow("PI - Modified"); 
	glutDisplayFunc(displayModified); 
	glutReshapeFunc(reshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(0, h); 
	glutInitWindowSize(256,256); 
	windows[HISTOGRAM] = glutCreateWindow("Histogram"); 
	glutDisplayFunc(drawHistogram); 
	glutReshapeFunc(reshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	glutHideWindow();
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowPosition(256, h); 
	glutInitWindowSize(256,256); 
	windows[EQ_HISTOGRAM] = glutCreateWindow("Equalized Histogram"); 
	glutDisplayFunc(drawEqHistogram); 
	glutReshapeFunc(reshape); 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	glClearColor(0.0, 0.0, 0.0, 0);
	glutHideWindow();
		
	//glutSetWindow(windows[MODIFIED]);
}

void setGlui() {
	GLUI *glui = GLUI_Master.create_glui ("OPTIONS", 0, 2*w, 0);
	
	GLUI_Panel *obj_panel = glui->add_panel ("Mirror effect");
	glui->add_button_to_panel(obj_panel, "Hozirontal", NULL, (GLUI_Update_CB)horMirror);
	glui->add_button_to_panel(obj_panel, "Vertical", NULL, (GLUI_Update_CB)verMirror);
	
	glui->add_separator();
	
	GLUI_Panel *obj_panel2 = glui->add_panel ("");
	glui->add_button_to_panel(obj_panel2, "Gray Scale", NULL, (GLUI_Update_CB)grayScale);
	glui->add_button_to_panel(obj_panel2, "Negative", NULL, (GLUI_Update_CB)negative);

	glui->add_separator();
	
	GLUI_Panel *obj_panel3 = glui->add_panel("Image Quantization");
	GLUI_Spinner *segment_spinner = glui->add_spinner_to_panel(obj_panel3, "# of colors:", GLUI_SPINNER_INT, &tones);
	segment_spinner->set_int_limits(1, 256, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel3, "Quantize!", NULL, (GLUI_Update_CB)quantizeGray);
	
	glui->add_separator();
	
	GLUI_Panel *obj_panel4 = glui->add_panel("Save File");
	//glui->add_edittext_to_panel(obj_panel4, "File name (20 characters):", GLUI_EDITTEXT_TEXT, newFileName);
	glui->add_button_to_panel(obj_panel4, "Save !", NULL, (GLUI_Update_CB)saveFile);
	
	glui->add_separator();
	
	GLUI_Panel *obj_panel5 = glui->add_panel ("Adjusts");
	GLUI_Spinner *segment_spinner2 = glui->add_spinner_to_panel(obj_panel5, "Bias (bright):", GLUI_SPINNER_INT, &bias);
	segment_spinner2->set_int_limits(-255, 255, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel5, "Bright !", NULL, (GLUI_Update_CB)brightAdjust);
	glui->add_separator();
	GLUI_Spinner *segment_spinner3 = glui->add_spinner_to_panel(obj_panel5, "Gain (contrast):", GLUI_SPINNER_FLOAT, &gain);
	//segment_spinner3->set_float_limits(-255, 255, GLUI_LIMIT_WRAP);
	glui->add_button_to_panel(obj_panel5, "Contrast !", NULL, (GLUI_Update_CB)contrastAdjust);
	
	GLUI_Panel *obj_panel6 = glui->add_panel ("Histogram");
	glui->add_button_to_panel(obj_panel6, "Calculate", NULL, (GLUI_Update_CB)calcHistogram);
	glui->add_button_to_panel(obj_panel6, "Equalize", NULL, (GLUI_Update_CB)equalizeHistogram);
	
	glui->set_main_gfx_window(windows[MODIFIED]);
	GLUI_Master.set_glutIdleFunc (NULL);
}
