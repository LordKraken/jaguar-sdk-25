#include "renderbuffers.h"

#include "blit.h"
#include "renderer.h"
#include "globals.h"
#include "modeldata.h"

//*****************************************************************************

extern void VIDon(int);					/* turns video on */
extern void VIDsync(void);				/* waits for a vertical blank interrupt */

extern short DISPBUF0[];
extern short DISPBUF1[];
extern short jag257[];

//*****************************************************************************

// There are a few pieces of data here:
// 1) DISPBUF0/1: 2 display buffers defined in miscasm.s
// 2) SCREEN_BUFFER_1/2: Macros pointing to DISPBUF0/1
// 3) Their debug variants (_debugBuffer1/2 & _debugBuffer1/2)
// 4) _screen1/2: bitmap for the 3d engine to draw into, their data are SCREEN_BUFFER_1/2
// 5) g_olistScreen1/2: Object list containing objects for SCREEN_BUFFER_1/2 

// length in bytes of a screen line (2 data buffers + 1 Z buffer -> 3*2 = 6 bytes/pixel
#define SCREEN_LINE_LENTH 				(6L)

// Screen buffers are defined in miscasm.s
// SCREEN_BUFFER_WIDTH/HEIGHT is the maximum size of the rendering window
#define SCREEN_BUFFER_WIDTH				320
#define SCREEN_BUFFER_HEIGHT			240
#define SCREEN_BUFFER_SIZE				(SCREEN_BUFFER_WIDTH * (long) SCREEN_BUFFER_HEIGHT * SCREEN_LINE_LENTH)
#define SCREEN_BUFFER_1 				((char*) DISPBUF0)
#define SCREEN_BUFFER_2 				((char*) DISPBUF1)

#define SCREEN_WIDTH 					160
#define SCREEN_HEIGHT 					120
#define SCREEN_BLITTER_WIDTH_FLAG 		WID160

Bitmap* g_screen;

//*****************************************************************************

#ifdef N3D_DEBUG_CONSOLE

#define DEBUG_BUFFER_WIDTH 				320
#define DEBUG_BUFFER_HEIGHT 			32
#define DEBUG_BUFFER_SIZE 				(DEBUG_BUFFER_WIDTH * (long) DEBUG_BUFFER_HEIGHT * SCREEN_LINE_LENTH)
#define DEBUG_BLITTER_WIDTH_FLAG		WID320

short _debugBuffer1[DEBUG_BUFFER_SIZE];
short _debugBuffer2[DEBUG_BUFFER_SIZE];

#define DEBUG_BUFFER_1 					((char*) _debugBuffer1)
#define DEBUG_BUFFER_2 					((char*) _debugBuffer2)

#define SCREEN_DEBUG_WIDTH 				DEBUG_BUFFER_WIDTH
#define SCREEN_DEBUG_HEIGHT 			DEBUG_BUFFER_HEIGHT
#define SCREEN_DEBUG_BLITTER_WIDTH_FLAG WID320

Bitmap* g_screenDebug;

#endif

//*****************************************************************************

Bitmap _screen1 = {
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS2 | SCREEN_BLITTER_WIDTH_FLAG,
	(void*) (SCREEN_BUFFER_1)
};

Bitmap _screen2 = {
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS1 | SCREEN_BLITTER_WIDTH_FLAG,
	(void*) (SCREEN_BUFFER_2)
};

#ifdef N3D_DEBUG_CONSOLE

Bitmap _screenDebug1 = {
	SCREEN_DEBUG_WIDTH, 
	SCREEN_DEBUG_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS2 | SCREEN_DEBUG_BLITTER_WIDTH_FLAG,
	(void*) (DEBUG_BUFFER_1)
};

Bitmap _screenDebug2 = {
	SCREEN_DEBUG_WIDTH,
	SCREEN_DEBUG_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS1 | SCREEN_DEBUG_BLITTER_WIDTH_FLAG,
	(void*) (DEBUG_BUFFER_2)
};

#endif

union olist g_olistScreen1[] = {
	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	SCREEN_BUFFER_1,		/* data */
	 	SCREEN_HEIGHT, 			/* height */
	 	SCREEN_WIDTH * 3 / 4,	/* dwidth */ 
	 	SCREEN_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_DOUBLE,		/* scaling stuffs */
	 	OL_SCALE_DOUBLE, 
	 	0 }},

	{{	OL_BITMAP,				/* type */
		96, 240 * 2 - 96,		/* x, y */
	 	0L,						/* link */
	 	(char*) jag257,			/* data */
	 	48, 					/* height */
	 	128 * 1 / 4,			/* dwidth */ 
	 	128 / 4,				/* iwidth */
	 	4, 1, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_NONE,			/* scaling stuffs */
	 	OL_SCALE_NONE, 
	 	0 }},

#ifdef N3D_DEBUG_CONSOLE
	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	DEBUG_BUFFER_1,			/* data */
	 	SCREEN_DEBUG_HEIGHT, 		/* height */
	 	SCREEN_DEBUG_WIDTH * 3 / 4,	/* dwidth */ 
	 	SCREEN_DEBUG_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_NONE,			/* scaling stuffs */
	 	OL_SCALE_NONE, 
	 	0 }},
#endif

	{{	OL_STOP }},
};

union olist g_olistScreen2[] = {
	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	SCREEN_BUFFER_2,		/* data */
	 	SCREEN_HEIGHT, 			/* height */
	 	SCREEN_WIDTH * 3 / 4,	/* dwidth */ 
	 	SCREEN_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_DOUBLE,		/* scaling stuffs */
	 	OL_SCALE_DOUBLE, 
	 	0 }},		

	{{	OL_BITMAP,				/* type */
		96, 240 * 2 - 96,		/* x, y */
	 	0L,						/* link */
	 	(char*) jag257,			/* data */
	 	48, 					/* height */
	 	128 * 1 / 4,			/* dwidth */ 
	 	128 / 4,				/* iwidth */
	 	4, 1, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_NONE,			/* scaling stuffs */
	 	OL_SCALE_NONE, 
	 	0 }},

#ifdef N3D_DEBUG_CONSOLE
	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	DEBUG_BUFFER_2,			/* data */
	 	SCREEN_DEBUG_HEIGHT, 	/* height */
	 	SCREEN_DEBUG_WIDTH * 3 / 4,	/* dwidth */ 
	 	SCREEN_DEBUG_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_NONE,			/* scaling stuffs */
	 	OL_SCALE_NONE, 
	 	0 }},
#endif

	{{	OL_STOP }},
};

//*****************************************************************************

short  _swapScreens;

void N3DScreenInit(void) {
	VIDon(0x6c1);						/* 0x6c1 = CRY; 0x6c7 = RGB */
	VIDsync();							/* wait for video sync (paranoid code) */
	
	_swapScreens = 0;

	g_screen = &_screen1;
	memset(SCREEN_BUFFER_1, 0x00, SCREEN_BUFFER_SIZE);
	memset(SCREEN_BUFFER_2, 0x00, SCREEN_BUFFER_SIZE);

#ifdef N3D_DEBUG_CONSOLE
	g_screenDebug = &_screenDebug1;
	memset(DEBUG_BUFFER_1, 0x00, DEBUG_BUFFER_SIZE);
	memset(DEBUG_BUFFER_2, 0x00, DEBUG_BUFFER_SIZE);
#endif
}

//*****************************************************************************
/* Clears the bitmap pointed to by "screenBuffer", filling its data with a 
 * solid color, and its Z buffer with a null value
 */
void N3DScreenClear(Bitmap* screenBuffer) {
	long bgcolor = 0xf8f0f8f0;			/* Fill color in CRY format, duplicated */
	//long bgcolor = 0x00000000;			/* Fill color in CRY format, duplicated */
	long zvalue = 0xffffffff;			/* Z value (16.16 fraction) */

	B_PATD[0] = bgcolor;
	B_PATD[1] = bgcolor;
	B_Z3 = zvalue;
	B_Z2 = zvalue;
	B_Z1 = zvalue;
	B_Z0 = zvalue;
	A1_BASE = (long) screenBuffer->data;
	A1_STEP = 0x00010000L | ((-screenBuffer->width) & 0x0000ffff);
	A1_FLAGS = screenBuffer->blitflags | XADDPHR;
	A1_PIXEL = 0;
	A1_CLIP = 0;
	B_COUNT = ((long) screenBuffer->height << 16) | (screenBuffer->width);
	B_CMD = UPDA1|DSTWRZ|PATDSEL;
}

//*****************************************************************************

void N3DScreenSwap(void) {
	VIDsync();

	if (_swapScreens) {
		g_screen = &_screen1;
#ifdef N3D_DEBUG_CONSOLE
		g_screenDebug = &_screenDebug1;
#endif
	}
	else {
		g_screen = &_screen2;
#ifdef N3D_DEBUG_CONSOLE
		g_screenDebug = &_screenDebug2;
#endif
	}

	_swapScreens = !_swapScreens;
}

//*****************************************************************************

void N3DScreenMode() {
}
