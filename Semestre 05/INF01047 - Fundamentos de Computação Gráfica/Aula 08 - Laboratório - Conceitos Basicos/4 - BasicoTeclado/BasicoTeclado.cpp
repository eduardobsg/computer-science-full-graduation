/* 
BasicoTeclado.cpp
incrementa o programa Basico com uso de teclado 

a) Observe as novas funções introduzidas no programa, para tratamento de eventos 
de teclado: SpecialKeys e KeyboardFunc e a forma como elas são “informadas” para 
a OpenGL na função main do programa.

b) Compile e execute o programa, acionando as diversas teclas identificadas.

c) Busque na documentação da GLUT as constantes de identificação de outras teclas. 
Escolha uma para programar o controle de cor do triângulo exibido e outra para 
encerrar o programa. 
*/

/* include de definicoes das funcoes da glut 
   glut.h inclui gl.h, que contem os headers de funcoes da OpenGL propriamente dita
   glut.h inclui tambem definicoes necessarias para o uso de OpenGl nos diversos 
   ambientes Windows
*/
#include <gl/glut.h>

/* estrutura que descreve um ponto (x,y) */
typedef struct XY {
        GLfloat x;
        GLfloat y;
} PontoXY;

PontoXY P1, P2, P3;

/* estrutura que descreve uma tripla RGB para cor */
typedef struct RGB {
        GLfloat r;
        GLfloat g;
        GLfloat b;
} TriplaRGB;

TriplaRGB cor;


/* 
Função de callback de desenho
Executada sempre que é necessario re-exibir a imagem
*/
void RenderScene(void){
	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);
 
    // Indica para a m&iuml;&iquest;&frac12;quina de estados da OpenGL que todas as primitivas geom&iuml;&iquest;&frac12;tricas que 
    // forem chamadas deste ponto em diante devem ter a cor vermelha
    glColor3f (cor.r, cor.g, cor.b); 
    
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
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  // Cor de fundo da janela - preto
}

/* Inicializa os tres pontos com valores default */
void SetupObjeto (void){ 
    P1.x = 0;
    P1.y = 1;
    P2.x = -1;
    P2.y = 0;
    P3.x = 1;
    P3.y = 0;
    
    cor.r = 0;
    cor.g = 0;
    cor.r = 0;
}
    
void SpecialKeys(int key, int x, int y){
	if(key == GLUT_KEY_UP)
		P1.y += 0.5;

	if(key == GLUT_KEY_DOWN)
		P1.y -= 0.5f;

	if(key == GLUT_KEY_LEFT)
		P1.x -= 0.5f;

	if(key == GLUT_KEY_RIGHT)
		P1.x += 0.5f;

	if(P1.y < -1.0f)
		P1.y = -1.0f;

	if (P1.y > 1.0f)
		P1.y = 1.0f;

    if (P1.x < -1.0f)
		P1.x = -1.0f;

    if (P1.x > 1.0f)
		P1.x = 1.0f;
  
    if (key == GLUT_KEY_F1){
       cor.r = 1;
    }
    
    if (key == GLUT_KEY_F2){
       cor.g = 1;
    }
    
    if (key == GLUT_KEY_F3){
       cor.b = 1;
    }
    
    if (key == GLUT_KEY_F4){
       cor.r = 0;
       cor.g = 0;
       cor.b = 0;
    }
    
    if (key == GLUT_KEY_F5){
       exit(1);
    }

    // Refresh da imagem: força a execução da RenderScene
	glutPostRedisplay();
}
    

/* Especifica callback comum de teclado */
void KeyboardFunc ( unsigned char key, int x, int y ){
     if(key == 'r')
       SetupObjeto();
     glutPostRedisplay();
     
}


/* 
Parte principal - ponto de início de execução
Cria janela 
Inicializa aspectos relacionados a janela e a geracao da imagem
Especifica a funcao de callback de desenho
Especifica as funcões de callback de teclado para teclas normais e especiais
*/
int main(void){
	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Cria uma janela com o titulo especificado
	glutCreateWindow("Programa com uso de Teclado&quot");

    // Especifica a funcao que vai tratar teclas comuns 
    glutKeyboardFunc(KeyboardFunc);
    
    // Especifica a funcao que vai tratar teclas especiais (up, down, left, right, mose, F1-F11)
 	glutSpecialFunc(SpecialKeys);
  
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

