#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************

#include "decl/math.h"

//*****************************************************************************

extern N3DAngles g_cameraAngles;
extern Matrix g_cameraMatrix;

//*****************************************************************************

extern void CameraInit();
extern void CameraUpdate();

#endif
