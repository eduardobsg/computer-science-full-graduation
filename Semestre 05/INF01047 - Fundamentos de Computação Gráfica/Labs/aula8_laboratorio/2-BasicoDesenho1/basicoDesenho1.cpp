/*
FCG  - BasicoDesenho.cpp
incrementa o programa Basico com desenho de uma figura geometrica 

a) Observe a estrutura declarada para representação de pontos, as variáveis P1, 
P2 e P3, e a função que as inicializa

// estrutura que descreve um ponto (x,y) 
typedef struct XY { 
        float x; 
        float y; 
} PontoXY;

PontoXY P1, P2, P3;

void SetupObjeto (void) { 
    P1.x = 0; 
    P1.y = 1; 
    P2.x = -1; 
    P2.y = 0; 
    P3.x = 1; 
    P3.y = 0; 
}

b) Observe como esta estrutura é utilizada na função “RenderScene”, com as 
primitivas de desenho.

e) Modifique a cor de desenho do triângulo alterando os parâmetros da função 
glColor3f (1.0f, 0.0f, 0.0f);
*/

/*
include de definicoes das funcoes da glut 
glut.h inclui gl.h, que contem os headers de funcoes da OpenGL propriamente dita
glut.h inclui tambem definicoes necessarias para o uso de OpenGl nos diversos ambientes Windows
*/
#include <GL/glut.h>

// estrutura que descreve um ponto (x,y)
typedef struct XY {
        GLfloat x;
        GLfloat y;
} PontoXY;

PontoXY P1, P2, P3;


/* 
Função de callback de desenho
Executada sempre que é necessario re-exibir a imagem
*/
void RenderScene(void){
	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);
 
    // Indica para a m&iuml;&iquest;&frac12;quina de estados da OpenGL que todas as primitivas geom&iuml;&iquest;&frac12;tricas que 
    // forem chamadas deste ponto em diante devem ter a cor vermelha
    //glColor3f (1.0f, 0.0f, 0.0f); // cor vermelha
    glColor3f (1.0f, 0.0f, 1.0f); // cor rosa
    
    // Chamadas de fun&iuml;&iquest;&frac12;&iuml;&iquest;&frac12;es OpenGL para desenho
    glBegin (GL_TRIANGLES);
	  glVertex2f (P1.x,P1.y);
	  glVertex2f (P2.x,P2.y);
	  glVertex2f (P3.x,P3.y);
    glEnd();

	// Flush dos comandos de desenho que estejam no &quot;pipeline&quot; da OpenGL
    // para conclusao da geracao da imagem
    glFlush();
}

/* Inicializa aspectos do rendering */
void SetupRC(void){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // Cor de fundo da janela
}

/* Inicializa os tres pontos com valores default */
void SetupObjeto (void){ 
    P1.x = 0;
    P1.y = 1;
    P2.x = -1;
    P2.y = 0;
    P3.x = 1;
    P3.y = 0;
}


/* 
Parte principal - ponto de início de execução
Cria janela 
Inicializa aspectos relacionados a janela e a geracao da imagem
Especifica a funcao de callback de desenho
*/
int main(int argc, char **argv){
	glutInit(&argc, argv);

    // Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Cria uma janela com o titulo especificado
	glutCreateWindow("Meu primeiro programa OpenGL&quot");
 
    // Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
	glutDisplayFunc(RenderScene);

    // Executa a inicializacao de parametros de exibicao
	SetupRC();
 
    // Inicializa as informacoes geometricas do objeto
    SetupObjeto();

    // Dispara a &quot;maquina de estados&quot; de OpenGL 
	glutMainLoop();
	
	return 0;
}

