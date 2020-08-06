#include "gui.h"



/* 
 * Constructor
 */

GUI::GUI (): weightFactor(NULL), colorFactor(NULL), dialog(NULL){}
GUI::~GUI(){}

void GUI::set_foreground_marking_color(guchar* rgb){gimp_rgb_set_uchar(&rgb_foreground, rgb[0], rgb[1], rgb[2]);}
void GUI::set_background_marking_color(guchar* rgb){gimp_rgb_set_uchar(&rgb_background, rgb[0], rgb[1], rgb[2]);}

/* Callback function registration */
void GUI::register_run_function(void(*f)(GtkWidget*)){ run_callback = f;}
void GUI::register_fg_active_function(void(*f)(void)){ fg_active_callback = f;}
void GUI::register_bg_active_function(void(*f)(void)){ bg_active_callback = f;}

void GUI::register_reset_function(void(*f)(void)){ reset_button_callback = f;}
void GUI::register_ok_function(void(*f)(void)){ ok_button_callback = f;}

void GUI::register_weightFactor(double* f){ weightFactor = f; }
void GUI::register_colorFactor(double* f){ colorFactor = f; }


void GUI::init()
{
  
  // Get main window
  dialog = createDialog();
  
  // Add radioButton
  GtkWidget *radioButton;
  radioButton = createRadioButton();
    
  // Add Notebook
  //radioButton = createNotebook();

  // Add run button
  //GtkWidget* runButton;
  //runButton = createRunButton();

  // /TEMP gtk_container_add(GTK_CONTAINER (GTK_DIALOG (dialog)->vbox), radioButton);

  
  //gtk_container_add(GTK_CONTAINER (GTK_DIALOG (dialog)->vbox), runButton);

  /* TEMP */

  // Create notebook
  GtkWidget *notebook;
  notebook = gtk_notebook_new ();
  gtk_box_pack_start (GTK_BOX (GTK_DIALOG(dialog)->vbox), notebook, TRUE, TRUE, 0);
  gtk_widget_show(notebook);
  
  // Add pages
  create_cutout_page(notebook, radioButton);
  create_advanced_page(notebook);



  /* /TEMP */

  gtk_widget_show(radioButton);  
  //gtk_widget_show(runButton);
  gtk_widget_show (dialog); 
    
}


/*
 * display the gui
 */
gboolean GUI::run()
{
  
  gboolean run = true; //(gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);    
  //gtk_widget_destroy (dialog);
  gtk_main ();
  return run;
}

/*
 * Static variable declaration
 */

GimpRGB GUI::rgb_foreground;
GimpRGB GUI::rgb_background;

void (*GUI::bg_active_callback)(void) = NULL;
void (*GUI::fg_active_callback)(void) = NULL;

void (*GUI::reset_button_callback)(void) = NULL;
void (*GUI::ok_button_callback)(void) = NULL;

void (*GUI::run_callback)(GtkWidget*) = NULL;
/*
 * Create the main window
 * Returns: Main window
 */
GtkWidget* GUI::createDialog()
{
    
  GtkWidget *dialog;
 
  gimp_ui_init ("lazy snapping", FALSE);
  dialog = gimp_dialog_new ("lazy snapping", "lazy snapping",
			    NULL, (GtkDialogFlags)0,
			    gimp_standard_help_func, "plug-in lazy snapping",
			    GIMP_STOCK_RESET,   RESPONSE_RESET,
			    GTK_STOCK_APPLY,    GTK_RESPONSE_APPLY,
			    GTK_STOCK_QUIT,     RESPONSE_QUIT,
			    NULL);

  g_signal_connect (dialog, "response",
                    G_CALLBACK (response_handler),
                    NULL);

  g_signal_connect (dialog, "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);
  return dialog;       
}


/*
 * Create radio buttons, for selecting between
 * foregorung and background.
 * Binds call back functions
 * Returns: Radio buttons
 */
GtkWidget* GUI::createRadioButton()
{
  GtkWidget *main_vbox;
  main_vbox = gtk_vbox_new (FALSE, 6);

  // Add background radio button 
  GtkWidget *button;
  button = gtk_radio_button_new_with_label (NULL, "Mark BG");
  gtk_widget_set_name (button, "Background");
  
  gtk_box_pack_start (GTK_BOX (main_vbox), button, TRUE, TRUE, 0);
  // Connect signal of background radio button to set_background_active
  g_signal_connect( G_OBJECT (button),
		    "toggled",
		    G_CALLBACK (set_background_active),
		    NULL);
  
  set_background_active(button);
  // Set the active radio button
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);
  

  gtk_widget_show (button);
  
  // Add foreground radio button
  button = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (button),
	                                                  "Mark FG");
  gtk_widget_set_name (button, "Foreground");
  
  // Connect signal of foreground radio button to set_foreground_active
  g_signal_connect( G_OBJECT (button),
		    "toggled",
		    G_CALLBACK (set_foreground_active),
		    NULL);
  
  gtk_box_pack_start (GTK_BOX (main_vbox), button, TRUE, TRUE, 0);
  
  gtk_widget_show (button);
  
  return main_vbox;
}


/*
 * Create advanced page
 */
void GUI::create_advanced_page(GtkWidget* notebook)
{
  GtkWidget *hbox;
  GtkWidget *table;
  GtkObject *scale_entry;


  hbox = gtk_hbox_new(FALSE, 12);
  gtk_container_set_border_width(GTK_CONTAINER(hbox), 12);
  gtk_notebook_append_page(GTK_NOTEBOOK (notebook), hbox,
			  gtk_label_new_with_mnemonic ("Advanced"));
  gtk_widget_show (hbox);


  // Create a table
  table = gtk_table_new(4, 3, FALSE);
  //gtk_table_set_col_spacings (GTK_TABLE (table), 6);
  //gtk_table_set_row_spacings (GTK_TABLE (table), 6);
  gtk_box_pack_start (GTK_BOX(hbox), table, FALSE, FALSE, 0);
  gtk_widget_show (table);

  scale_entry = gimp_scale_entry_new (GTK_TABLE (table), 0, 0,
				     "_Weight Factor:", 100, 0,
				     *weightFactor, 1.0, 128.0, 1, 5.0, 0,
				     TRUE, 0, 0,
				     NULL, NULL);

  g_signal_connect (scale_entry, "value-changed",
                    G_CALLBACK (gimp_double_adjustment_update),
                    weightFactor);
  
  scale_entry = gimp_scale_entry_new (GTK_TABLE (table), 0, 1,
				     "_Color Factor:", 100, 0,
				     *colorFactor, 0.00, 1.0, 0.01, 0.1, 2,
				     TRUE, 0, 0,
				     NULL, NULL);
  
  g_signal_connect (scale_entry, "value-changed",
                    G_CALLBACK (gimp_double_adjustment_update),
		    colorFactor);
  
}

/*
 * Create cutout page
 */
void GUI::create_cutout_page(GtkWidget* notebook, GtkWidget* content)
{
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), content,
			    gtk_label_new_with_mnemonic ("Cutout"));

}


/*
 * Create "run" button
 */
GtkWidget* GUI::createRunButton()
{    
  // the run button
  GtkWidget* button;
  button = gtk_button_new_with_label("run");    
  gtk_button_clicked(GTK_BUTTON(button));
  
  g_signal_connect (G_OBJECT (button), "clicked",
		    G_CALLBACK (run_callback), (gpointer) "run button");
    
  return button;
}

/*
 * Set the color, for marking the foreground and background
 */
void GUI::set_foreground_active(GtkWidget* button)
{
  if (GTK_TOGGLE_BUTTON (button)->active){
    set_foreground(rgb_foreground);

    if(fg_active_callback != NULL) {
      fg_active_callback();
    }
  }
}

void GUI::set_background_active(GtkWidget* button)
{
  if (GTK_TOGGLE_BUTTON (button)->active){    
    set_foreground(rgb_background);
    if(bg_active_callback != NULL) {
      bg_active_callback();
    }
  }
}


/*
 * Set the color as foreground color
 * rgb: The new foreground color
 */  
void GUI::set_foreground(GimpRGB& rgb)
{
  gboolean done;
  done = gimp_palette_set_foreground(&rgb);
  
  if (!done) cout << "Failed to set foreground color!" << endl;
}


/*
 *
 */
void GUI::response_handler(GtkWidget *widget,
			   gint  responseID,
			   gpointer data)
{

  switch(responseID){

  case RESPONSE_RESET:
    //cout << "RESPONSE_RESET" << endl;
    if(reset_button_callback != NULL) 
      reset_button_callback();
    
    break;

  case GTK_RESPONSE_APPLY:
    if(run_callback != NULL)
      run_callback(NULL);
    break;

  case RESPONSE_QUIT:
    //cout << "RESPONSE_OK" << endl;
    if(ok_button_callback != NULL) 
      ok_button_callback();

    gtk_widget_destroy(widget);    
    break;

  default:
    gtk_widget_destroy (widget);
  }
}
