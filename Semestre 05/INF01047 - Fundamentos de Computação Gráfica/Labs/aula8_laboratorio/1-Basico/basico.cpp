/* 
Cadeira de FCG
Programa: Basico.cpp
Atualizado em 2007

a) Estude o programa Basico.cpp e tente entender sua organização. Observe com 
atenção os seguintes aspectos:
Linguagem C: definição e chamada de funções
OpenGL: include  e chamadas de funções gl<..>
Estrutura básica:
    - função principal, onde a comunicação com a OpenGL é estabelecida e são 
    disparadas as inicializações necessárias;
    - função “RenderScene”, onde serão incluídas as funções de desenho;
    - função de inicialização “SetupRC”, para conter as inicializações relativas 
    à exibição.
    
b) Altere a cor de fundo da janela para verde, modificando os argumentos da 
chamada da função
   
glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

Os valores especificados são valores de RGBA (Red-Green-Blue-Alpha) que variam 
de 0 a 1, do tipo float. Não se preocupe com o Alpha, pois ele será usado para 
efeitos de transparência e combinação de imagens, posteriormente.
*/

#include <GL/glut.h>
/* 
include de definicoes das funcoes da glut 
glut.h inclui gl.h, que contem os headers de funcoes da OpenGL propriamente dita
glut.h inclui tambem definicoes necessarias para o uso de OpenGl nos diversos 
ambientes Windows
*/


/* 
Função de callback de desenho
Executada sempre que eh necessario re-exibir a imagem
*/
void RenderScene(void){
	glClear(GL_COLOR_BUFFER_BIT); // Limpa a janela com a cor especificada como cor de fundo    
    // funcoes OpenGL para desenho
    glFlush(); // Força a execução das instruções do pipeline OpenGL, para desenhar a imagem
}


/* Inicializa aspectos do rendering */
void SetupRC(void){
    //glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  // Cor de fundo da janela - verde
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // Cor de fundo da janela - azul
    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);  // Cor de fundo da janela - vermelho
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
	glutCreateWindow("Programa Basico OpenGL");

    // Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
	glutDisplayFunc(RenderScene);

    // Executa a inicializacao de parametros de exibicao
	SetupRC();

    // Dispara a &quot;maquina de estados&quot; de OpenGL 
	glutMainLoop();
	
	return 0;
}

