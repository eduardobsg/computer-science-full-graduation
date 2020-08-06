// Gustavo Valdez
// João Gaiewski

// TRON - Trabalho Final de FCG

#ifdef _WIN32
#include <windows.h>
#endif

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <vector>
#include "EasyBMP.h"
using namespace std;

// Definições de Ambiente
int kilom_x = 10, kilom_z = 10;
#define FLOOR_SQUARES_X (8 * kilom_x)
#define FLOOR_SQUARES_Z (8 * kilom_z)
#define SQUARE_SIZE 20

#define FLOOR_CENTER_X ((FLOOR_SQUARES_X / 2) * (SQUARE_SIZE))
#define FLOOR_CENTER_Z ((FLOOR_SQUARES_Z / 2) * (SQUARE_SIZE))
#define FLOOR_END_X (FLOOR_SQUARES_X * (SQUARE_SIZE))
#define FLOOR_END_Z (FLOOR_SQUARES_Z * (SQUARE_SIZE))
#define WALL_HEIGHT 80


int num_lasers = 4;

#define NRO_TEXTURES 5
#define TEXTURA_CHAO 0
#define TEXTURA_PAREDE 1
#define TEXTURA_TRAIL 2
#define TEXTURA_FIRE 3
#define TEXTURA_MOTO 4

int num_motos = 1;
int lasers_capturados = 0;

#define MOTO_SPEED 4
#define CIMA 0
#define DIREITA 1
#define BAIXO 2
#define ESQUERDA 3

#define MODO_NORMAL 0
#define MODO_LASER 1
#define MODO_AMBOS 2
int modo_de_jogo = 1;


int WindowWidth = 800;
int WindowHeight = 600;
int SubWindowWidth = 300;
int SubWindowHeight = 300;
int WindowId;
int SubWindowId;
int ia_counter = 0; // Contador de Iterações para decidir quando as IAs devem agir
bool game_end; // Verdadeiro se o jogo acabou, para parar as motos.
vector< vector<int> > Tabela_Jogo; // Tabela com as posições do Jogo
vector<int> IA_Level; // Nível de IA de cada moto
// Gerência das Explosões
vector<int> Explode_x;
vector<int> Explode_y;
vector<int> Explode_progress;
vector<bool> Explode_grow;

typedef struct moto {
        vector<int> curvax;
        vector<int> curvay;
        int vira;
        bool acelera;
        int x;
        int y;
        int direcao;
        int explodiu;
} Moto;

typedef struct laser {
        int x;
        int y;
        bool capturado;
} Laser;

vector< Moto > Motos;
vector< Laser > Lasers;

typedef struct camera {
        GLdouble atx;
        GLdouble aty;
        GLdouble atz;
        GLdouble tox;
        GLdouble toy;
        GLdouble toz;
        GLdouble rotAngle;
} Observador;

Observador CameraPersp;
Observador CameraOrto;

// Parametros de projeção
GLfloat fAspect;
GLfloat angle = 50;    // ângulo de abertura para proj. Perspectiva

// limites do volume ortografico
GLdouble minX=-100.00;
GLdouble maxX=100.00;
GLdouble minY=-100.00;
GLdouble maxY=100.00;
GLint incremento=0;

// planos near e far para recorte em profundidade
GLdouble near_plane= 2.0;
GLdouble far_plane=240.0;

// Luz
    GLfloat mat_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 0.5, 1, 0.7, 0.0 };

//TEXTURAS
GLuint texName[NRO_TEXTURES];
#define    TEXTURA_PAREDE_SIZE 350
#define    TEXTURA_PISO_SIZE 32
#define    TEXTURA_TRAIL_SIZE 128
#define    TEXTURA_FIRE_SIZE 512
#define    TEXTURA_MOTO_SIZE 512
GLubyte TexturaDaParede[TEXTURA_PAREDE_SIZE][TEXTURA_PAREDE_SIZE][3];
GLubyte TexturaDoPiso[TEXTURA_PISO_SIZE][TEXTURA_PISO_SIZE][3];
GLubyte TexturaDoTrail[TEXTURA_TRAIL_SIZE][TEXTURA_TRAIL_SIZE][3];
GLubyte TexturaExplosao[TEXTURA_FIRE_SIZE][TEXTURA_FIRE_SIZE][3];
GLubyte TexturaDaMoto[TEXTURA_MOTO_SIZE][TEXTURA_MOTO_SIZE][3];


void CarregaTexturas(void)
{
    BMP TexturaCarregada;
    // Textura do chão
    TexturaCarregada.ReadFromFile("resources/textures/floor.bmp");
    int i, j;

       for (i = 0; i < TEXTURA_PISO_SIZE; i++) {
        for (j = 0; j < TEXTURA_PISO_SIZE; j++) {
            TexturaDoPiso[i][j][0] = (GLubyte) TexturaCarregada(i,j)->Red;
            TexturaDoPiso[i][j][1] = (GLubyte) TexturaCarregada(i,j)->Green;
            TexturaDoPiso[i][j][2] = (GLubyte) TexturaCarregada(i,j)->Blue;
        }
    }
    // Textura da Parede
    TexturaCarregada.ReadFromFile("resources/textures/parede.bmp");
       for (i = 0; i < TEXTURA_PAREDE_SIZE; i++) {
        for (j = 0; j < TEXTURA_PAREDE_SIZE; j++) {

            TexturaDaParede[i][j][0] = (GLubyte) TexturaCarregada(i,j)->Red;
            TexturaDaParede[i][j][1] = (GLubyte) TexturaCarregada(i,j)->Green;
            TexturaDaParede[i][j][2] = (GLubyte) TexturaCarregada(i,j)->Blue;
        }
    }
    // Textura dos Rastros
    TexturaCarregada.ReadFromFile("resources/textures/trail.bmp");
       for (i = 0; i < TEXTURA_TRAIL_SIZE; i++) {
        for (j = 0; j < TEXTURA_TRAIL_SIZE; j++) {

            TexturaDoTrail[i][j][0] = (GLubyte) TexturaCarregada(i,j)->Red;
            TexturaDoTrail[i][j][1] = (GLubyte) TexturaCarregada(i,j)->Green;
            TexturaDoTrail[i][j][2] = (GLubyte) TexturaCarregada(i,j)->Blue;
        }
    }
    // Textura das Explosões
    TexturaCarregada.ReadFromFile("resources/textures/fire.bmp");
       for (i = 0; i < TEXTURA_FIRE_SIZE; i++) {
        for (j = 0; j < TEXTURA_FIRE_SIZE; j++) {

            TexturaExplosao[i][j][0] = (GLubyte) TexturaCarregada(i,j)->Red;
            TexturaExplosao[i][j][1] = (GLubyte) TexturaCarregada(i,j)->Green;
            TexturaExplosao[i][j][2] = (GLubyte) TexturaCarregada(i,j)->Blue;
        }
    }
    // Textura da Moto
    TexturaCarregada.ReadFromFile("resources/textures/moto.bmp");
       for (i = 0; i < TEXTURA_MOTO_SIZE; i++) {
        for (j = 0; j < TEXTURA_MOTO_SIZE; j++) {

            TexturaDaMoto[i][j][0] = (GLubyte) TexturaCarregada(i,j)->Red;
            TexturaDaMoto[i][j][1] = (GLubyte) TexturaCarregada(i,j)->Green;
            TexturaDaMoto[i][j][2] = (GLubyte) TexturaCarregada(i,j)->Blue;
        }
    }
}

void InicializaTextura()
{
    CarregaTexturas();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
/* I-Especificar matriz ou vetor de (R, G, B, A) cor e transparencia
    a função abaixo configura a textura que, em geral, é uma imagem.
glTexImage2D
(
	target	GL_TEXTURE_2D
	level	0
	components 	1=R, 2=RA, 3=RGB, 4=RGBA
	width	minimo 64
	height	minimo 64
	border	usualmente 0
	format	GL_RGB, GL_COLOR_INDEX, GL_RGBA, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA
	type	GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, GL_BITMAP
	pixels	a textura em si (imagem ou matriz)
 )*/
    glGenTextures(NRO_TEXTURES, texName);
    glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_CHAO]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, TEXTURA_PISO_SIZE,
        TEXTURA_PISO_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE,
        &TexturaDoPiso[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_PAREDE]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, TEXTURA_PAREDE_SIZE,
        TEXTURA_PAREDE_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE,
        &TexturaDaParede[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_TRAIL]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, TEXTURA_TRAIL_SIZE,
        TEXTURA_TRAIL_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE,
        &TexturaDoTrail[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_FIRE]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, TEXTURA_FIRE_SIZE,
        TEXTURA_FIRE_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE,
        &TexturaExplosao[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_MOTO]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, TEXTURA_MOTO_SIZE,
        TEXTURA_MOTO_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE,
        &TexturaDaMoto[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
        GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_TEXTURE_2D);
}

// Inicialização
void SetupRC(void)
{

    // Limpa a janela e habilita o teste para eliminar faces ocultas por outras
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //Configurar Texturas
    InicializaTextura();

    glShadeModel (GL_SMOOTH);


    CameraPersp.atx=70;
    CameraPersp.aty=70;
    CameraPersp.atz=70;

    CameraPersp.tox=0;
    CameraPersp.toy=0.0;
    CameraPersp.toz=0;
    CameraPersp.rotAngle=0.0;

    CameraOrto.atx=FLOOR_CENTER_X;
    CameraOrto.aty=100.0;
    CameraOrto.atz=FLOOR_CENTER_Z;

    CameraOrto.tox=FLOOR_CENTER_X;
    CameraOrto.toy=0.0;
    CameraOrto.toz=FLOOR_CENTER_Z;
    CameraOrto.rotAngle=0.0;

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
}


/* Função usada para especificar o volume de visualizacao
*  para a projecao Perspectiva
*/
void PerspectiveViewing(void)
{
	// Especifica manipulacao da matriz de projecao
	glMatrixMode(GL_PROJECTION);
	// Inicializa matriz com a identidade
	glLoadIdentity();

    // Especifica a projeção Perspectiva
    gluPerspective(angle,fAspect,0.1,5000);
   //  gluPerspective(angle,fAspect,near_plane,far_plane);

    // Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa matriz modelview com a identidade
	glLoadIdentity();
	// Especifica posição do observador e do alvo
	gluLookAt (CameraPersp.atx+Motos[0].x,CameraPersp.aty,CameraPersp.atz+Motos[0].y,CameraPersp.tox+Motos[0].x,CameraPersp.toy,CameraPersp.toz+Motos[0].y, 0,1,0);
    glTranslatef(CameraPersp.tox+Motos[0].x, CameraPersp.toy, CameraPersp.toz+Motos[0].y);
    glRotatef(- CameraPersp.rotAngle, 0, 1, 0);
    glTranslatef(- CameraPersp.tox - Motos[0].x, - CameraPersp.toy, - CameraPersp.toz - Motos[0].y);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

/* Funcao usada para especificar o volume de visualizacao
*  para a projecao Perspectiva
*/
void OrthoViewing(void)
{

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	// Especifica posição do observador e do alvo
	gluLookAt (CameraOrto.atx,CameraOrto.aty,CameraOrto.atz,CameraOrto.tox,CameraOrto.toy,CameraOrto.toz, 1,0,0);

	glMatrixMode(GL_PROJECTION);
	// Inicializa matriz com a identidade
	glLoadIdentity();

    // Especifica a projeção ortográfica

    glOrtho(-(FLOOR_CENTER_X),
            +(FLOOR_CENTER_X),
            -(FLOOR_CENTER_Z),
            +(FLOOR_CENTER_Z),
            0.1,1000);

    glMatrixMode(GL_MODELVIEW);
}
// Chamada pela GLUT quando a janela e redimensionada
void ChangeSize(GLsizei w, GLsizei h)
{
    WindowHeight = h;
    WindowWidth = w;
	if ( h == 0 )
		h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
    glutSetWindow(WindowId);
        PerspectiveViewing();
        glutPostRedisplay();

    glutSetWindow(SubWindowId);
        glutPositionWindow(w - SubWindowWidth, h - SubWindowHeight);
        glutReshapeWindow(SubWindowWidth,SubWindowHeight);
        OrthoViewing();
        glutPostRedisplay();
}
void DesenhaMapa(){
    if (glutGetWindow() ==  WindowId)
        glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_CHAO]);
    glBegin(GL_QUADS);
        glNormal3f(0, 1,0);
        if (glutGetWindow() == SubWindowId)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
        glTexCoord2f(0.0, FLOOR_SQUARES_Z); glVertex3f(0,0,FLOOR_END_Z);
        glTexCoord2f(FLOOR_SQUARES_X, FLOOR_SQUARES_Z); glVertex3f(FLOOR_END_X,0,FLOOR_END_Z);
        glTexCoord2f(FLOOR_SQUARES_X, 0.0); glVertex3f(FLOOR_END_X,0,0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_PAREDE]);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);
        glColor3f(1.0f, 1.0f, 1.0f);
        //Textura da parede (coordenadas variam entre 0 e 1)
        glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
        glTexCoord2f(0.0, FLOOR_END_X/WALL_HEIGHT); glVertex3f(FLOOR_END_X, 0, 0);
        glTexCoord2f(1, FLOOR_END_X/WALL_HEIGHT); glVertex3f(FLOOR_END_X, WALL_HEIGHT, 0);
        glTexCoord2f(1, 0.0); glVertex3f(0, WALL_HEIGHT, 0);
    glEnd();

    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, -1.0);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(1.0, 0.0); glVertex3f(0, WALL_HEIGHT, FLOOR_END_Z);
        glTexCoord2f(1.0, FLOOR_END_X/WALL_HEIGHT); glVertex3f(FLOOR_END_X, WALL_HEIGHT, FLOOR_END_Z);
        glTexCoord2f(0.0, FLOOR_END_X/WALL_HEIGHT); glVertex3f(FLOOR_END_X, 0, FLOOR_END_Z);
        glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, FLOOR_END_Z);
    glEnd();

    glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0, 0.0);
        glColor3f(1.0f, 1.0f, 01.0f);
        glTexCoord2f(1.0, FLOOR_END_Z/WALL_HEIGHT); glVertex3f(0, WALL_HEIGHT ,0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0, WALL_HEIGHT, FLOOR_END_Z);
        glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, FLOOR_END_Z);
        glTexCoord2f(0.0, FLOOR_END_Z/WALL_HEIGHT); glVertex3f(0, 0, 0);
    glEnd();

    glBegin(GL_QUADS);
        glNormal3f(-1.0, 0.0, 0.0);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0, FLOOR_END_Z/WALL_HEIGHT); glVertex3f(FLOOR_END_X, 0, 0);
        glTexCoord2f(0.0, 0.0); glVertex3f(FLOOR_END_X, 0, FLOOR_END_Z);
        glTexCoord2f(1.0, 0.0); glVertex3f(FLOOR_END_X, WALL_HEIGHT, FLOOR_END_Z);
        glTexCoord2f(1.0, FLOOR_END_Z/WALL_HEIGHT); glVertex3f(FLOOR_END_X, WALL_HEIGHT ,0);
    glEnd();
}
void DesenhaMotoseRastros(){
    for(int m = 0; m < Motos.size(); m++){
        float rastro_height = 20;
        if (Motos[m].explodiu < 40)
            rastro_height = rastro_height - (Motos[m].explodiu / 2.0f);
        bool apagar_rastro = false;
        for (int i =  0; i < Motos[m].curvax.size(); i++){
            float min_x, min_y, max_x, max_y;
            float work_x, work_y;
            if(i == Motos[m].curvax.size() - 1){
                work_x = Motos[m].x;
                work_y = Motos[m].y;
            }else{
                work_x = Motos[m].curvax[i+1];
                work_y = Motos[m].curvay[i+1];
            }
            if (work_x == Motos[m].curvax[i]){
                min_x = work_x - 1;
                max_x = work_x + 1;
            }else if (work_x > Motos[m].curvax[i]){
                max_x = work_x + 1;
                min_x = Motos[m].curvax[i] - 1;
            }else{
                max_x = Motos[m].curvax[i] + 1;
                min_x = work_x - 1;
            }
            if (work_y == Motos[m].curvay[i]){
                min_y = work_y - 1;
                max_y = work_y + 1;
            }else if (work_y > Motos[m].curvay[i]){
                max_y = work_y + 1;
                min_y = Motos[m].curvay[i] - 1;
            }else{
                max_y = Motos[m].curvay[i] + 1;
                min_y = work_y - 1;
            }
            if (Motos[m].explodiu < 40){
                glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_TRAIL]);

                glBegin(GL_QUADS);
                    glNormal3f(0.0, 0.0, -1.0);
                    if(Motos[m].explodiu)
                        glColor3f(1.0f, 1.0f, 0.0f);

                    else if (m == 0)
                        glColor3f(0.0f, 1.0f, 1.0f);
                    else
                        glColor3f(1.0f, 0.0f, 0.0f);
                    glTexCoord2f(1, 0.0); glVertex3f(min_x, rastro_height, min_y);
                    glTexCoord2f(1, 1); glVertex3f(max_x, rastro_height, min_y);
                    glTexCoord2f(0.0, 1); glVertex3f(max_x, 0, min_y);
                    glTexCoord2f(0.0, 0.0); glVertex3f(min_x, 0, min_y);
                glEnd();

                glBegin(GL_QUADS);
                    glNormal3f(0.0, 0.0, 1.0);

                    glTexCoord2f(0.0, 0.0); glVertex3f(min_x, 0, max_y);
                    glTexCoord2f(0.0, 1); glVertex3f(max_x, 0, max_y);
                    glTexCoord2f(1.0, 1); glVertex3f(max_x, rastro_height, max_y);
                    glTexCoord2f(1.0, 0.0); glVertex3f(min_x, rastro_height, max_y);



                glEnd();

                glBegin(GL_QUADS);
                    glNormal3f(-1.0, 0.0, 0.0);
                    glTexCoord2f(0.0, 1); glVertex3f(min_x, 0, min_y);
                    glTexCoord2f(0.0, 0.0); glVertex3f(min_x, 0, max_y);
                    glTexCoord2f(1.0, 0.0); glVertex3f(min_x, rastro_height, max_y);
                    glTexCoord2f(1.0, 1); glVertex3f(min_x, rastro_height ,min_y);



                glEnd();

                glBegin(GL_QUADS);
                    glNormal3f(1.0, 0.0, 0.0);

                    glTexCoord2f(1.0, 1); glVertex3f(max_x, rastro_height ,min_y);
                    glTexCoord2f(1.0, 0.0); glVertex3f(max_x, rastro_height, max_y);
                    glTexCoord2f(0.0, 0.0); glVertex3f(max_x, 0, max_y);
                    glTexCoord2f(0.0, 1); glVertex3f(max_x, 0, min_y);



                glEnd();

                glBegin(GL_QUADS);
                    glNormal3f(0, 1,0);
                    glTexCoord2f(0.0, 0.0); glVertex3f(min_x, rastro_height, min_y);
                    glTexCoord2f(1, 0); glVertex3f(min_x,rastro_height,max_y);
                    glTexCoord2f(1, 1); glVertex3f(max_x,rastro_height,max_y);
                    glTexCoord2f(0, 1); glVertex3f(max_x,rastro_height,min_y);

                glEnd();
            }
            else{
                apagar_rastro = true;
                if (Motos[m].explodiu != 100)
                    Motos[m].explodiu = 100;
                for(int i=min_x; i <= max_x; i++)
                    for(int j=min_y; j <= max_y; j++)
                        Tabela_Jogo[i][j] = 0;
            }
        }
        if(apagar_rastro){
            Motos[m].curvax.resize(0);
            Motos[m].curvay.resize(0);
        }
        if(!Motos[m].explodiu){
            if (glutGetWindow() == WindowId)
                glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_MOTO]);
            glPushMatrix();
                glTranslatef(Motos[m].x, 0, Motos[m].y);
                if (Motos[m].direcao == CIMA || Motos[m].direcao == BAIXO)
                    glScalef(20,(WALL_HEIGHT/4)+ 2,7);
                else
                    glScalef(7,(WALL_HEIGHT/4)+ 2,20);
                glRotatef(90, 1, 0, 0);
                glRotatef(90*(Motos[m].direcao + 1), 0, 0, 1);
                   GLUquadricObj* quadric = gluNewQuadric();
                   gluQuadricTexture(quadric,GL_TRUE);
                   gluQuadricNormals(quadric,GLU_SMOOTH);
                   gluQuadricOrientation(quadric, GLU_OUTSIDE);
                   gluQuadricDrawStyle(quadric, GLU_FILL);

                   gluSphere(quadric, 1, 10, 10);
                   gluDeleteQuadric(quadric);


            glPopMatrix();
        }
        for (int i = 0; i < num_lasers; i++){
            if(!Lasers[i].capturado){
                glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_TRAIL]);
                glColor3f(0.0f, 1.0f, 0.0f);
                glPushMatrix();
                    glTranslatef(Lasers[i].x, 0, Lasers[i].y);

                       glRotatef(90, -1, 0, 0);

                       GLUquadricObj* quadric = gluNewQuadric();
                       gluQuadricTexture(quadric,GL_TRUE);
                       gluQuadricNormals(quadric,GLU_SMOOTH);
                       gluQuadricOrientation(quadric, GLU_OUTSIDE);
                       gluQuadricDrawStyle(quadric, GLU_FILL);

                       gluCylinder(quadric,10,0, WALL_HEIGHT, 10, 10);
                       gluDeleteQuadric(quadric);


                glPopMatrix();
            }
        }
    }
}
void DesenhaExplosoes(){
    for (int i = 0; i < Explode_progress.size(); i++){
        if(Explode_progress[i] > 0){
            glBindTexture(GL_TEXTURE_2D, texName[TEXTURA_FIRE]);
            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();

            glTranslatef(Explode_x[i], 0, Explode_y[i]);
            glRotatef(90, 1, 0, 0);
            GLUquadricObj* quadric = gluNewQuadric();
            gluQuadricTexture(quadric,GL_TRUE);
            gluQuadricNormals(quadric,GLU_SMOOTH);
            gluQuadricOrientation(quadric, GLU_OUTSIDE);
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluSphere(quadric, Explode_progress[i]*3, Explode_progress[i] , Explode_progress[i] );
            gluDeleteQuadric(quadric);


            glPopMatrix();
        }
    }
}

// Minha Função de Desenho
void RenderScene(void)
{
	// Limpa a janela
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    DesenhaMapa();

    DesenhaMotoseRastros();

    DesenhaExplosoes();

	glFlush();
	glutSwapBuffers();
}

void HandleMouse(int button, int state, int x, int y)
{

    if ((button == 3 && state == GLUT_UP)||(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)){
			// Zoom-in
			if (CameraPersp.atx > 70){
                CameraPersp.atx -= 10;
                CameraPersp.atz -= 10;
                CameraPersp.aty -= 10;
			}

    }
    if ((button == 4 && state == GLUT_UP) || (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)){
			// Zoom out
                CameraPersp.atx += 10;
                CameraPersp.atz += 10;
                CameraPersp.aty += 10;

    }
    glutSetWindow(WindowId);
        PerspectiveViewing();
        glutPostRedisplay();

    glutSetWindow(SubWindowId);
          OrthoViewing();
        glutPostRedisplay();
}
// Movimento do Mouse Move a Câmera
void MouseMove(int x, int y){
    static int oldx = -1;
    static int oldy = -1;
    if (oldx == -1){
        oldx = x;
        oldy = y;
    }
	if (oldx > x + 5){
        CameraPersp.rotAngle -= 10;
        oldx = x;
	}
	if (oldx < x - 5){
        CameraPersp.rotAngle += 10;
        oldx = x;
	}
    oldy = y;
    glutSetWindow(WindowId);
        PerspectiveViewing();
        glutPostRedisplay();

    glutSetWindow(SubWindowId);
        OrthoViewing();
        glutPostRedisplay();
}
// Setas controlam a moto
void teclasDeControle( int tecla, int mouse_x, int mouse_y)
{
    /* OBS 1 : as variaveis acima poderiam ser globais ...*/
    switch( tecla )
    {
        case GLUT_KEY_UP:
             Motos[0].acelera = 1;
        break;
        case GLUT_KEY_LEFT:
            Motos[0].vira = 3;
        break;
        case GLUT_KEY_RIGHT:
            Motos[0].vira = 1;
        break;
        default:
        break;
    }
    glutSetWindow(WindowId);
        PerspectiveViewing();
        glutPostRedisplay();

    glutSetWindow(SubWindowId);
        OrthoViewing();
        glutPostRedisplay();
}
// WASD também controlam a moto, + e - controlam tamanho do mini-mapa
void teclado( unsigned char tecla, int mouse_x, int mouse_y)
{
    /* OBS 1 : as variaveis acima poderiam ser globais ...*/
    switch( tecla )
    {
        case 'w':
        case 'W':
             Motos[0].acelera = 1;
        break;
        case 'a':
        case 'A':
            Motos[0].vira = 3;
        break;
        case 'd':
        case 'D':
            Motos[0].vira = 1;
        break;
        case '+':
        case '=':
            if (SubWindowWidth <= WindowWidth - 100 && SubWindowHeight <= WindowHeight - 100){
                SubWindowWidth += 100;
                SubWindowHeight += 100;
            }
        break;
        case '-':
            if (SubWindowWidth >= 100 && SubWindowHeight >= 100){
                SubWindowWidth -= 100;
                SubWindowHeight -= 100;
            }
        break;
        default:
        break;
    }
    glutSetWindow(WindowId);
        PerspectiveViewing();
        glutPostRedisplay();

    glutSetWindow(SubWindowId);
        glutPositionWindow(WindowWidth - SubWindowWidth, WindowHeight - SubWindowHeight);
        glutReshapeWindow(SubWindowWidth,SubWindowHeight);
        OrthoViewing();
        glutPostRedisplay();
}
void createExplosion(int x, int y){
    Explode_x.push_back(x);
    Explode_y.push_back(y);
    Explode_progress.push_back(0);
    Explode_grow.push_back(true);
}

void IA_Facil(int i){
    if (ia_counter%20 == 0){
        int j, k;
        int deve_virar = !(rand()%100);
        int adiantar_virar = rand()%50;
        switch( Motos[i].direcao )
        {
            case CIMA:
                for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                    for(k = Motos[i].x + 3; k <= Motos[i].x + 40 + adiantar_virar + MOTO_SPEED; k++){
                        if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case BAIXO:
                for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                    for(k = Motos[i].x - 3; k >= Motos[i].x - 40 - adiantar_virar - MOTO_SPEED; k--){
                        if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case DIREITA:
                for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                    for(k = Motos[i].y + 3; k <= Motos[i].y + 40 + adiantar_virar + MOTO_SPEED; k++){
                        if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case ESQUERDA:
                for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                    for(k = Motos[i].y - 3; k >= Motos[i].y - 40 - adiantar_virar - MOTO_SPEED; k--){
                        if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            default:
            break;
        }
        if(deve_virar){
            int deve_virar = false;
            int direcao = rand()%2;
            int adiantar_virar = rand()%30;
            switch( Motos[i].direcao + (direcao*2) + 1 )
            {
                case CIMA:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x + 3; k <= Motos[i].x + 40 + adiantar_virar + MOTO_SPEED; k++){
                            if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case BAIXO:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x - 3; k >= Motos[i].x - 40 - adiantar_virar - MOTO_SPEED; k--){
                            if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case DIREITA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y + 3; k <= Motos[i].y + 40 + adiantar_virar + MOTO_SPEED; k++){
                            if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case ESQUERDA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y - 3; k >= Motos[i].y - 40 - adiantar_virar - MOTO_SPEED; k--){
                            if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                default:
                break;
            }
            if(!deve_virar)
                Motos[i].vira = (direcao*2) + 1 ;
            else
                Motos[i].vira = ((!direcao)*2) + 1 ;
        }
    }
}

void IA_Media(int i){
    if (ia_counter%10 == 0){
        int j, k;
        int deve_virar = !(rand()%100);
        int adiantar_virar = rand()%30;
        switch( Motos[i].direcao )
        {
            case CIMA:
                for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                    for(k = Motos[i].x + 3; k <= Motos[i].x + 40 + adiantar_virar + MOTO_SPEED; k++){
                        if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case BAIXO:
                for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                    for(k = Motos[i].x - 3; k >= Motos[i].x - 40 - adiantar_virar - MOTO_SPEED; k--){
                        if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case DIREITA:
                for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                    for(k = Motos[i].y + 3; k <= Motos[i].y + 40 + adiantar_virar + MOTO_SPEED; k++){
                        if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case ESQUERDA:
                for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                    for(k = Motos[i].y - 3; k >= Motos[i].y - 40 - adiantar_virar - MOTO_SPEED; k--){
                        if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            default:
            break;
        }
        if(deve_virar){
            int deve_virar = false;
            int direcao = rand()%2;
            int adiantar_virar = rand()%30;
            switch( Motos[i].direcao + (direcao*2) + 1 )
            {
                case CIMA:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x + 3; k <= Motos[i].x + 40 + adiantar_virar + MOTO_SPEED; k++){
                            if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case BAIXO:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x - 3; k >= Motos[i].x - 40 - adiantar_virar - MOTO_SPEED; k--){
                            if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case DIREITA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y + 3; k <= Motos[i].y + 40 + adiantar_virar + MOTO_SPEED; k++){
                            if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case ESQUERDA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y - 3; k >= Motos[i].y - 40 - adiantar_virar - MOTO_SPEED; k--){
                            if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                default:
                break;
            }
            if(!deve_virar)
                Motos[i].vira = (direcao*2) + 1 ;
            else
                Motos[i].vira = ((!direcao)*2) + 1 ;
        }
    }
}

void IA_Dificil(int i){
    if (ia_counter%5 == 0){
        int j, k;
        int deve_virar = !(rand()%100);
        int adiantar_virar = rand()%10;
        switch( Motos[i].direcao )
        {
            case CIMA:
                for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                    for(k = Motos[i].x + 3; k <= Motos[i].x + 25 + adiantar_virar + MOTO_SPEED; k++){
                        if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case BAIXO:
                for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                    for(k = Motos[i].x - 3; k >= Motos[i].x - 40 - adiantar_virar - MOTO_SPEED; k--){
                        if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case DIREITA:
                for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                    for(k = Motos[i].y + 3; k <= Motos[i].y + 40 + adiantar_virar + MOTO_SPEED; k++){
                        if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            case ESQUERDA:
                for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                    for(k = Motos[i].y - 3; k >= Motos[i].y - 40 - adiantar_virar - MOTO_SPEED; k--){
                        if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                            deve_virar = true;
                        }
                    }
                }
            break;
            default:
            break;
        }
        if(deve_virar){
            int deve_virar = false;
            int direcao = rand()%2;
            int adiantar_virar = rand()%30;
            switch( Motos[i].direcao + (direcao*2) + 1 )
            {
                case CIMA:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x + 3; k <= Motos[i].x + 40 + adiantar_virar + MOTO_SPEED; k++){
                            if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case BAIXO:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x - 3; k >= Motos[i].x - 40 - adiantar_virar - MOTO_SPEED; k--){
                            if (k <= FLOOR_END_X && k >= 0 && Tabela_Jogo[k][j] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case DIREITA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y + 3; k <= Motos[i].y + 40 + adiantar_virar + MOTO_SPEED; k++){
                            if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                case ESQUERDA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y - 3; k >= Motos[i].y - 40 - adiantar_virar - MOTO_SPEED; k--){
                            if (k <= FLOOR_END_Z && k >= 0 && Tabela_Jogo[j][k] == 1){
                                deve_virar = true;
                            }
                        }
                    }
                break;
                default:
                break;
            }
            if(!deve_virar)
                Motos[i].vira = (direcao*2) + 1 ;
            else
                Motos[i].vira = ((!direcao)*2) + 1 ;
        }
    }
}
// Avança o estado das explosões
void avancarExplosoes(){
    for (int i = 0; i < Explode_progress.size(); i++){
        if (Explode_progress[i] >= 0){
            if (Explode_grow[i]){
                if (Explode_progress[i] < 30)
                    Explode_progress[i] += 1;
                else
                    Explode_grow[i] = false;
            }
            else{
                    Explode_progress[i] -= 1;
            }
        }
    }
    for (int i = 0; i < num_motos; i++){
        if (Motos[i].explodiu && Motos[i].explodiu < 40){
            Motos[i].explodiu++;
        }
    }
}

// Controla a captura de Lasers pelo jogador
void ColideLaser(){
        int moto_xmin, moto_xmax, moto_ymin, moto_ymax;
        int laser_xmin, laser_xmax, laser_ymin, laser_ymax;
        switch( Motos[0].direcao )
        {
            case CIMA:
            moto_xmin = Motos[0].x - 11;
            moto_xmax = Motos[0].x + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[0].acelera));
            moto_ymin = Motos[0].y - 4;
            moto_ymax = Motos[0].y + 4;
            break;
            case BAIXO:
            moto_xmin = Motos[0].x - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[0].acelera));
            moto_xmax = Motos[0].x + 11;
            moto_ymin = Motos[0].y - 4;
            moto_ymax = Motos[0].y + 4;
            break;
            case DIREITA:
            moto_ymin = Motos[0].y - 11;
            moto_ymax = Motos[0].y + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[0].acelera));
            moto_xmin = Motos[0].x - 4;
            moto_xmax = Motos[0].x + 4;
            break;
            case ESQUERDA:
            moto_ymin = Motos[0].y - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[0].acelera));
            moto_ymax = Motos[0].y + 11;
            moto_xmin = Motos[0].x - 4;
            moto_xmax = Motos[0].x + 4;
            break;
        }
        for (int i = 0; i < num_lasers; i++){
            if(!Lasers[i].capturado){
                laser_xmin = Lasers[i].x - 10;
                laser_xmax = Lasers[i].x + 10;
                laser_ymin = Lasers[i].y - 10;
                laser_ymax = Lasers[i].y + 10;
                if( // Testa se os lasers cruzam a moto do jogador
                (
                   (   (laser_xmin <= moto_xmax && laser_xmin >= moto_xmin)
                        || (laser_xmax <= moto_xmax && laser_xmax >= moto_xmin) )
                   &&  (   (laser_ymin <= moto_ymax && laser_ymin >= moto_ymin)
                        || (laser_ymax <= moto_ymax && laser_ymax >= moto_ymin) )
                )
                 ||
                (
                   (   (moto_xmin <= laser_xmax && moto_xmin >= laser_xmin)
                        || (moto_xmax <= laser_xmax && moto_xmax >= laser_xmin) )
                   &&  (   (moto_ymin <= laser_ymax && moto_ymin >= laser_ymin)
                        || (moto_ymax <= laser_ymax && moto_ymax >= laser_ymin) )
                )
                )
                {
                    Lasers[i].capturado = true;
                    lasers_capturados++;
                    cout << "Laser Capturado! Faltam " << 4 - lasers_capturados << endl;
                    cout << Motos[0].direcao << endl;
                }
            }
        }

}
void MoveeColideMotos(){
    for (int i = 0; i < num_motos; i++){
    if(!Motos[i].explodiu){
        int motoi_xmin, motoi_xmax, motoi_ymin, motoi_ymax;
        int motoj_xmin, motoj_xmax, motoj_ymin, motoj_ymax;
        switch( Motos[i].direcao )
        {
            case CIMA:
            motoi_xmin = Motos[i].x - 11;
            motoi_xmax = Motos[i].x + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
            motoi_ymin = Motos[i].y - 4;
            motoi_ymax = Motos[i].y + 4;
            break;
            case BAIXO:
            motoi_xmin = Motos[i].x - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
            motoi_xmax = Motos[i].x + 11;
            motoi_ymin = Motos[i].y - 4;
            motoi_ymax = Motos[i].y + 4;
            break;
            case DIREITA:
            motoi_ymin = Motos[i].y - 11;
            motoi_ymax = Motos[i].y + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
            motoi_xmin = Motos[i].x - 4;
            motoi_xmax = Motos[i].x + 4;
            break;
            case ESQUERDA:
            motoi_ymin = Motos[i].y - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
            motoi_ymax = Motos[i].y + 11;
            motoi_xmin = Motos[i].x - 4;
            motoi_xmax = Motos[i].x + 4;
            break;
        }
        for (int j = i+1; j < num_motos; j++){
            if(!Motos[j].explodiu){
                switch( Motos[j].direcao )
                {
                    case CIMA:
                    motoj_xmin = Motos[j].x - 11;
                    motoj_xmax = Motos[j].x + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
                    motoj_ymin = Motos[j].y - 4;
                    motoj_ymax = Motos[j].y + 4;
                    break;
                    case BAIXO:
                    motoj_xmin = Motos[j].x - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
                    motoj_xmax = Motos[j].x + 11;
                    motoj_ymin = Motos[j].y - 4;
                    motoj_ymax = Motos[j].y + 4;
                    break;
                    case DIREITA:
                    motoj_ymin = Motos[j].y - 11;
                    motoj_ymax = Motos[j].y + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
                    motoj_xmin = Motos[j].x - 4;
                    motoj_xmax = Motos[j].x + 4;
                    break;
                    case ESQUERDA:
                    motoj_ymin = Motos[j].y - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera));
                    motoj_ymax = Motos[j].y + 11;
                    motoj_xmin = Motos[j].x - 4;
                    motoj_xmax = Motos[j].x + 4;
                    break;
                }

                if((
               (   (motoi_xmin <= motoj_xmax && motoi_xmin >= motoj_xmin)
                    || (motoi_xmax <= motoj_xmax && motoi_xmax >= motoj_xmin) )
                &&  (   (motoi_ymin <= motoj_ymax && motoi_ymin >= motoj_ymin)
                    || (motoi_ymax <= motoj_ymax && motoi_ymax >= motoj_ymin) )
                )
         ||
        (
           (   (motoj_xmin <= motoi_xmax && motoj_xmin >= motoi_xmin)
                || (motoj_xmax <= motoi_xmax && motoj_xmax >= motoi_xmin) )
           &&  (   (motoj_ymin <= motoi_ymax && motoj_ymin >= motoi_ymin)
                || (motoj_ymax <= motoi_ymax && motoj_ymax >= motoi_ymin) )
        )
        )
                {
                    Motos[i].explodiu = 1;
                    Motos[j].explodiu = 1;
                    createExplosion(((Motos[i].x + Motos[j].x)/2), ((Motos[i].y + Motos[j].y)/2));
                    goto KILL_IF_EXPLODE;
                }
            }
        }
        if (Motos[i].explodiu == 1)
            goto KILL_IF_EXPLODE;
        if (Motos[i].vira == 0){
            int j, k;
            switch( Motos[i].direcao )
            {
                case CIMA:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x + 3; k <= Motos[i].x + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); k++){
                            if (Tabela_Jogo[k][j] == 1){
                                Motos[i].explodiu = 1;
                                createExplosion(Motos[i].x, Motos[i].y);
                                goto KILL_IF_EXPLODE;
                            }
                        }
                    }
                break;
                case BAIXO:
                    for(j = Motos[i].y - 3; j <= Motos[i].y + 3; j++){
                        for(k = Motos[i].x - 3; k >= Motos[i].x - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); k--){
                            if (Tabela_Jogo[k][j] == 1){
                                Motos[i].explodiu = 1;
                                createExplosion(Motos[i].x, Motos[i].y);
                                goto KILL_IF_EXPLODE;
                            }
                        }
                    }
                break;
                case DIREITA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y + 3; k <= Motos[i].y + 11 + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); k++){
                            if (Tabela_Jogo[j][k] == 1){
                                Motos[i].explodiu = 1;
                                createExplosion(Motos[i].x, Motos[i].y);
                                goto KILL_IF_EXPLODE;
                            }
                        }
                    }
                break;
                case ESQUERDA:
                    for(j = Motos[i].x - 3; j <= Motos[i].x + 3; j++){
                        for(k = Motos[i].y - 3; k >= Motos[i].y - 11 - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); k--){
                            if (Tabela_Jogo[j][k] == 1){
                                Motos[i].explodiu = 1;
                                createExplosion(Motos[i].x, Motos[i].y);
                                goto KILL_IF_EXPLODE;
                            }
                        }
                    }
                break;
                default:
                break;
            }

            if (!Motos[i].explodiu){
                switch( Motos[i].direcao )
                {
                    case CIMA:
                        for(j = Motos[i].x; j <= Motos[i].x + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); j++){
                            Tabela_Jogo[j][Motos[i].y - 1] = 1;
                            Tabela_Jogo[j][Motos[i].y] = 1;
                            Tabela_Jogo[j][Motos[i].y + 1] = 1;
                        }
                        Motos[i].x += MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera);
                    break;
                    case BAIXO:
                        for(j = Motos[i].x; j >= Motos[i].x - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); j--){
                            Tabela_Jogo[j][Motos[i].y - 1] = 1;
                            Tabela_Jogo[j][Motos[i].y] = 1;
                            Tabela_Jogo[j][Motos[i].y + 1] = 1;
                        }
                        Motos[i].x -= MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera);
                    break;
                    case DIREITA:
                        for(j = Motos[i].y; j <= Motos[i].y + (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); j++){
                            Tabela_Jogo[Motos[i].x - 1][j] = 1;
                            Tabela_Jogo[Motos[i].x][j] = 1;
                            Tabela_Jogo[Motos[i].x + 1][j] = 1;
                        }
                        Motos[i].y += MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera);
                    break;
                    case ESQUERDA:
                        for(j = Motos[i].y; j >= Motos[i].y - (MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera)); j--){
                            Tabela_Jogo[Motos[i].x - 1][j] = 1;
                            Tabela_Jogo[Motos[i].x][j] = 1;
                            Tabela_Jogo[Motos[i].x + 1][j] = 1;
                        }
                        Motos[i].y -= MOTO_SPEED + MOTO_SPEED *(Motos[i].acelera);
                    break;
                    default:
                    break;
                }
            }
        }else {
            Motos[i].direcao = (Motos[i].direcao + Motos[i].vira) % 4;
            //if (i == 0 && Motos[0].vira == 1)
            //    CameraPersp.rotAngle -= 90;
            //if (i == 0 && Motos[0].vira == 3)
            //    CameraPersp.rotAngle += 90;
            Motos[i].vira = 0;
            Motos[i].curvax.push_back(Motos[i].x);
            Motos[i].curvay.push_back(Motos[i].y);
        }
        Motos[i].acelera = 0;
    }
KILL_IF_EXPLODE:
    ; // Pula para próxima iteração do for
      // Nesse caso o uso de goto pode
      // ser justificado por ser apenas um break maior :P
}
}


//Jogo
void playGame(int value){
    avancarExplosoes(); // Avança o estado das explosões

    ColideLaser(); // Controla a captura de Lasers pelo jogador

    if(!game_end){

    // Executa IA de cada moto, conforme sua configuração
        for (int i = 1; i < num_motos; i++){
                switch( IA_Level[i] )
                {
                    case 1:
                        IA_Facil(i);
                    break;
                    case 2:
                        IA_Media(i);
                    break;
                    case 3:
                        IA_Dificil(i);
                    break;
                    case 0:
                    default:
                        break;

                }
        }
        ia_counter++;

    // Colisões e andar
        MoveeColideMotos();

        if (Motos[0].explodiu){
            cout << "Game Over - Sua Moto foi Destruída" << endl;
            game_end = true;
        } else if((modo_de_jogo != MODO_NORMAL) && lasers_capturados == num_lasers){
            cout << "Parabéns - Você capturou todos os Lasers" << endl;
            game_end = true;
        } else if(modo_de_jogo != MODO_LASER){
            int motos_adversarias = 0;
            for (int i = 1; i < num_motos; i++){
                if (!Motos[i].explodiu)
                    motos_adversarias++;
            }
            if (motos_adversarias == 0){
                cout << "Parabéns - Todas as Motos Adversárias foram destruídas" << endl;
                game_end = true;
            }
        }
    }
    glutTimerFunc(25, playGame, 0);
    glutSetWindow(WindowId);
        PerspectiveViewing();
        glutPostRedisplay();

    glutSetWindow(SubWindowId);
        OrthoViewing();
        glutPostRedisplay();
}
void gameStart(){
    srand ( time(NULL) );
    char ler = 's';
    bool lendo_arquivo = false;
    cout << "Ler do arquivo lb.cfg?(S/N)" << endl;
    cin >> ler;
    if(ler == 's' || ler == 'S'){
        freopen ("lb.cfg","r",stdin);
        lendo_arquivo = true;
    }
    if(!lendo_arquivo)
        cout << "Digite a quilometragem do mapa: (x)"<< endl;
    cin >> kilom_x;
    if (kilom_x < 2)
        kilom_x = 2;
    if(!lendo_arquivo)
        cout << "Digite a quilometragem do mapa: (y)"<< endl;
    cin >> kilom_z;
    if (kilom_z < 2)
        kilom_z = 2;

    if(!lendo_arquivo)
        cout << "Digite o número de motos adversárias: (y)"<< endl;
    cin >> num_motos;

    if(!lendo_arquivo){
        cout << "Modos de Jogo:"<< endl;
        cout << "0 -> Destruir Adversários" << endl;
        cout << "1 -> Capturar Lasers" << endl;
        cout << "2 -> Destruir Adversários ou Capturar Lasers" << endl;
        cout << endl;
    }

    if(!lendo_arquivo)
        cout << "Escolha o modo de jogo:" << endl;
    cin >> modo_de_jogo;

    if (modo_de_jogo != 0){
        if(!lendo_arquivo)
            cout << "Digite o número de Lasers: (y)"<< endl;
            cin >> num_lasers;
    }else{
        num_lasers = 0;
    }

    if (num_motos < 0)
        num_motos = 0;
    num_motos++;
    IA_Level.resize(num_motos);
    if(!lendo_arquivo){
        cout << "Dificuldades:"<< endl;
        cout << "0 -> Segue Reto" << endl;
        cout << "1 -> Sobrevive (Fácil)" << endl;
        cout << "2 -> Sobrevive (Médio)" << endl;
        cout << "3 -> Sobrevive (Difícil)" << endl;
        cout << endl;
    }
    for(int i=1; i < num_motos;i++){
        if(!lendo_arquivo)
            cout << "Escolha a dificuldade da moto " << i << ":" << endl;
        cin >> IA_Level[i];
    }

    Tabela_Jogo.resize(FLOOR_END_X + 1);
    for (int i = 0; i < FLOOR_END_X + 1; i++){
        Tabela_Jogo[i].resize(FLOOR_END_Z + 1);
    }
    for (int i = 0; i < FLOOR_END_X + 1; i++){
        for (int j = 0; j < FLOOR_END_Z + 1; j++){
            if (i == 0 || j == 0 || i == FLOOR_END_X || j == FLOOR_END_Z )
                Tabela_Jogo[i][j] = 1;
            else
                Tabela_Jogo[i][j] = 0;
        }
    }
    Motos.resize(num_motos);
    for (int i = 0; i < num_motos; i++){
        int x = (rand() % (FLOOR_END_X - 100)) + 50;
        int y = (rand() % (FLOOR_END_Z - 100)) + 50;
        Motos[i].vira = 0;
        Motos[i].curvax.push_back(x);
        Motos[i].curvay.push_back(y);
        Motos[i].x = x;
        Motos[i].y = y;
        if(rand() % 2)
            if (x > FLOOR_END_X / 2)
                Motos[i].direcao = BAIXO;
            else
                Motos[i].direcao = CIMA;
        else
            if (y > FLOOR_END_Z / 2)
                Motos[i].direcao = ESQUERDA;
            else
                Motos[i].direcao = DIREITA;
        Motos[i].explodiu =0;
        Motos[i].acelera =0;
    }
    for (int i = 0; i < num_lasers; i++){
        Laser umLaser;
        umLaser.capturado = false;
        umLaser.x = (rand() % (FLOOR_END_X - 160)) + 80;
        umLaser.y = (rand() % (FLOOR_END_Z - 160)) + 80;
        Lasers.push_back(umLaser);
    }
    game_end = false;
}
// Programa Principal
int main(int argc, char *argv[])
{
    gameStart();
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WindowWidth,WindowHeight);
	WindowId = glutCreateWindow("Tron 3D - by Gustavo Valdez e João Gaiewski");
	glutSpecialFunc( teclasDeControle );
	glutPassiveMotionFunc(MouseMove);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(teclado);
	glutMouseFunc(HandleMouse);
    SetupRC();
    glutTimerFunc(25, playGame, 0);
	SubWindowId = glutCreateSubWindow(WindowId, WindowWidth - SubWindowWidth, WindowHeight - SubWindowHeight, SubWindowWidth, SubWindowHeight);
	glutSpecialFunc( teclasDeControle );
	glutPassiveMotionFunc(MouseMove);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(teclado);
	glutMouseFunc(HandleMouse);
    SetupRC();

	glutMainLoop();
    return (0);
}
