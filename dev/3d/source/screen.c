#include "screen.h"

#include "n3d.h"
#include "blit.h"
#include "olist.h"

#include "decl/renderdef.h"

//*****************************************************************************

extern short DISPBUF0[];
extern short DISPBUF1[];

//*****************************************************************************

#define SCREEN_BUFFER_1 				((char*) DISPBUF0)
#define SCREEN_BUFFER_2 				((char*) DISPBUF1)

#define CAMERA_WIDTH 					320
#define CAMERA_HEIGHT 					240
#define OBJECT_WIDTH 					320
#define OBJECT_HEIGHT 					240

// blitter flags corresponding to OBJWIDTH
#define BLTTER_WIDTH_FLAG 				WID320

// length in bytes of a screen line (2 data buffers + 1 Z buffer -> 3*2 = 6 bytes/pixel
#define LINE_LENTH 						(OBJECT_WIDTH * 6L)

// 1/100th of the clock speed
#define MHZ 							265900L

//*****************************************************************************

union olist _screen1ObjectList[] = {
	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	SCREEN_BUFFER_1,		/* data */
	 	OBJECT_HEIGHT, 			/* height */
	 	OBJECT_WIDTH * 3 / 4,	/* dwidth */ 
	 	OBJECT_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_DOUBLE,		/* scaling stuffs */
	 	OL_SCALE_DOUBLE, 
	 	0 }},		

	{{	OL_STOP }},
};

union olist _screen2ObjectList[] = {
	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	SCREEN_BUFFER_2,		/* data */
	 	OBJECT_HEIGHT, 			/* height */
	 	OBJECT_WIDTH * 3 / 4,	/* dwidth */ 
	 	OBJECT_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_DOUBLE,		/* scaling stuffs */
	 	OL_SCALE_DOUBLE, 
	 	0 }},		

	{{	OL_STOP }},
};

Bitmap _screen1Bitmap = {
	CAMERA_WIDTH, 
	CAMERA_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS2 | BLTTER_WIDTH_FLAG,
	(void*) (SCREEN_BUFFER_1 + ((OBJECT_WIDTH - CAMERA_WIDTH) * 3L) + 
		(((OBJECT_HEIGHT - CAMERA_HEIGHT) / 2) * LINE_LENTH)),
};

Bitmap _screen2Bitmap = {
	CAMERA_WIDTH,
	CAMERA_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS1 | BLTTER_WIDTH_FLAG,
	(void*) (SCREEN_BUFFER_2 + ((OBJECT_WIDTH - CAMERA_WIDTH) * 3L) + 
		(((OBJECT_HEIGHT - CAMERA_HEIGHT) / 2) * LINE_LENTH)),
};

void N3DScreenInit(void) {
}

