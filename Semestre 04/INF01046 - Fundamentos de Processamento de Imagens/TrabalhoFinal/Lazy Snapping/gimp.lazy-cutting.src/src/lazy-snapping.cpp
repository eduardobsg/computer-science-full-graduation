#include "lazy-snapping.h"


/*
 * Constructor
 * img_ID: id of the image
 * draw_ID: id of the drawabale
 */
LazySnapping::LazySnapping(gint32 img_ID, gint32 draw_ID, gint32 lay_ID):weightFactor(__default__weightFactor__),
									 colorFactor(__default__colorFactor__),
									 gui(new GUI()),
									 image_ID(img_ID), 
									 drawable_ID(draw_ID), 
									 layer_ID(lay_ID),
									 graph(new Graph()),
									 bg_input(Pixels()), 
									 fg_input(Pixels()),
									 kmean(KMeans<_k,_dim, float>())
{
  // define bg_color and fg_color
  bg_color[0] = 255; bg_color[1] = 255; bg_color[2] = 0;
  fg_color[0] = 255; fg_color[1] = 0; fg_color[2] = 0;
    
  bg_centroids = new guchar[_dim];
  fg_centroids = new guchar[_dim];
  
  lazySnapping = this;
}



LazySnapping::~LazySnapping()
{
	delete[] fg_centroids;
	delete[] bg_centroids;
}


  
/*
 * Run lazy-snapping
 */
void  LazySnapping::run()
{
  input_layer = add_layer("InputLayer");
  start_GUI();
}


/*
 * Callback function for the run button
 */
void LazySnapping::run_Button_Callback(GtkWidget* button)
{
  cout << "Running lazySnapping with: weightFactor: " << lazySnapping->weightFactor << " and colorFactor: " << lazySnapping->colorFactor << endl;

  lazySnapping->process_input(lazySnapping->input_layer);

  lazySnapping->getCentroids();
  lazySnapping->computeMaxFlow(lazySnapping->input_layer);
  
    
  //lazySnapping->extractFG();
  
  //lazySnapping->extractFGToMask("TEST");
  
}


/*
 * Compute the maxflow and add extract the solution 
 * to the mask 
 */

void  LazySnapping::computeMaxFlow(gint32 layer)
{
  time_t a,b;
  a = time(NULL);
  build_graph(input_layer);
  b = time(NULL);
  cout << "build_graph took " << b-a << " seconds\n";
  graph->maxflow();

  lazySnapping->extractFGToMask();
  //lazySnapping->extractFG("build_graph");
  
  //createGraph(input_layer);
  a = time(NULL);
  cout << "createGraph took " << a-b << " seconds\n";
  //graph->maxflow();
  //lazySnapping->extractFG("createGraph");
}




/*
 * Create the graph for graph cut algorithm
 * First a very simple and very unefficent implementation
 *
 */  

void  LazySnapping::createGraph(gint32 layer)
{
  GimpDrawable* image_drawable;
  GimpDrawable* layer_drawable;

  
  image_drawable = gimp_drawable_get(drawable_ID);
  layer_drawable = gimp_drawable_get(layer);
  
  // Compute number of nodes used for the graph
  unsigned int nrNodes = image_drawable->height * image_drawable->width;
  

  nodes = new Graph::node_id[nrNodes];
  
  
  // init nodes
  for(unsigned int i = 0; i < nrNodes; i++)
    nodes[i] = graph->add_node();
  

    
  // Connect each node with source and sink     
  GimpPixelRgn src_layer, src_image;
  
  gimp_pixel_rgn_init(&src_layer, layer_drawable,
		      0, 0,
		      layer_drawable->width,
		      layer_drawable->height,
		      FALSE, FALSE);

  gimp_pixel_rgn_init(&src_image, image_drawable,
		      0, 0,
		      image_drawable->width, image_drawable->height,
		      FALSE, FALSE);

  guchar* imgPtr;
  guchar* layPtr;

  assert(image_drawable->width == layer_drawable->width);
  
  guchar* image_row = new guchar[image_drawable->bpp * image_drawable->width];
  guchar* layer_row = new guchar[layer_drawable->bpp * layer_drawable->width];
    

  Graph::node_id* itNode = nodes;
  
  const Graph::captype inf = numeric_limits<Graph::captype>::max();

  float minfg, minbg;
  //unsigned char minfg, minbg;

  // LIKELIHOOD ENERGY computation
  for (unsigned int i = 0; i < image_drawable->height; i++){

    gimp_pixel_rgn_get_row(&src_layer, layer_row, 0, i, layer_drawable->width);
    gimp_pixel_rgn_get_row(&src_image, image_row, 0, i, image_drawable->width);

    layPtr = layer_row;
    imgPtr = image_row;      
      

    for(unsigned int k = 0; k < image_drawable->width; k++, layPtr += src_layer.bpp, imgPtr += src_image.bpp, itNode++){
	
      // is the selected pixel member of the background?
      if((layPtr[0] == bg_color[0]) && (layPtr[1] == bg_color[1]) && (layPtr[2] == bg_color[2])){
	  
	graph->set_tweights(*itNode, inf, 0);	
	  
	// is the selected pixel member of the foreground?
      }else if((layPtr[0] == fg_color[0]) && (layPtr[1] == fg_color[1]) && (layPtr[2] == fg_color[2])){
	
	graph->set_tweights(*itNode, 0, inf);

	// the pixel belongs to the unknown region
      }else{
	minfg = min_fg(imgPtr);
	minbg = min_bg(imgPtr);
	
	Graph::captype fgEnergy, bgEnergy;
	//unsigned char fgEnergy, bgEnergy;
	fgEnergy = (Graph::captype)(minfg / (minbg + minfg));
	bgEnergy = (Graph::captype)(minbg / (minfg + minbg));

	//fgEnergy = 0.5; bgEnergy = 0.5; // Debuging, ignores color information
	graph->set_tweights(*itNode, fgEnergy, bgEnergy);
	
      }
    }

  }
    
  // PRIOR ENERGY computation:
  // Connect adjacent pixels with each other 

  /* Traverse all rows and connect the adjacent pixels 
   * with each other:
   *
   *  p - p - p - p (row 1)
   *
   *  p - p - p - p (row 2)
   */   
 
  itNode = nodes;
  
  for (unsigned int i = 0; i < image_drawable->height; i++, itNode++){

    gimp_pixel_rgn_get_row(&src_image, image_row, 0, i, image_drawable->width);
    
    imgPtr = image_row;
      
    for (unsigned int k = 0; k < image_drawable->width-1; k++,itNode++, imgPtr += src_image.bpp){
	
      float rgbDist = colorDistanceSq(imgPtr, imgPtr + src_image.bpp, 3);
      float weight = 1/(rgbDist + 1);
      graph->add_edge(*itNode, *(itNode+1), weight, weight);
    }    
  }

  
  /* Traverse all columns and connect the adjacent pixels 
   * with each other:
   *
   *  p - p - p - p (row 1)
   *  |   |   |   |
   *  p - p - p - p (row 2)
   */

  guchar* image_col = new guchar[image_drawable->height * image_drawable->bpp];
  
  itNode = nodes;
  Graph::node_id* itNode2 = nodes;
  
  for (unsigned int i = 0; i < image_drawable->width; i++, itNode++){
      
    gimp_pixel_rgn_get_col(&src_image, image_col, i, 0, image_drawable->height);
    
    itNode2 = itNode;

    imgPtr = image_col;

    for (unsigned int k = 0; k < image_drawable->height-1; k++, itNode2 += image_drawable->width, imgPtr += src_image.bpp){

      float rgbDist = colorDistanceSq(imgPtr, imgPtr + src_image.bpp, 3);
      float weight = 1/(rgbDist + 1);

      graph->add_edge(*itNode2, *(itNode2 + image_drawable->width), weight, weight);
    }  
  }
    
  // Free all allocated memory memory
  //delete[] image_row;
  //delete[] layer_row;
  //delete[] image_col;
}
  

/***** FUNCTIONS USED FOR THE PRIOR ENERGY COMPUTATION ********************/
 
 
/* Compute distance between two crgb colors
 *
 * return: returns the SQUARED distance
 */

float LazySnapping::colorDistanceSq(guchar* c1, guchar* c2, int dim)
{
  float result = 0;
  for (int i = 0; i < dim; i++){
    result += (c1[i]-c2[i])*(c1[i]-c2[i]);
  }
  return result;
}



/***** FUNCTIONS USED FOR THE LIKELIHOOD ENERGY COMPUTATION ***************/

/*
 * Compute min distance to FOREGROUND CENTROIDS
 * color: the rgb color to which the distance should be computed
 * return: minimum distance
 */

float LazySnapping::min_fg(guchar* color)
{
  if (fg_centroids != 0)
    return minCentroidDistance(color, fg_centroids, 3);
  else
    return 0;
}



/*
 * Compute min distance to BACKGROUND CENTROIDS
 * color: the rgb color, to which the distance should be computed
 * return: minimum distance
 */

float LazySnapping::min_bg(guchar* color)
{
  if (bg_centroids != 0)
    return minCentroidDistance(color, bg_centroids, 3);
  else
    return 0;
}


/* Compute min distance to the centroids, given a color
 * color: a rgb color 
 * centroids: a rgb color vector
 * retrun: the minimum distance betweeb the rgb color and the centroid
 */
float LazySnapping::minCentroidDistance(guchar* color, guchar* centroids, int dim)
{    
	float min = distance(color, centroids, dim);
	float tmpMin;
	for (unsigned int i = dim; i < _dim; i += dim){
		tmpMin = distance(color, centroids+i, dim);
		if (tmpMin < min)
			min = tmpMin;
	}
	return sqrt(min);
}


/*
 * Compute the square of the euclidien distance between two points
 *
 * c1: rgb color as array of guchar
 * c2: rgb color as array of guchar
 * dim: the dimension of the color
 * return: euclidien distance squared
 */
float LazySnapping::distance(const guchar* c1, const guchar* c2, int dim)
{ 
	float result = 0;
	
	for (int i = 0; i < dim; i++)
	{
		result += ((float)c1[i] - c2[i])*((float)c1[i] - c2[i]);
	}
	
	return result;    
}


/* For the moment copy foreground to new layer*/
void LazySnapping::extractFG(gchar* name)
{
  // Get new layer
  gint32 layer = add_layer(name);
  
  GimpDrawable* image_drawable;
  GimpDrawable* layer_drawable;
  
  image_drawable = gimp_drawable_get(drawable_ID);
  layer_drawable = gimp_drawable_get(layer);
  

  GimpPixelRgn dest_layer, src_image;

  gimp_pixel_rgn_init(&dest_layer, layer_drawable,
		      0, 0,
		      layer_drawable->width,
		      layer_drawable->height,
		      TRUE, TRUE);
  
  gimp_pixel_rgn_init(&src_image, image_drawable,
		      0, 0,
		      image_drawable->width, 
		      image_drawable->height,
		      FALSE, FALSE);
  
  guchar* image_row = new guchar[image_drawable->bpp * image_drawable->width];
  guchar* layer_row = new guchar[layer_drawable->bpp * layer_drawable->width];
  
  guchar* imgPtr; 
  guchar* layPtr;

  Graph::node_id* nodeIt = nodes;

  for (unsigned int i = 0; i < image_drawable->height; i++){
    gimp_pixel_rgn_get_row(&src_image, image_row, 0, i, image_drawable->width);

    imgPtr = image_row;
    layPtr = layer_row;

    for (unsigned int k = 0; k < image_drawable->width; k++, imgPtr += image_drawable->bpp, layPtr += layer_drawable->bpp, nodeIt++){
      
      layPtr[3] = 0; //set alpha value

      if (graph->what_segment(*nodeIt) == Graph::SINK){
	
	layPtr[0] = imgPtr[0]; 
	layPtr[1] = imgPtr[1]; 
	layPtr[2] = imgPtr[2];
	layPtr[3] = 255; //set alpha value
	}
      
    }
    
    gimp_pixel_rgn_set_row(&dest_layer, layer_row, 0, i, layer_drawable->width);
    
  }
  
  gimp_drawable_flush(layer_drawable);
  gimp_drawable_merge_shadow (layer, TRUE);
  gimp_displays_flush();
  
  /* Detach drawables*/
  gimp_drawable_detach(layer_drawable);
  gimp_drawable_detach(image_drawable);
}


void LazySnapping::extractFGToMask()
{
  // Clear the old selection
  gimp_selection_clear(image_ID);

  GimpDrawable* image_drawable;
  GimpDrawable* mask_drawable;

  gint32 layer_mask_ID;
  
  layer_mask_ID = gimp_layer_get_mask(layer_ID);

  // If mask does not exist create one and attache it to the layer
  if (layer_mask_ID == -1){
    layer_mask_ID = gimp_layer_create_mask(layer_ID, GIMP_ADD_WHITE_MASK); 

    gimp_layer_add_mask(layer_ID, layer_mask_ID);
  }

  // Get drawables
  image_drawable = gimp_drawable_get(drawable_ID);
  mask_drawable   = gimp_drawable_get(layer_mask_ID);
  
  //cout << "Mask width: " << mask_drawable->width << " heigh: " << mask_drawable->height << " bpp:" << mask_drawable->bpp << endl;
  //cout << "Image width: " << image_drawable->width << " heigh: " << image_drawable->height << " bpp:" << image_drawable->bpp << endl;

  GimpPixelRgn mask_rgn;

  gimp_pixel_rgn_init(&mask_rgn, mask_drawable,
		      0, 0,
		      mask_drawable->width,
		      mask_drawable->height,
		      TRUE, TRUE);

  // Create a pixel row for the image and for the mask
  guchar* mask_row  = new guchar[mask_drawable->bpp * image_drawable->width];

  // Define iterator pointers
  guchar* maskPtr;
  
  Graph::node_id* nodeIt = nodes;

  // Iterate over all rows
  for(unsigned int i = 0; i < image_drawable->height; i++){
    maskPtr = mask_row;
    
    for(unsigned int k = 0; k < image_drawable->width; k++, maskPtr += mask_drawable->bpp, nodeIt++){
      // Set the alpha value
      maskPtr[0] =  (graph->what_segment(*nodeIt) == Graph::SINK)? 255: 0;
    }

    // Write it to the mask
    gimp_pixel_rgn_set_row(&mask_rgn, mask_row, 0, i, mask_drawable->width);    
  }
  
  
  gimp_drawable_flush(mask_drawable);
  gimp_drawable_merge_shadow(layer_mask_ID, TRUE);

  gimp_layer_set_edit_mask (layer_ID, FALSE);

  bool done = gimp_selection_load(layer_mask_ID);

  if(done)
    cout << "Loaded channel to selection mask!" << endl;
  else
    cout << "Loading failed!" << endl;


  // When making a selection the foreground is active
  if(!active_fg)
    gimp_selection_invert(image_ID);


  gimp_layer_set_apply_mask(layer_ID, FALSE);

  gimp_displays_flush();

  // Delete allocated rows
  delete[] mask_row;

  // Detach drawable
  gimp_drawable_detach(mask_drawable);  
}


/* 
 * Computes the centroids of foreground 
 * and background
 */
void LazySnapping::getCentroids()
{
  Pixels bg_centroidVec = vector<float>(_k*_dim, 0);
  Pixels fg_centroidsVec = vector<float>(_k*_dim, 0);
  cout << "Get Centroids" << endl;
  
  //printVector(bg_input);
  if (bg_input.size() != 0)
    kmean.computeKMeans(bg_input, bg_centroidVec);
  
  //printVector(bg_centroidVec, "Background Centroids");

  if (fg_input.size() != 0)
    kmean.computeKMeans(fg_input, fg_centroidsVec);
  
  //printVector(fg_centroidsVec, "Foreground Centroids");
  
  int i = 0;
  for (Iterator it = bg_centroidVec.begin(); it != bg_centroidVec.end(); it++, i++)
    {
      bg_centroids[i] = (guchar)*it;
    }
  i = 0;
  for (Iterator it = fg_centroidsVec.begin(); it != fg_centroidsVec.end(); it++, i++)
    {
	  fg_centroids[i] = (guchar)*it;
    }
  
  //printVector(bg_centroidVec);
}



/*
 * Get user input from layer
 * layer: id of layer
 */

void LazySnapping::process_input(gint32 layer)
{
  cout << "Process input: " << endl;
  GimpDrawable* layer_drawable;
  GimpDrawable* image_drawable;
  
  GimpPixelRgn src_layer, src_image;
  
  layer_drawable = gimp_drawable_get(layer);
  image_drawable = gimp_drawable_get(lazySnapping->drawable_ID);
    
  gpointer ptr;

  gimp_pixel_rgn_init(&src_layer, layer_drawable, 
		      0, 0,
		      layer_drawable->width,
		      layer_drawable->height,
		      FALSE, FALSE);
  
  gimp_pixel_rgn_init(&src_image, image_drawable,
		      0, 0,
		      image_drawable->width,
		      image_drawable->height,
		      FALSE, FALSE);
  
  assert(src_image.bpp >= 3);
  guchar rgb[3];
  guchar* src;
  guchar* dest;
  
  // Clear fg_input and bg_input
  fg_input.clear();
  bg_input.clear();
  
  for(ptr = gimp_pixel_rgns_register(2, &src_layer, &src_image); ptr != NULL; ptr = gimp_pixel_rgns_process(ptr)){
    src = src_layer.data;
    dest = src_image.data;
    
    
    int size = src_layer.w * src_layer.h;
      
    //cout << "layer bpp: " << src_layer.bpp << "image bpp " << src_image.bpp << endl;
    
    for (int k = 0; k < size; k++, src+= src_layer.bpp, dest += src_image.bpp){
      rgb[0] = src[0];
      rgb[1] = src[1];
      rgb[2] = src[2];
      
      if ((rgb[0] == bg_color[0])&& (rgb[1] == bg_color[1]) && 
	  (rgb[2] == bg_color[2])){
	
	
	bg_input.push_back((float)dest[0]);
	bg_input.push_back((float)dest[1]);
	bg_input.push_back((float)dest[2]);


      } else if ((rgb[0] == fg_color[0]) && (rgb[1] == fg_color[1]) && 
		 (rgb[2] == fg_color[2])){
	
	fg_input.push_back((float)dest[0]);
	fg_input.push_back((float)dest[1]);
	fg_input.push_back((float)dest[2]);
	

      } else {
	  //cout << "Unknown color! " << endl;
      }
      
    }
    
  }    
}



/*
 * Get user input from layer
 */
#define scaleFactor	0x00ffffff
#define infinity	0xefffffff
// I created two variable called weightFactor, and colorFactor
// They both can be changed through the GUI on the advanced page
// The default values are 64 and 0.5

//#define weightFactor 64 
//#define colorFactor 0.5
void LazySnapping::build_graph(gint32 layer)
{
    cout << "Build Graph: " << endl;
    GimpDrawable* layer_drawable;
    GimpDrawable* image_drawable;
    
    GimpPixelRgn src_layer, src_image;
	
    layer_drawable = gimp_drawable_get(layer);
    image_drawable = gimp_drawable_get(lazySnapping->drawable_ID);
    
    gpointer ptr;
    
    gimp_pixel_rgn_init(&src_layer, layer_drawable, 
						0, 0,
						layer_drawable->width,
						layer_drawable->height,
						FALSE, FALSE);
    
    gimp_pixel_rgn_init(&src_image, image_drawable,
						0, 0,
						image_drawable->width,
						image_drawable->height,
						FALSE, FALSE);
	
    // Graph setup
    unsigned int graphDimension = image_drawable->width*image_drawable->height;
    nodes = new Graph::node_id[graphDimension];
    graph = new Graph();
	
    for (unsigned int i = 0; i < graphDimension; i++)
	{
		nodes[i] = graph->add_node();
	}
    
    // Add interconnections
    // Problem: Energy depends on assignment
    gint numChan = image_drawable->bpp;
    unsigned int posX, posY, posIdx;
    Graph::captype cap;
    guint8 ** dataLineCache = new guint8*[image_drawable->width];
    guint8 ** dataColumnCache = new guint8*[image_drawable->height];
	//memset(dataLineCache, 0, image_drawable->width);
	//memset(dataColumnCache, 0, image_drawable->height);
    for (unsigned int i = 0; i < image_drawable->width; i++)
		dataLineCache[i] = NULL;
    for (unsigned int i = 0; i < image_drawable->height; i++)
		dataColumnCache[i] = NULL;
    
    for(ptr = gimp_pixel_rgns_register(2, &src_layer, &src_image); ptr != NULL; ptr = gimp_pixel_rgns_process(ptr))
	{
		guchar * userInput = src_layer.data;
		guchar * dataInput = src_image.data;
		unsigned int numPixel = src_image.w*src_image.h;
		for (unsigned int i = 0; i < numPixel; i++, userInput += src_layer.bpp, dataInput += src_image.bpp)
		{
			posX = src_image.x + i%src_image.w;
			posY = src_image.y + i/src_image.w;
			posIdx = posX + posY*image_drawable->width;
			
			if ((userInput[0] == lazySnapping->bg_color[0]) && (userInput[1] == lazySnapping->bg_color[1]) && 
				(userInput[2] == lazySnapping->bg_color[2]))
			{
				graph->set_tweights(nodes[posIdx], infinity, 0);
			}
			else if ((userInput[0] == lazySnapping->fg_color[0]) && (userInput[1] == lazySnapping->fg_color[1]) && 
					 (userInput[2] == lazySnapping->fg_color[2]))
			{
				graph->set_tweights(nodes[posIdx], 0, infinity);
			}
			else
			{
				// Calculate weight
				float sDist, dDist;
				sDist = min_fg(dataInput);
				dDist = min_bg(dataInput);
				Graph::captype sEnergy, dEnergy;
				sEnergy = (Graph::captype)(scaleFactor * (sDist / (sDist + dDist)*colorFactor + (1-colorFactor)*0.5) );
				dEnergy = (Graph::captype)(scaleFactor * (dDist / (sDist + dDist)*colorFactor + (1-colorFactor)*0.5) );
				//sEnergy = 0.5*scaleFactor; dEnergy = 0.5*scaleFactor; // Fixed
				graph->set_tweights(nodes[posIdx], sEnergy, dEnergy);
				
			}
			
			if (dataLineCache[posX])
			{
				cap = weightFactor*(Graph::captype)(scaleFactor * 1/ (1 + colorDistance(dataInput, dataLineCache[posX], numChan)));
				graph->add_edge(nodes[posIdx], nodes[posIdx-image_drawable->width], cap, cap); // Link to up
			}
			else
			{
				dataLineCache[posX] = new guint8[numChan];
			}
			if (dataColumnCache[posY])
			{
				cap = weightFactor*(Graph::captype)(scaleFactor * 1/ (1 + colorDistance(dataInput, dataColumnCache[posY], numChan)));
				graph->add_edge(nodes[posIdx], nodes[posIdx-1], cap, cap); // Link to left
			}
			else
			{
				dataColumnCache[posY] = new guint8[numChan];
			}
			// Fixed
			memcpy(dataLineCache[posX], dataInput, numChan);
			memcpy(dataColumnCache[posY], dataInput, numChan);
		}
		//cout << "Region (" << src_image.x << "," << src_image.y << ") Completed" << endl;
	}
    cout << "Graph Completed" << endl;
	for (unsigned int i = 0; i < image_drawable->width; i++)
	{
		delete[] dataLineCache[i];
	}
	for (unsigned int i = 0; i < image_drawable->height; i++)
	{
		delete[] dataColumnCache[i];
	}
	delete[] dataLineCache;
	delete[] dataColumnCache;
}


/*
 * Create a transparent layer and add it to the image.
 * name: name of the layer
 * Returns: id of the layer
 */

gint32 LazySnapping::add_layer(gchar* name)
{
  
  gboolean done;
  gint32 layer;
  
  gint width, height;
  
  width = gimp_image_width(image_ID);
  height = gimp_image_height(image_ID);
    
  // Create layer
  layer = gimp_layer_new(image_ID,
			 name,
			 width,
			 height,
			 GIMP_RGBA_IMAGE,
			 100,
			 GIMP_NORMAL_MODE);
  
  // Make layer transparent
  done = gimp_drawable_fill(layer, GIMP_TRANSPARENT_FILL); 
  
  if (!done)
    cout << "Failed to make layer transparent!" << endl;
  
  // Add the layer to image
  done = gimp_image_add_layer(image_ID,
			      layer,
			      -1);
  if (!done)cout << "Could not add layer: " << name << endl;
  else cout << "Added layer: " << name << ", ID: " << layer << endl;
  
  // Make layer visible
  //gimp_layer_set_show_mask(layer, FALSE);
  
  return layer;    
}

  
/*
 * Start GUI
 */
void LazySnapping::start_GUI()
{
  /* Register callback function */
  gui->register_run_function(&run_Button_Callback);

  gui->register_fg_active_function(&activate_fg);
  gui->register_bg_active_function(&activate_bg);

  gui->register_reset_function(&reset_action);
  gui->register_ok_function(&termination_action);
  
  gui->register_weightFactor(&weightFactor);
  gui->register_colorFactor(&colorFactor);

  gui->set_foreground_marking_color(fg_color);
  gui->set_background_marking_color(bg_color);
    
  gui->init();
  gui->run();
    
}


  
/*
 * Make the pen the default for makring foreground and background
 */
/*
void lazySnapping::setDefaultMarkingTool()
{


}
*/
  
void LazySnapping::printVector(vector<float>& v, const char* com)
{
  cout << com << v.size() << endl;
  for (unsigned int i = 0; i < v.size(); i+=3){
    cout << (int)v[i] << ", " << (int)v[i+1] << ", " << (int)v[i+2] << endl;
    
  }
  
}

void LazySnapping::printVector(vector<unsigned char>& v)
{
	cout << "Print Vector of size: " << v.size() << endl;
	for (unsigned int i = 0; i < v.size(); i+=3){
		cout << (int)v[i] << ", " << (int)v[i+1] << ", " << (int)v[i+2] << endl;
		
	}
	
}

/* Static Function declaration */

void LazySnapping::activate_fg()
{
  // If foreground is active, invert the selection,
  // to make the background editable
  if (active_fg){
    //cout << "Activating background!" << endl;
    gimp_selection_invert(lazySnapping->image_ID);
    active_fg = FALSE;
  }
}


void LazySnapping::activate_bg()
{
  // If the background is active invert the selection,
  // to make the foreground editable
  if(!active_fg){
    //cout << "Activation foreground!" << endl;
    gimp_selection_invert(lazySnapping->image_ID);
    active_fg = TRUE;
  }
}


void LazySnapping::reset_action()
{   
  gimp_selection_clear(lazySnapping->image_ID);
  gimp_image_remove_layer(lazySnapping->image_ID, lazySnapping->input_layer);
  lazySnapping->input_layer = lazySnapping->add_layer("InputLayer");
  gimp_displays_flush();
}

void LazySnapping::termination_action()
{
  
  gimp_image_remove_layer(lazySnapping->image_ID, lazySnapping->input_layer);
  gimp_displays_flush();
}

/*
 * Static variables
 */

LazySnapping* LazySnapping::lazySnapping = NULL;
bool LazySnapping::active_fg = TRUE;
