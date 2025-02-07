#ifndef _RENDER_TOOLS_H_
#define _RENDER_TOOLS_H_

//*****************************************************************************

#include "n3d.h"

//*****************************************************************************

extern void N3DToolsInit();
extern void N3DToolsNextRenderer();
extern void N3DToolsFixTexture(Bitmap*);
extern void N3DToolsFixAllTextures(int);

#endif
