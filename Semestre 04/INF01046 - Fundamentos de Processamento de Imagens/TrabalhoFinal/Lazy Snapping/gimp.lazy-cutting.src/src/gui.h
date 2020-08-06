#ifndef __GUI_H__
#define __GUI_H__


#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

#include <iostream>

#define RESPONSE_RESET   1
#define RESPONSE_QUIT    2

using namespace std;

class GUI{

 public:
  GUI ();
  ~GUI();

  void set_foreground_marking_color(guchar* rgb);
  void set_background_marking_color(guchar* rgb);

  void register_run_function(void(*f)(GtkWidget*));

  void register_fg_active_function(void(*f)(void));
  void register_bg_active_function(void(*f)(void));
  
  void register_reset_function(void(*f)(void));
  void register_ok_function(void(*f)(void));

  void register_weightFactor(double* f);
  void register_colorFactor(double* f);

  void init();
  

  /*
   * display the gui
   */
  gboolean run();



 private:
  double *weightFactor;
  double *colorFactor;
  GtkWidget *dialog;
  
  static GimpRGB rgb_foreground;// Color used for the foreground marking
  static GimpRGB rgb_background;// Color used for the background marking


  static void (*run_callback)(GtkWidget*); // Run button  function

  static void (*bg_active_callback)(void); // Background active function
  static void (*fg_active_callback)(void); // Foreground active function

  static void (*reset_button_callback)(void);     // Reset button callback
  static void (*ok_button_callback)(void);        // OK button callback

  /*
   * Create the main window
   * Returns: Main window
   */
  GtkWidget* createDialog();


  /*
   * Create radio buttons, for selecting between
   * foregorung and background.
   * Binds call back functions
   * Returns: Radio buttons
   */
  GtkWidget* createRadioButton();

  /*
   * Create "run" button
   */
  GtkWidget* createRunButton();

  /*
   * Create notebook
   */
  GtkWidget* createNotebook();

  void create_advanced_page(GtkWidget* notebook);
  void create_cutout_page(GtkWidget* notebook, GtkWidget* content);
  /*
   * Set the color, for marking the foreground and background
   */
  static void set_foreground_active(GtkWidget* button);
  static void set_background_active(GtkWidget* button);

  /*
   * Set the color as foreground color
   * rgb: The new foreground color
   */  
  static void set_foreground(GimpRGB& rgb);


  static void response_handler(GtkWidget *widget,
			       gint responseID,
			       gpointer data);

};
#endif 
