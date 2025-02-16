#ifndef _N3D_RENDER_BUFFERS_H_
#define _N3D_RENDER_BUFFERS_H_

//*****************************************************************************

#include "n3d.h"
#include "olist.h"

#include "config.h"

//*****************************************************************************

extern union olist g_olistScreen1[];
extern union olist g_olistScreen2[];

extern Bitmap* g_screen;
#ifdef N3D_DEBUG_CONSOLE
extern Bitmap* g_screenDebug;
#endif

//*****************************************************************************

extern void N3DScreenInit();
extern void N3DScreenClear();
extern void N3DScreenSwap();
extern void N3DScreenMode();

#endif
