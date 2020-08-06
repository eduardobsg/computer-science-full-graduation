/* GIMP Plug-in Template
 * Copyright (C) 2000  Michael Natterer <mitch@gimp.org> (the "Author").
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Author of the
 * Software shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the Author.
 */

#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include "lazy-snapping.h"

using namespace std;


/*  Constants  */
#define PROCEDURE_NAME   "lazy-snapping"

#define DATA_KEY_VALS    "plug_in_template"
#define DATA_KEY_UI_VALS "plug_in_template_ui"

#define PARASITE_KEY     "plug-in-template-options"


/*  Local function prototypes  */
static void query(void);

static void run(const gchar      *name,
		     gint              nparams,
		     const GimpParam  *param,
		     gint             *nreturn_vals,
		     GimpParam       **return_vals);


/*  Local variables  */
/*
const PlugInVals default_vals =
{
  0,
  1,
  2,
  0,
  FALSE
};

const PlugInImageVals default_image_vals =
{
  0
};

const PlugInDrawableVals default_drawable_vals =
{
  0
};

const PlugInUIVals default_ui_vals =
{
  TRUE
};

static PlugInVals         vals;
static PlugInImageVals    image_vals;
static PlugInDrawableVals drawable_vals;
static PlugInUIVals       ui_vals;
*/

GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,  /* init_proc  */
  NULL,  /* quit_proc  */
  query, /* query_proc */
  run,   /* run_proc   */
};


MAIN ()

// Procedure regristration
static void query (void)
{ 
  /* GimpParamDef contains:
   *  - the parameter type, 
   *  - its name, 
   *  - and a string describing the parameter.
   */
  static GimpParamDef args[] =
  {
    { GIMP_PDB_INT32,    "run_mode",   "Interactive, non-interactive"    },
    { GIMP_PDB_IMAGE,    "image",      "Input image"                     },
    { GIMP_PDB_DRAWABLE, "drawable",   "Input drawable"                  }


    //    { GIMP_PDB_INT32,    "dummy",      "dummy1"                          },
    //    { GIMP_PDB_INT32,    "dummy",      "dummy2"                          },
    //    { GIMP_PDB_INT32,    "dummy",      "dummy3"                          },
    //    { GIMP_PDB_INT32,    "seed",       "Seed value (used only if randomize is FALSE)" },
    //    { GIMP_PDB_INT32,    "randomize",  "Use a random seed (TRUE, FALSE)" }
  };


  /*gimp_install_procedure declares:
   * - procedure name, 
   * - some description and help strings, 
   * - menu path where the plug-in should sit, 
   * - image types handled by the plug-in, 
   * - and at the end, input and output parameters number, as well as the parameters descriptors.
  */

  gimp_install_procedure (PROCEDURE_NAME,
			  "lazy snapping",
			  "Help",
			  "Gerhard Roethlin <gerhardr@student.ethz.ch>, Olivier Saurer <saurero@student.ethz.ch",
			  "Gerhard Roethlin <gerhardr@student.ethz.ch>, Olivier Saurer <saurero@student.ethz.ch>",
			  "2006",
			  "<Image>/Filters/Image Cutout/lazy snapping",
			  "RGB*, GRAY*, INDEXED*",
			  GIMP_PLUGIN,
			  G_N_ELEMENTS (args), 0,
			  args, NULL);
}



/* *run* is the other function for PLUG_IN_INFO
   The core of the plug-in stands there.
   Output values (return_vals in the prototype) must have at least one value associated - the plug-in status. 
   Typically, this parameter will hold "GIMP_PDB_SUCCESS". 
*/

static void run (const gchar      *name,
		 gint              n_params, 
		 const GimpParam  *param,
		 gint             *nreturn_vals,
		 GimpParam       **return_vals)
{

  
  gint32 drawable_ID;
  gint32 image_ID;
  gint32 top_layer_ID;

  /* get image */
  image_ID = param[1].data.d_image;

  /* get drawable */
  drawable_ID = param[2].data.d_drawable;
  
  /* get layer */
  top_layer_ID = gimp_image_get_active_layer(image_ID);
  gimp_layer_add_alpha(top_layer_ID);

  //cout << "Input layer " << layer_ID << endl;



  static GimpParam  values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode       run_mode;
  
  /* Setting mandatory output values */
  *nreturn_vals = 1;
  *return_vals  = values;
  
  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;
  
  /* Getting run_mode - we won't display a dialog if 
   * we are in NONINTERACTIVE mode */
  run_mode = (GimpRunMode)param[0].data.d_int32;

  LazySnapping* lazy = new LazySnapping(image_ID, drawable_ID, top_layer_ID);
  lazy->run();  

}
