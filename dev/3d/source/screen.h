#ifndef _RENDER_SCREEN_H_
#define _RENDER_SCREEN_H_

//*****************************************************************************

#include "blit.h"
#include "n3d.h"
#include "olist.h"

//*****************************************************************************

extern union olist g_olistScreen1[];
extern union olist g_olistScreen2[];
extern Bitmap g_bitmapScreen1;
extern Bitmap g_bitmapScreen2;
extern Bitmap g_debugScreen1;
extern Bitmap g_debugScreen2;

//*****************************************************************************

extern void N3DScreenInit();
extern void N3DScreenMode();

#endif
