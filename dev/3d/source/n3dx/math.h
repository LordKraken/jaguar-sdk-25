#ifndef _N3D_MATH_DEF_H_
#define _N3D_MATH_DEF_H_

//*****************************************************************************

#include "n3d.h"

//*****************************************************************************

typedef struct Angles {
	short alpha;		/* rotations x, y, z */
	short beta;
	short gamma;		
	short xpos;			/* position */
	short ypos;
	short zpos;		
} N3DAngles;

//*****************************************************************************

extern int cos(int);
extern int sin(int);
extern void mkMatrix(Matrix*, N3DAngles*);

#endif
