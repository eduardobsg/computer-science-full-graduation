#include <cstdio>
#include <cstring>
#include "JpegImage.h"
#include "jpeglib.h"

// is used for the optional error recovery mechanism
#include <setjmp.h>

//-----------------------------------------------------------------------------
// JPEGLIB routines for error handling
//-----------------------------------------------------------------------------
struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	    /* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}


/******************************************************************************/
/*  JpegImage Implementation                                                  */ 
/******************************************************************************/
//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------
JpegImage::JpegImage()
{
	init();
}

//-----------------------------------------------------------------------------
// destructor
//-----------------------------------------------------------------------------
JpegImage::~JpegImage() 
{
  	if ( data )
	{
		delete [] ((unsigned char *)data);
		data = NULL;
	}
}

//-----------------------------------------------------------------------------
// public methods
//-----------------------------------------------------------------------------
bool JpegImage::writeJpegFile(const char *filename, int quality)
{
    // This struct contains the JPEG compression parameters and pointers to
    // working space (which is allocated as needed by the JPEG library).
    // It is possible to have several such structures, representing multiple
    // compression/decompression processes, in existence at once.  We refer
    // to any one struct (and its associated working data) as a "JPEG object".
    struct jpeg_compress_struct cinfo;

    // This struct represents a JPEG error handler.  It is declared separately
    // because applications often want to supply a specialized error handler
    // (see the second half of this file for an example).  But here we just
    // take the easy way out and use the standard error handler, which will
    // print a message on stderr and call exit() if compression fails.
    // Note that this struct must live as long as the main JPEG parameter
    // struct, to avoid dangling-pointer problems.
    struct jpeg_error_mgr jerr;
  
    // target file 
    FILE * outfile;		
    
    // pointer to JSAMPLE row[s] 
    JSAMPROW row_pointer[1];	
    
    // physical row width in image buffer 
    int row_stride;		

    /* Step 1: allocate and initialize JPEG compression object */

    // We have to set up the error handler first, in case the initialization
    // step fails.  (Unlikely, but it could happen if you are out of memory.)
    // This routine fills in the contents of struct jerr, and returns jerr's
    // address which we place into the link field in cinfo.
    cinfo.err = jpeg_std_error(&jerr);
  
    // Now we can initialize the JPEG compression object. 
    jpeg_create_compress(&cinfo);

    /* Step 2: specify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */

    // Here we use the library-supplied code to send compressed data to a
    // stdio stream.  You can also write your own code to do something else.
    // VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
    // requires it in order to write binary files.
    if ((outfile = fopen(filename, "wb")) == NULL) 
    {
        fprintf(stderr, "can't open %s\n", filename);
        return false;
    }
  
    jpeg_stdio_dest(&cinfo, outfile);

    /* Step 3: set parameters for compression */

    // First we supply a description of the input image.
    // Four fields of the cinfo struct must be filled in:
    cinfo.image_width = width; 	            // image width , in pixels 
    cinfo.image_height = height;            // image height, in pixels 
    cinfo.input_components = channels;		// Number of color components per pixel 
    cinfo.in_color_space = JCS_RGB; 	    // colorspace of input image 

  
    // Now use the library's routine to set default compression parameters.
    // (You must set at least cinfo.in_color_space before calling this,
    // since the defaults depend on the source color space.)
    jpeg_set_defaults(&cinfo);
  
    // Now you can set any non-default parameters you wish to.
    // Here we just illustrate the use of quality (quantization table) scaling:
    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

    /* Step 4: Start compressor */

    // TRUE ensures that we will write a complete interchange-JPEG file.
    // Pass TRUE unless you are very sure of what you're doing.
    jpeg_start_compress(&cinfo, TRUE);

imageFlipUp();
  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
  row_stride = width * 3;	/* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    row_pointer[0] = & data[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

    /* Step 6: Finish compression */
    
    
imageFlipUp();    
    jpeg_finish_compress(&cinfo);
    
    // After finish_compress, we can close the output file. 
    fclose(outfile);
    
    /* Step 7: release JPEG compression object */
    
    // This is an important step since it will release a good deal of memory.
    jpeg_destroy_compress(&cinfo);
    
    // write SUCESSFULL
    return true;     
}

bool JpegImage::readJpegFile(const char *filename)
{
    // source file
    FILE * pFile;                        
    
    // output row buffer
    JSAMPARRAY pBuffer; 
                     
    // physical row width in output buffer                 
    int nRowSize;                        
    
    struct my_error_mgr jerr;
    
    // This struct contains the JPEG decompression parameters and pointers to
    // working space (which is allocated as needed by the JPEG library).
    struct jpeg_decompress_struct cinfo;
    
    // if there is some image loaded, release it
    if ( data )
    {    
       release();
    }
       
    // try open file   
    if (!(pFile = fopen(filename,"rb")))
       return false; 
        
    /* Step 1: allocate and initialize JPEG decompression object */    
    /* We set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;
    
    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) 
    {
        // JPEG code has signaled an error.
        // clean up the JPEG object, close the input file, and return.
        jpeg_destroy_decompress(&cinfo);
        fclose(pFile);
        return false;
    }
    
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, pFile);
    jpeg_read_header(&cinfo, TRUE); 
    jpeg_start_decompress(&cinfo);
     
    nRowSize = cinfo.output_width * cinfo.output_components;
    
    pBuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, nRowSize, 1);

    // load image info
    width = cinfo.output_width;
    height = cinfo.output_height;
    channels = cinfo.output_components;
    size = width * height * channels;    
    data = new unsigned char[size];

    int last_byte = size - nRowSize;

    while (cinfo.output_scanline < cinfo.output_height)
    { 
        jpeg_read_scanlines(&cinfo, pBuffer, 1); 
        
        if (last_byte >= 0)
        {
            memcpy(data + last_byte, pBuffer[0],(sizeof(unsigned char)*nRowSize));
            last_byte -= nRowSize;
        }
    } 
    
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(pFile);

    return true;   
}

//-----------------------------------------------------------------------------
// protected methods 
//-----------------------------------------------------------------------------
void JpegImage::init( void )
{
	width = 0;
	height = 0;
	data = NULL;
	size = 0;
	channels = 0;
}

void JpegImage::release( void )
{
	if ( data )
	{
		delete[] ((unsigned char *)data);
		data = NULL;
	}

	width = 0;
	height = 0;
	size = 0;
	channels = 0;
}

void JpegImage::imageFlipUp( void )
{
	unsigned char *buffer = NULL;
    int line_up,line_down;
    int limiar;
    int i;
    const int line_width = width * channels;
    
    if (height % 2)
	{
       limiar = (int)((height - 1) / 2);
    } 
	else 
	{
       limiar = (int)(height / 2);
    }

	buffer = new unsigned char[line_width];    
     
    line_down = size - line_width;
    line_up = 0;
    
    for (i = 0; i < limiar; ++i)
	{        
        // copia linha para o buffer em ordem crescente ate o meio da imagem
        memcpy(buffer, data + line_up, line_width);
        memcpy(data + line_up, data + line_down, line_width);
        memcpy(data + line_down, buffer, line_width);
        
        line_up += line_width;
        line_down -= line_width;     
    }   

	delete [] buffer;
}

void JpegImage::espelhamento_horizontal()		//Espelha a imagem: esquerda <-> direita
{
	int limite, tam_linha, tam_coluna, bytes, i, j, colunas, col_aux, lin_aux, aux2;
	unsigned char buffer[3];
	tam_linha = height;
	tam_coluna = width;
	
	if(tam_coluna % 2 == 0)
		limite = tam_coluna / 2;
	else 
		limite = (tam_coluna - 1) / 2;

	for(i = 0; i < tam_linha; i++)
	{	
		col_aux = (tam_coluna * channels);
		lin_aux = col_aux * i;
			
		aux2 = 0;
		for(j = 0; j < limite; j++)			//Percorre a linha apontando para o inicio da linha e para o final e incrementando e decrementando ate chegar ao meio
		{
			col_aux -= channels;
			memcpy(buffer, data + lin_aux + aux2, channels);
			memcpy(data + lin_aux + aux2, data + lin_aux+ col_aux , channels);
			memcpy(data + lin_aux+ col_aux, buffer, channels);
		
			aux2 +=channels;
		}
		
	}
}

void JpegImage::luminancia()		//Equacao aplicada segundo a definição do trabalho
{
	int value1, value2, value3;
	int L=0, ind=0;

	if(channels == 3)
	{
		for(ind = 0 ; ind < (height * width * channels); ind+=3)
		{	
			value1 = data[ind];
			value2 = data[ind+1];
			value3 = data[ind+2];


			L = 0.299 * value1 + 0.587 * value2 + 0.114* value3; 
	
			data[ind] = L;
			data[ind+1] = L;
			data[ind+2] = L;
		}
	}
}

void JpegImage::quantizacao(int n_tons)		//Divido em conjuntos e troco o pixel pelo ponto médio do conjunto ao qual ele pertence
{
	int value1, value2, value3;
	int aux=0, ind=0;

	for(ind = 0 ; ind < (height * width * channels); ind+=channels)
	{	
		
		for(aux = (int) 255 / n_tons; aux <=255; aux += 255 / n_tons)
		{
			if(data[ind] > (aux - (int) 255 / n_tons) && data[ind] < aux)
			{
				if(aux+ 255 / n_tons  > 255)
				{
					value1 = (255 +  (int) 255 / n_tons) / 2;
					data[ind] = value1;
					data[ind+1] = value1;
					data[ind+2] = value1;
				
				}
				else 
				{
					value1 = (aux + aux -  (int) 255 / n_tons) / 2;
					data[ind] = value1;
					data[ind+1] = value1;
					data[ind+2] = value1;
				
				}
			}
		}
 		
	}
}

void JpegImage::espelhamento_vertical()		//Espelhando trocando linha por linha
{
	unsigned char *buffer = NULL;
	int limite, tam_linha, tam_coluna, bytes, i, colunas;
	bytes = (height * width * channels);
	
	tam_linha = height;
	tam_coluna = width;
	buffer = new unsigned char[tam_coluna*3]; 
 
	if(tam_linha % 2 == 0)
		limite = tam_linha / 2;
	else
		limite = (tam_linha - 1) / 2;
	
	colunas = 0;
	for(i = 0; i < limite; i++)
	{
		bytes = bytes - tam_coluna*channels;
		memcpy(buffer, data + colunas , tam_coluna*channels);
		memcpy(data+colunas, data + bytes, tam_coluna*channels);
		memcpy(data+bytes, buffer, tam_coluna*channels);
		
		colunas += tam_coluna*channels;
	}

		delete [] buffer;
}

JpegImage::JpegImage( JpegImage* other )			//Construtor, passa um vetor para outro
{
    init();
        
    if (other)
    {
        width = other->width;                
        height = other->height;
        size = other->size;
        channels = other->channels;
        data = new unsigned char [ size ];
        
        memcpy( data, other->data, size );  
	}
}
