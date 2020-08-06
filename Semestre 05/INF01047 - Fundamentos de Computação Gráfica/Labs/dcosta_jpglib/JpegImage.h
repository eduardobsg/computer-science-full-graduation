
//-----------------------------------------------------------------------------
//        PRIMEIRA ETAPA DO TRABALHO DE FUNDAMENTOS DE PROCESSAMENTO DE IMAGENS 2010/2
//		  Prof. Dr. Manuel Menezes de Oliveira Neto
//        Nome: DIOGO COSTA
//        Cartão: 180188
//        Turma: A
//
//	   
//        Agradecimento ao colega Israel Andreis pelo fornecimento dessa biblioteca para ler e gravas imagens.
//
//-----------------------------------------------------------------------------

#ifndef __JPEG_IMAGE_H__
#define __JPEG_IMAGE_H__


#define RED     0
#define GREEN   1
#define BLUE    2

class JpegImage {

//-----------------------------------------------------------------------------
// Atributs
//-----------------------------------------------------------------------------
protected:
	int width;				// image width
    int height;				// image height
    int size;				// image size in bytes
    int channels;			// number of channels (RGB = 3 | RGBA = 4)
    unsigned char *data;	// pointer to bytes of image

//-----------------------------------------------------------------------------
// Methods
//-----------------------------------------------------------------------------
public:
    
	// Constructors
	JpegImage();							// init empty object	
	JpegImage( JpegImage* other );
	// Destructor
	
	~JpegImage();

	int getWidth(){ return width; }			
	int getHeight(){ return height; }		
	int getSize(){ return size; }			 
	int getChannels(){ return channels; }		 
    void *getImage(){ return data; } 
	
unsigned char getPixel( int linha, int coluna, int canal)
    {
        return data[(width * channels * linha) + (coluna * channels) + canal];
    }

unsigned char getPixel(int indice)
	{
		return data[indice];
	}

void setPixel(int i,int valor)
	{
		data[i] = valor;
	}
   
void setPixel( int linha, int coluna, int canal, unsigned char valor)
    {
        data[(width * channels * linha) + (coluna * channels) + canal] = valor;
    }
    

void espelhamento_vertical();

void quantizacao(int n_tons);
			
void luminancia();

void espelhamento_horizontal();

	// read jpeg image, return true if sucess or false if failure
bool readJpegFile(const char *filename);

// write jpeg image, return true if sucess or false if failure
    
bool writeJpegFile(const char *filename, int quality);
    
protected:       
	void init( void );
	void release( void );
    void imageFlipUp( void );
};

#endif

