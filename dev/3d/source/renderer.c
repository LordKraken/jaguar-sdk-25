#include "renderer.h"

#include "decl/globals.h"
#include "decl/lights.h"

#include "blit.h"
#include "n3d.h"
#include "n3dintern.h"

//*****************************************************************************

extern void VIDon(int);					/* turns video on */
extern void VIDsync(void);				/* waits for a vertical blank interrupt */
extern void GPUload(long *);			/* loads a package into the GPU */
extern void GPUrun(void (*)());			/* runs a GPU program */

//*****************************************************************************

SRenderer* g_currentRenderer = 0;

//*****************************************************************************

void N3DInit(void) {
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
/* Render an object into a bitmap. The parameters are:
 *	window: the destination bitmap
 *	obj:	the N3D object to render
 *	cam:	the viewing matrix
 *	lmodel:	the lighting model
 *	rend:	the renderer to use (wireframe, gouraud, or texture mapped9
 */

TPoint* tpoints;
//TPoint tpoints2[1000];

void N3DRender(Bitmap* window, N3DObject* obj, Matrix* cam, SRenderer* rend)
{
	// load GPU code
	GPUload(rend->gpucode);

	// allocate temporary storage
	tpoints = malloc(sizeof(TPoint) * obj->data->numpoints);

	params[0] = (long) obj->data;
	params[1] = (long) &obj->M;
	params[2] = (long) window;
	params[3] = (long) cam;
	params[4] = (long) &g_lightModel;
	params[5] = (long) (tpoints);
	//params[5] = (long)(&tpoints2[0]);

	GPUrun(rend->gpuenter);

	free(tpoints);
}

//*****************************************************************************

void N3DSwap() {
	VIDsync();
}

//*****************************************************************************

void N3DDebug() {

}
