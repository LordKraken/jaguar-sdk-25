#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************

#include "decl/math.h"

//*****************************************************************************

extern N3DAngles g_cameraAngles;
extern Matrix g_cameraMatrix;

//*****************************************************************************

extern void N3DCameraInit();
extern void N3DCameraUpdate();
extern void N3DCameraForward(short);
extern void N3DCameraStrife(short);
extern void N3DCameraMove(short, short, short);
extern void N3DCameraRotate(short, short, short);

#endif
