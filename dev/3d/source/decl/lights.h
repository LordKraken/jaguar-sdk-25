#ifndef _LIGHTS_DEF_H_
#define _LIGHTS_DEF_H_

//*****************************************************************************

#include "n3d.h"

//*****************************************************************************

Lightmodel g_lightModel = {
	0x2222,				/* ambient illumination */
	1,					/* number of lights */
	{					/* Light definitions */
	  { -0x24f3, -0x24f3, -0x24f3, 0x4000 },
	  { 0, 0, 0, 0xC000 },
	  { 0x4000, 0, 0, 0x4000 },
	  { 0, 0x4000, 0, 0x4000 },
	  { 0, 0, 0x4000, 0x4000 },
	}
};

#endif
