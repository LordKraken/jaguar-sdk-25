#include "renderer.h"

#include "decl/globals.h"
#include "decl/lights.h"
#include "decl/renderdef.h"

#include "blit.h"
#include "camera.h"
#include "models.h"
#include "n3d.h"
#include "n3dintern.h"
#include "rendertools.h"

//*****************************************************************************

extern void VIDon(int);					/* turns video on */
extern void VIDsync(void);				/* waits for a vertical blank interrupt */
extern void GPUload(long *);			/* loads a package into the GPU */
extern void GPUrun(void (*)());			/* runs a GPU program */

//*****************************************************************************

// Rendering code (asm)
extern long wfcode[], 
	gourcode[], 
	gourphrcode[],
	texcode[], 
	flattexcode[], 
	gstexcode[];

// Rendering functions (asm)
extern void wfenter(), 
	gourenter(), 
	gourphrenter(),
	texenter(), 
	flattexenter(), 
	gstexenter();

// Renderers supported
SRenderer _renderers[] = {
	{ RENDER_MODE_WIREFRAME, TEXTURE_MODE_NORMAL, wfcode, wfenter },
	{ RENDER_MODE_GOURAUD, TEXTURE_MODE_NORMAL, gourcode, gourenter },
	{ RENDER_MODE_GOURAUD_PHRASE, TEXTURE_MODE_NORMAL, gourphrcode, gourphrenter },
	{ RENDER_MODE_TEXTURE_UNSHADED, TEXTURE_MODE_NORMAL, texcode, texenter },
	{ RENDER_MODE_TEXTURE_FLATSHADED, TEXTURE_MODE_NORMAL, flattexcode, flattexenter },
	{ RENDER_MODE_TEXTURE_GOURAUD, TEXTURE_MODE_SHADING, gstexcode, gstexenter },
};
const short _renderersCount = sizeof(_renderers) / sizeof(SRenderer);

// Current renderer and current rendering functions
SRenderer* g_renderer;
long* _gpucode;
void (*_gpuenter)();

//*****************************************************************************

void N3DInit(void) {
	N3DToolsInit();

	g_renderer = 0;
	_gpucode = 0;
	_gpuenter = 0;

	N3DLoad(RENDER_MODE_TEXTURE_GOURAUD);

	VIDon(0x6c1);						/* 0x6c1 = CRY; 0x6c7 = RGB */
	VIDsync();							/* wait for video sync (paranoid code) */
}

//*****************************************************************************
/* Clears the bitmap pointed to by "buf", filling its data with a solid color,
 * and its Z buffer with a null value
 */
void N3DClear(Bitmap* buf) {
	long bgcolor = 0xf8f0f8f0;			/* Fill color in CRY format, duplicated */
	long zvalue = 0xffffffff;			/* Z value (16.16 fraction) */

	B_PATD[0] = bgcolor;
	B_PATD[1] = bgcolor;
	B_Z3 = zvalue;
	B_Z2 = zvalue;
	B_Z1 = zvalue;
	B_Z0 = zvalue;
	A1_BASE = (long) buf->data;
	A1_STEP = 0x00010000L | ((-buf->width) & 0x0000ffff);
	A1_FLAGS = buf->blitflags | XADDPHR;
	A1_PIXEL = 0;
	A1_CLIP = 0;
	B_COUNT = ((long) buf->height << 16) | (buf->width);
	B_CMD = UPDA1|DSTWRZ|PATDSEL;
}

//*****************************************************************************

void N3DLoad(ERenderMode mode) {
	int i;
	for (i = 0; i < _renderersCount; i++) {
		if (_renderers[i].mode == mode) {
			g_renderer = &_renderers[i];
			_gpucode = g_renderer->gpucode;
			_gpuenter = g_renderer->gpuenter;
			N3DToolsFixAllTextures(g_renderer->texmode);
			break;
		}
	}
}

//*****************************************************************************
/* Render an object into a bitmap. The parameters are:
 *	window: the destination bitmap
 *	obj:	the N3D object to render
 *	cam:	the viewing matrix
 *	lmodel:	the lighting model
 */

TPoint* tpoints;
//TPoint tpoints2[1000];

void N3DRender(Bitmap* window, N3DObject* obj)
{
	// load GPU code
	GPUload(_gpucode);

	// allocate temporary storage
	//tpoints = malloc(sizeof(TPoint) * obj->data->numpoints);
	tpoints = malloc(sizeof(TPoint) * obj->data->numpoints);

	params[0] = (long) obj->data;
	params[1] = (long) &obj->M;
	params[2] = (long) window;
	params[3] = (long) &g_cameraMatrix;
	params[4] = (long) &g_lightModel;
	params[5] = (long) (tpoints);
	//params[5] = (long)(&tpoints2[0]);

	GPUrun(_gpuenter);

	free(tpoints);
}

//*****************************************************************************

void N3DSwap(void) {
	VIDsync();
}

//*****************************************************************************

void N3DDebug(void) {
}
