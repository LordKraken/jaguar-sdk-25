/*
 * Test program for new 3D renderer.
 * Copyright 1995 Atari Corporation.
 * All Rights Reserved.
 */

#include "olist.h"
#include "blit.h"
#include "joypad.h"
#include "n3d.h"
#include "n3dintern.h"

/****************************************************************
 *	Defines							*
 ****************************************************************/

/* camera width and height */
#define CAMWIDTH 								320
#define CAMHEIGHT 							240

/* the width and height of the screen object */
#define OBJWIDTH 								320
#define OBJHEIGHT 							240
#define WIDFLAG 								WID320		/* blitter flags corresponding to OBJWIDTH */

/* length in bytes of a screen line (2 data buffers + 1 Z buffer -> 3*2 = 6 bytes/pixel */
#define LINELEN 								(OBJWIDTH * 6L)

/* 1/100th of the clock speed */
#define MHZ 									265900L


/****************************************************************
 *	External variables					*
 ****************************************************************/


/* the 2 screen buffers */
extern short DISPBUF0[], DISPBUF1[];
#define DATA1 ((char *)DISPBUF0)
#define DATA2 ((char *)DISPBUF1)


/****************************************************************
 *	Initialized Data					*
 ****************************************************************/

/* object list for first screen */
union olist buf1_olist[] =
{
	{{	OL_BITMAP,			/* type */
		0, 0,					/* x, y */
	 	0L,					/* link */
	 	DATA1,				/* data */
	 	OBJHEIGHT, 			/* height */
	 	OBJWIDTH * 3 / 4,	/* dwidth */ 
	 	OBJWIDTH / 4,		/* iwidth */
	 	4, 3, 0, 			/* depth, pitch, index */
	 	OL_TRANS, 0,		/* flags, firstpix */
	 	OL_SCALE_DOUBLE,	/* scaling stuff */
	 	OL_SCALE_DOUBLE, 
	 	0 }},		

	{{	OL_STOP }},
};

/* object list for second screen */
union olist buf2_olist[] =
{
	{{OL_BITMAP,	/* type */
	 //20+(320-OBJWIDTH)/2, 20+(240-OBJHEIGHT),		/* x, y */
	0, 0,
	 0L,		/* link */
	 DATA2,		/* data */
	 OBJHEIGHT, OBJWIDTH*3/4, OBJWIDTH/4,		/* height, dwidth, iwidth */
	 4, 3, 0, OL_TRANS, 0,	/* depth, pitch, index, flags, firstpix */
	 OL_SCALE_DOUBLE,OL_SCALE_DOUBLE,0}},		/* scaling stuff */

	{{OL_STOP}}
};

/* Bitmaps for the two screens */
Bitmap scrn1 = {
	CAMWIDTH, CAMHEIGHT,
	PIXEL16 | PITCH3 | ZOFFS2 | WIDFLAG,
	(void*) (DATA1 + ((OBJWIDTH - CAMWIDTH) * 3L) + (((OBJHEIGHT - CAMHEIGHT) / 2) * LINELEN)),
};

/* initial data for camera corresponding to second screen buffer */
Bitmap scrn2 = {
	CAMWIDTH, CAMHEIGHT,
	PIXEL16 | PITCH3 | ZOFFS1 | WIDFLAG,
	(void*) (DATA2 + ((OBJWIDTH - CAMWIDTH) * 3L) + (((OBJHEIGHT - CAMHEIGHT) / 2) * LINELEN)),
};

