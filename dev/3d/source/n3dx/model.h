#ifndef _N3D_MODEL_DEF_H_
#define _N3D_MODEL_DEF_H_

//*****************************************************************************

#include "n3d.h"

//*****************************************************************************
/* A model consists of:
 * (1) a pointer for the data for the model
 * (2) starting X,Y,Z coordinates for the model
 */
typedef struct Model {
	N3DObjdata* n3ddata;
	short initx;
	short inity;
	short initz;
	short reserved;		/* pads structure to a longword boundary */
} N3DModel;

#endif
