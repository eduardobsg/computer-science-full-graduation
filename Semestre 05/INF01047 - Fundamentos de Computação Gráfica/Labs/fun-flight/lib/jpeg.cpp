#include "jpeg.h"

//-----------------------------------------------------------------------------
// JPEGLIB routines for error handling
//-----------------------------------------------------------------------------
struct my_error_mgr 
{
 	struct jpeg_error_mgr pub; //"public" fields
	jmp_buf setjmp_buffer; //for return to caller
};

typedef struct my_error_mgr *my_error_ptr;

// Here's the routine that will replace the standard error_exit method
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


//-----------------------------------------------------------------------------
// Public Methods
//-----------------------------------------------------------------------------

// Contructor for the jpeg image
Jpeg::Jpeg()
{
	init();
}


// Contructor for the jpeg image
Jpeg::Jpeg(Jpeg* other) 
{
    init();
        
    if(other)
    {
        this->width = other->width;                
        this->height = other->height;
        this->size = other->size;
        this->channels = other->channels;
        this->filename = other->filename;
        this->data = new unsigned char [size];
        
        memcpy(data, other->data, size);  
	}
}


// Destructor of the jpeg image
Jpeg::~Jpeg() 
{
  	if(data)
	{
		delete [] ((unsigned char *)data);
		data = NULL;
	}
}


// Set the filename
void Jpeg::SetFilename(char *_filename)
{ 
	this->filename = (char*) malloc( strlen(_filename) + 1 );
	strcpy(this->filename, _filename); 
}


/* Write (creates) a JPEG image, based on the objects jpeg image. 
 * This function also establishes a compression quality, so the 
 * programmer can choose the quality he wants for the image that
 * will be created.
*/
bool Jpeg::WriteJpegFile(char *filename, int quality)
{
    // This struct contains the JPEG compression parameters and pointers to
    // working space (which is allocated as needed by the JPEG library).
    // It is possible to have several such structures, representing multiple
    // compression/decompression processes, in existence at once.  We refer
    // to any one struct (and its associated working data) as a "JPEG object".
    struct jpeg_compress_struct cinfo;

    // This struct represents a JPEG error handler. It is declared separately
    // because applications often want to supply a specialized error handler
    // (see the second half of this file for an example). But here we just
    // take the easy way out and use the standard error handler, which will
    // print a message on stderr and call exit() if compression fails.
    // Note that this struct must live as long as the main JPEG parameter
    // struct, to avoid dangling-pointer problems.
    struct jpeg_error_mgr jerr;
  
    // Target file 
    FILE *outfile;		
    
    // Pointer to JSAMPLE row[s] 
    JSAMPROW row_pointer[1];	
    
    // Physical row width in image buffer 
    int row_stride;		

    /* Step 1: allocate and initialize JPEG compression object */

    // We have to set up the error handler first, in case the initialization
    // step fails. (Unlikely, but it could happen if you are out of memory.)
    // This routine fills in the contents of struct jerr, and returns jerr's
    // address which we place into the link field in cinfo.
    cinfo.err = jpeg_std_error(&jerr);
  
    // Now we can initialize the JPEG compression object. 
    jpeg_create_compress(&cinfo);

    /* Step 2: specify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */

    // Here we use the library-supplied code to send compressed data to a
    // stdio stream. You can also write your own code to do something else.
    // VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
    // requires it in order to write binary files.
    if((outfile = fopen(filename, "wb")) == NULL) 
    {
        fprintf(stderr, "can't open %s\n", filename);
        return false;
    }
  
    jpeg_stdio_dest(&cinfo, outfile);

    /* Step 3: set parameters for compression */

    // First we supply a description of the input image.
    // Four fields of the cinfo struct must be filled in:
    cinfo.image_width = this->width;            // image width , in pixels 
    cinfo.image_height = this->height;          // image height, in pixels 
    cinfo.input_components = this->channels;	// Number of color components per pixel 
    cinfo.in_color_space = JCS_RGB; 	        // colorspace of input image 

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
  	/*         jpeg_write_scanlines(...); */

  	// Here we use the library's state variable cinfo.next_scanline as the
   	// loop counter, so that we don't have to keep track ourselves.
    // To keep things simple, we pass one scanline per call; you can pass
    // more if you wish, though.
    
  	row_stride = width * 3;	// JSAMPLEs per row in image_buffer

	while(cinfo.next_scanline < cinfo.image_height) 
	{
		// jpeg_write_scanlines expects an array of pointers to scanlines.
		// Here the array is only one element long, but you could pass
		// more than one scanline at a time if that's more convenient.
		row_pointer[0] = & data[cinfo.next_scanline * row_stride];
		(void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
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

/* Given the name of the image this function loads the image information
 * into the objects attibutes  	
*/
bool Jpeg::ReadJpegFile()
{
    // Source file
    FILE *pFile;                        
    
    // Output row buffer
    JSAMPARRAY pBuffer; 
                     
    // Physical row width in output buffer                 
    int nRowSize;                        
    
    struct my_error_mgr jerr;
    
    // This struct contains the JPEG decompression parameters and pointers to
    // working space (which is allocated as needed by the JPEG library).
    struct jpeg_decompress_struct cinfo;
    
    // If there is some image loaded, release it
    if(data)
    {    
       release();
    }
       
    // Try open file   
    if(!(pFile = fopen(this->filename,"rb")))
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

    // Load image info
    this->width = cinfo.output_width;
    this->height = cinfo.output_height;
    this->channels = cinfo.output_components;
    this->size = this->width * this->height * this->channels;    
    this->data = new unsigned char[this->size];

    int last_byte = size - nRowSize;

    while(cinfo.output_scanline < cinfo.output_height)
    { 
        jpeg_read_scanlines(&cinfo, pBuffer, 1); 
        
        if(last_byte >= 0)
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
// Protected Methods 
//-----------------------------------------------------------------------------

/* Initializes the jpeg object
*/
void Jpeg::init(void)
{
	this->width 	= 0;
	this->height 	= 0;
	this->data 		= NULL;
	this->size 		= 0;
	this->channels 	= 0;
	this->filename 	= NULL; 
}


/* Clear all the values of an exisisting jpeg object
*/
void Jpeg::release(void)
{
	if(this->data)
	{
		delete [] ((unsigned char *)this->data);
		this->data = NULL;
	}

	this->width = 0;
	this->height = 0;
	this->size = 0;
	this->channels = 0;
	this->filename 	= NULL;
}


/*

*/
void Jpeg::imageFlipUp(void)
{
	unsigned char *buffer = NULL;
    int line_up,line_down;
    int limiar;
    const int line_width = this->width * this->channels;
    
    if(height % 2)
	{
       limiar = (int)((this->height - 1) / 2);
    } 
	else 
	{
       limiar = (int)(this->height / 2);
    }

	buffer = new unsigned char[line_width];    
     
    line_down = this->size - line_width;
    line_up = 0;
    
    for(int i = 0; i < limiar; ++i)
	{        
        // copies the line to the buffer ascending to the middle of the image
        memcpy(buffer, this->data + line_up, line_width);
        memcpy(this->data + line_up, data + line_down, line_width);
        memcpy(this->data + line_down, buffer, line_width);
        
        line_up += line_width;
        line_down -= line_width;     
    }   

	delete [] buffer;
}


/* Mirrors the image: left <-> right
*/
void Jpeg::HorizontalMirroring()		
{
	int limite, col_aux, lin_aux, aux2;
	unsigned char buffer[3];
	
	if(this->width % 2 == 0)
		limite = this->width / 2;
	else 
		limite = (this->width - 1) / 2;

	for(int i = 0; i < this->height; i++)
	{	
		col_aux = (this->width * this->channels);
		lin_aux = col_aux * i;
		aux2 = 0;
		for(int j = 0; j < limite; j++)	
		{   
			// Follows the line pointing to its beggining and ending
			// and increment and decremente until the middle is reached
			col_aux -= this->channels;
			memcpy(buffer, this->data + lin_aux + aux2, this->channels);
			memcpy(this->data + lin_aux + aux2, this->data + lin_aux + col_aux, this->channels);
			memcpy(this->data + lin_aux + col_aux, buffer, this->channels);
			aux2 += this->channels;
		}	
	}
}

/* Mirrors the image: up <-> down
 * Mirroring switching line by line
*/
void Jpeg::VerticalMirroring()		
{
	unsigned char *buffer = NULL;
	int limite, bytes, colunas;

	bytes = (this->height * this->width * this->channels);	
	buffer = new unsigned char[this->width * 3]; 
 
	if(this->height % 2 == 0)
		limite = this->height / 2;
	else
		limite = (this->height - 1) / 2;
	
	colunas = 0;
	
	for(int i = 0; i < limite; i++)
	{
		bytes = bytes - this->width * this->channels;
		memcpy(buffer, this->data + colunas , this->width * this->channels);
		memcpy(this->data + colunas, this->data + bytes, this->width * this->channels);
		memcpy(this->data + bytes, buffer, this->width * this->channels);
		
		colunas += this->width * this->channels;
	}

	delete [] buffer;
}
