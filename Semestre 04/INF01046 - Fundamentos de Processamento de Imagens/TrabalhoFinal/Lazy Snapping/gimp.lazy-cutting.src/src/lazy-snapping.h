#ifndef __LAZY_SNAPPING_H__
#define __LAZY_SNAPPING_H__

#include <iostream>
#include <vector>
#include <limits>

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#include <assert.h>
#include <time.h>

#include "gui.h"
#include "k-means.cpp"
#include "k-means.h"

#include "maxflow-v2.2.src/adjacency_list/graph.h"

/*
 * Definitions used for k-means
 */
#define _k 3
#define _dim 64
#define __default__weightFactor__   64
#define __default__colorFactor__    0.5

class LazySnapping{

 public:

  /*
   * Constructor
   * img_ID: id of the image
   * draw_ID: id of the drawabale
   */
  
  LazySnapping(gint32 img_ID, gint32 draw_ID, gint32 lay_ID);
  
  ~LazySnapping();
  /*
   * Run lazy-snapping
   */
  void run();

 private:
  double weightFactor;
  double colorFactor;

  GUI* gui;
  gint32 image_ID; 
  gint32 drawable_ID;
  gint32 layer_ID;

  gint32 input_layer;

  static LazySnapping* lazySnapping;

  /*
   * ture if foreground is active
   * false if background is active
   */

  static bool active_fg;


  /*
   * The Graph stuff
   * Node for minCut
   */
  Graph::node_id* nodes;
  Graph* graph;

  /*
   * Colors used to mark the back, foreground
   * The colors are defined in the constructor!
   */

  guchar bg_color[3];
  guchar fg_color[3];

  typedef vector<float> Pixels;
  typedef Pixels::iterator Iterator;
  

  Pixels bg_input;
  Pixels fg_input;
  
//  Pixels bg_centroids;
//  Pixels fg_centroids;
  guchar* bg_centroids;
  guchar* fg_centroids;

  //KMeans<_k, _dim, unsigned char> kmean;
  KMeans<_k, _dim, float> kmean;

  /*
   * Callback function for the run button
   */
  static void run_Button_Callback(GtkWidget* button);
  static void reset_action();
  static void termination_action();

  static void activate_fg(void);
  static void activate_bg(void);

  void computeMaxFlow(gint32 layer);

  /*
   * Create the graph for graph cut algorithm
   * First a very simple and very unefficent implementation
   *
   */  

  void createGraph(gint32 layer);


  /***** FUNCTIONS USED FOR THE PRIOR ENERGY COMPUTATION ********************/
  

  float colorDistanceSq(guchar* c1, guchar* c2, int dim);


  /***** FUNCTIONS USED FOR THE LIKELIHOOD ENERGY COMPUTATION ***************/

  /*
   * Compute min distance to FOREGROUND CENTROIDS
   *
   * return: minimum distance
   */

  float min_fg(guchar* color);


  /*
   * Compute min distance to BACKGROUND CENTROIDS
   *
   * return: minimum distance
   */

  float min_bg(guchar* color);

  /*
   * Compute min distance to centroids
   */

  float minCentroidDistance(guchar* color, Pixels& centroids, int dim);
  float minCentroidDistance(guchar* color, guchar* centroids, int dim);

  /*
   * Compute the square of the euclidien distance between two points
   * c1: rgb color as array of guchar
   * c2: rgb color as vector
   * return: euclidien distance squared
   */

  float distance(const guchar* c1, Iterator c2, int dim);
  float distance(const guchar* c1, const guchar* c2, int dim);


  /* For the moment copy foreground to new layer*/
  void extractFG(gchar* name);

  void extractFGToMask();
  /* 
   * Computes the centroids of foreground 
   * and background
   */
  void getCentroids();

  //  void getCentroids2();
  //void vector2Array(Pixels& vec, float* array);


  //void LazySnapping::vector2Array(Pixels& vec, float* array);
  /*
   * Get user input from layer
   * layer: id of layer
   */

  void process_input(gint32 layer);


  /*
   * Get user input from layer
   */
  void build_graph(gint32 layer);
  
  inline float colorDistance(guint8 * a, guint8 * b, unsigned int colors)
  {
	  float t = 0;
	  for (unsigned int i = 0; i < colors; i++)
	  {
		  float d = a[i] - b[i];
		  t += d*d;
	  }
	  return sqrt(t);
  }
    
  /*
   * Create a transparent layer and add it to the image.
   * name: name of the layer
   * Returns: id of the layer
   */

  gint32 add_layer(gchar* name);
  
  
  /*
   * Start GUI
   */
  void start_GUI();
  
  void printVector(vector<float>& v, const char* com);
  void printVector(vector<unsigned char>& v);

};
#endif
