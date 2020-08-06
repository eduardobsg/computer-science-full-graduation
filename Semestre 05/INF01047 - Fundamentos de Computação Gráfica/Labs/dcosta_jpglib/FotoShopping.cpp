#include <cstdlib>
#include <iostream>
#include <string>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glui.h>

#include "JpegImage.h"

using namespace std;


//------------------------------------------------------------------------------
// TEMPLATE DAS FUNÇÕES OPENGL
//------------------------------------------------------------------------------
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

//------------------------------------------------------------------------------
// TEMPLATE DAS FUNÇÕES DA INTERFACE
//------------------------------------------------------------------------------
void atribui();
void salvar();		
void quantizar();
void luminance();
void vertical();
void horizontal();


//------------------------------------------------------------------------------
// VARIÁVEIS GLOBAIS
//------------------------------------------------------------------------------
JpegImage *img = NULL;                   // imagem de teste
JpegImage *aux = NULL;
int segments;
char text[35];
int x, y;


//------------------------------------------------------------------------------
// Função chamada pelo opengl para desenhar na tela
//------------------------------------------------------------------------------
void display(void)
{
	 glutSetWindow(x);
    // limpa buffers do frame a ser mostrado
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  //  glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);

    // carrega matrix identidade como modelview
    glLoadIdentity();
    
    // seta posição inicial para desenho
    glRasterPos2i(0,0);
    
    // se existe imagem 
    if (img)
    {            
        if (img->getChannels() == 3)
        {
            // imagem contém 3 canais (RGB)
            glDrawPixels(   img->getWidth(),           // largura da imagem
                            img->getHeight(),          // altura da imagem
                            GL_RGB,                    // formato
                            GL_UNSIGNED_BYTE,          // alinhamento dos dados
                            img->getImage()            // array com dados
                         );
        }
        else
        {
            // imagem contém 4 canais (RGBA)
            glDrawPixels(   img->getWidth(),           // largura da imagem
                            img->getHeight(),          // altura da imagem
                            GL_RGBA,                   // formato
                            GL_UNSIGNED_BYTE,          // alinhamento dos dados
                            img->getImage()            // array com dados
                         );            
        }   
    }

    // chamada glut para trocar de buffer
    glutSwapBuffers();
}

void display2(void)
{
	 glutSetWindow(y); 
	// limpa buffers do frame a ser mostrado
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // carrega matrix identidade como modelview
    glLoadIdentity();
    
    // seta posição inicial para desenho
    glRasterPos2i(0,0);
    
    // se existe imagem 
    if (aux)
    {            
        if (aux->getChannels() == 3)
        {
            // imagem contém 3 canais (RGB)
            glDrawPixels(   aux->getWidth(),           // largura da imagem
                            aux->getHeight(),          // altura da imagem
                            GL_RGB,                    // formato
                            GL_UNSIGNED_BYTE,          // alinhamento dos dados
                            aux->getImage()            // array com dados
                         );
        }
        else
        {
            // imagem contém 4 canais (RGBA)
            glDrawPixels(   aux->getWidth(),           // largura da imagem
                            aux->getHeight(),          // altura da imagem
                            GL_RGBA,                   // formato
                            GL_UNSIGNED_BYTE,          // alinhamento dos dados
                            aux->getImage()            // array com dados
                         );            
        }   
     glutSwapBuffers();
	}

	
    // chamada glut para trocar de buffer
   
	else  {
			glClear(GL_COLOR_BUFFER_BIT);

			 //Executa os comandos OpenGL
		    glFlush();
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}
}

//------------------------------------------------------------------------------
// Função chamada sempre que uma janela é criada ou tem seu tamanho modificado
//------------------------------------------------------------------------------
void reshape(int w, int h)
{
	if (h < 1)
       h = 1;
    
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (float)w, 0.0, (float)h);
	glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------------------------
// Função chamada sempre que uma tecla é apertada
//------------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
    {  
		default:   break;
	}
}
//------------------------------------------------------------------------------
// FUNÇÕES DA INTERFACE
//------------------------------------------------------------------------------

void atribui()		//Copia um vetor de imagens para outro
{
	if(aux)
	{
			delete aux;
			aux = new JpegImage(img);
			glutSetWindow(y);
			glutPostRedisplay();
	}
	else 
	{
		aux = new JpegImage(img);
		glutSetWindow(y);
		glutPostRedisplay();
	}
}

void salvar()		//Salva uma imagem em jpg	
{
	if(aux)
		aux->writeJpegFile(text, 75);
}

void quantizar()		//Chama função para a quantização
{
	if(aux)
		aux->quantizacao(segments);
	glutSetWindow(y);
	glutPostRedisplay();
	
}
void luminance()		//Chama a função para a luminância
{
	if(aux)
		aux->luminancia();
	glutSetWindow(y);
	glutPostRedisplay();

}

void vertical() //Chama a função para espelhamento
{ 
	img->espelhamento_vertical(); 
	glutSetWindow(x);
	glutPostRedisplay();
}		

void horizontal() //Chama a função para espelhamento
{ 
	img->espelhamento_horizontal(); 
	glutSetWindow(x);
	glutPostRedisplay();

}	
	




int main(int argc, char *argv[])
{
	int i, j;
    if (argc < 1)
    {
        cout << "null parameter" << endl;
        system("pause");
    }   
    // cria objeto JpegImage
    img = new JpegImage();
   
    // testa se conseguiu alocar memoria
    if (!img) {
        cout << "ERRO: nao foi possivel alocar memoria para imagem..." << endl;
    }

    // tenta carregar arquivo .jpg
    if ( img->readJpegFile( argv[1] ) == false )
    {
        // libera memoria do objeto alocado anteriormente
        delete img;
        img = NULL;
       
        return EXIT_SUCCESS;       
    }
	


	//------------------------------------------------------------
    // funções do opengl	
    //------------------------------------------------------------
    
	//------------------------------------------------------------
	//CRIA JANELA 1
	//------------------------------------------------------------
	glutInit(&argc, argv);
    // seta flags de display 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
	
    // seta posição inicial da janela
    glutInitWindowPosition(0, 0);
	
	// seta tamanho da janela
	glutInitWindowSize( img->getWidth(), img->getHeight());
	
	
    // cria a janela
	  x = glutCreateWindow("Imagem Original");
    glutSetWindow(x);
    // cadastra função para desenhar na tela
	glutDisplayFunc(display);
	
	// cadastra função para redimensionamento de janela
	glutReshapeFunc(reshape);
	
	// cadastra função para manipular entradas do teclado
    glutKeyboardFunc(keyboard);
	
	// cadastra função padrão para desenho
    glutIdleFunc(display);
    
    // seta a maneira de como os pixeis serao armazenados
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//------------------------------------------------------------
	//CRIA JANELA 2
	//------------------------------------------------------------
	
	glutInitWindowPosition(500, 0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	y =  glutCreateWindow("Imagem Copiada");
    
	glutSetWindow(y);
			
    // cadastra função para desenhar na tela
	glutDisplayFunc(display2);
	
	// cadastra função para redimensionamento de janela
	glutReshapeFunc(reshape);
	
	// cadastra função para manipular entradas do teclado
    glutKeyboardFunc(keyboard);
	
	// cadastra função padrão para desenho
    glutIdleFunc(display2);
    
    // seta a maneira de como os pixeis serao armazenados
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//------------------------------------------------------------
	//CRIA JANELA COM BOTÕES
	//------------------------------------------------------------
	GLUI *glui = GLUI_Master.create_glui( "FotoShopping", 0,500,350 );
	
	//Copia Imagem
	glui->add_button("Copiar", -1, (GLUI_Update_CB)atribui); 
	
	//Painel com espelhamentos
	GLUI_Panel *obj_panel = glui->add_panel ( "Espelhar" );
	//glui->add_button( obj_panel,"Quit", 0,(GLUI_Update_CB)exit );
	glui->add_button_to_panel(obj_panel, "Vertical", 4,(GLUI_Update_CB)vertical );
	glui->add_button_to_panel(obj_panel, "Horizontal", 4,(GLUI_Update_CB)horizontal );

	//Painel com as operações
	GLUI_Panel *obj_panel2 = glui->add_panel ( "Operacoes" );
	//Sub-painel para quantização
	GLUI_Panel *obj_panel3 = glui->add_panel_to_panel (obj_panel2, "Tons de Cinza" );
	GLUI_Spinner *segment_spinner = glui->add_spinner_to_panel(obj_panel3, "Qtd de tons de cinza",GLUI_SPINNER_INT, &segments );
	segment_spinner->set_int_limits( 1, 255, GLUI_LIMIT_WRAP );
	glui->add_button_to_panel(obj_panel3, "Quantizar", 4,(GLUI_Update_CB)quantizar );
	//Luminância
	glui->add_button_to_panel(obj_panel2, "Luminancia", 4,(GLUI_Update_CB)luminance );

	//Painel para Salvar
	GLUI_Panel *obj_panel4 = glui->add_panel ( "Salvar" );
	GLUI_EditText *edittext = glui->add_edittext_to_panel(obj_panel4, "Nome:", GLUI_EDITTEXT_TEXT, &text );
	glui->add_button_to_panel(obj_panel4, "OK", 4,(GLUI_Update_CB)salvar );

    glutMainLoop();

	
	return EXIT_SUCCESS;
}
