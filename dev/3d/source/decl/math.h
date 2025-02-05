#ifndef _MATH_DEF_H_
#define _MATH_DEF_H_

//*****************************************************************************

#include "n3d.h"

//*****************************************************************************

typedef struct Angles {
	short alpha;		/* rotations */
	short beta;
	short gamma;		
	short xpos;			/* position */
	short ypos;
	short zpos;		
} SAngles;

//*****************************************************************************

extern void mkMatrix(Matrix*, SAngles*);

#endif
