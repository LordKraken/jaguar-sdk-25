#include "screen.h"

//*****************************************************************************

extern short DISPBUF0[];
extern short DISPBUF1[];

//extern const char* _jaguar32;
extern short jag257[];

//*****************************************************************************


#define CAMERA_WIDTH 					256
#define CAMERA_HEIGHT 					192
#define SCREEN_WIDTH 					256
#define SCREEN_HEIGHT 					192
#define DEBUG_WIDTH 					320
#define DEBUG_HEIGHT 					32

// blitter flags corresponding to OBJWIDTH
#define BLITTER_WIDTH_FLAG 				WID256
#define BLITTER_WIDTH_FLAG_DEBUG		WID320

// length in bytes of a screen line (2 data buffers + 1 Z buffer -> 3*2 = 6 bytes/pixel
#define LINE_LENTH 						(SCREEN_WIDTH * 6L)

// 1/100th of the clock speed
#define MHZ 							265900L

//*****************************************************************************

short _debugBuffer1[DEBUG_WIDTH * DEBUG_HEIGHT * 3];
short _debugBuffer2[DEBUG_WIDTH * DEBUG_HEIGHT * 3];

#define SCREEN_BUFFER_1 				((char*) DISPBUF0)
#define SCREEN_BUFFER_2 				((char*) DISPBUF1)
#define DEBUG_BUFFER_1 					((char*) _debugBuffer1)
#define DEBUG_BUFFER_2 					((char*) _debugBuffer2)

//*****************************************************************************

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

	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	DEBUG_BUFFER_1,		/* data */
	 	DEBUG_HEIGHT, 			/* height */
	 	DEBUG_WIDTH * 3 / 4,	/* dwidth */ 
	 	DEBUG_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_NONE,			/* scaling stuffs */
	 	OL_SCALE_NONE, 
	 	0 }},

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


	{{	OL_BITMAP,				/* type */
		0, 0,					/* x, y */
	 	0L,						/* link */
	 	DEBUG_BUFFER_2,		/* data */
	 	DEBUG_HEIGHT, 			/* height */
	 	DEBUG_WIDTH * 3 / 4,	/* dwidth */ 
	 	DEBUG_WIDTH / 4,		/* iwidth */
	 	4, 3, 0, 				/* depth, pitch, index */
	 	OL_TRANS, 0,			/* flags, firstpix */
	 	OL_SCALE_NONE,			/* scaling stuffs */
	 	OL_SCALE_NONE, 
	 	0 }},

	{{	OL_STOP }},
};

Bitmap g_bitmapScreen1 = {
	CAMERA_WIDTH, 
	CAMERA_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS2 | BLITTER_WIDTH_FLAG,
	(void*) (SCREEN_BUFFER_1)
	/*
	(void*) (SCREEN_BUFFER_1 + 
		((SCREEN_WIDTH - CAMERA_WIDTH) * 3L) + 
		(((SCREEN_HEIGHT - CAMERA_HEIGHT) / 2) * LINE_LENTH)
		),
	*/
};

Bitmap g_bitmapScreen2 = {
	CAMERA_WIDTH,
	CAMERA_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS1 | BLITTER_WIDTH_FLAG,
	(void*) (SCREEN_BUFFER_2)
	/*
	(void*) (SCREEN_BUFFER_2 + 
		((SCREEN_WIDTH - CAMERA_WIDTH) * 3L) + 
		(((SCREEN_HEIGHT - CAMERA_HEIGHT) / 2) * LINE_LENTH)
		),
	*/
};

Bitmap g_debugScreen1 = {
	DEBUG_WIDTH, 
	DEBUG_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS2 | BLITTER_WIDTH_FLAG_DEBUG,
	(void*) (DEBUG_BUFFER_1)
};

Bitmap g_debugScreen2 = {
	DEBUG_WIDTH,
	DEBUG_HEIGHT,
	PIXEL16 | PITCH3 | ZOFFS1 | BLITTER_WIDTH_FLAG_DEBUG,
	(void*) (DEBUG_BUFFER_2)
};

void N3DScreenInit(void) {
}

