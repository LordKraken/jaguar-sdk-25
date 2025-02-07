//*****************************************************************************
// PROJECT TOP GEAR
//*****************************************************************************

#include "decl/globals.h"
#include "decl/fonts.h"
#include "decl/math.h"

#include "camera.h"
#include "object.h"
#include "models.h"
#include "renderer.h"
#include "rendertools.h"

#include "demo.c"
#include "game.h"
#include "scene.h"

//*****************************************************************************

/* storage for packed object lists */
int packed_olist1[160];
int packed_olist2[160];

N3DAngles objangles;

N3DObject testobj;

//*****************************************************************************

int main() {
		int drawbuf;			/* flag: 0 means first buffer, 1 means second */
	Bitmap *curwindow;		/* pointer to output bitmap */
	N3DAngles* curangles;	/* which set of angles (viewer or camera) are being manipulated */
	long buts, shotbuts;		/* joystick buttons pushed */
	long curframe;			/* current frame counter */
	long framespersecond;		/* frames per second counter */
	long time;			/* elapsed time */
	char buf[256];			/* scratch buffer for sprintf */

	/* build packed versions of the two object lists */
	/* (output is double buffered)			 */
	OLbldto(buf1_olist, packed_olist1);
	OLbldto(buf2_olist, packed_olist2);
	
	N3DGameObject obj, obj2;
	N3DGameObjectInit(&obj, N3DGetModel(0));
	N3DGameObjectInit(&obj2, N3DGetModel(4));


	/* initialize the video */
	OLPset(packed_olist2);
	
	N3DInit();

	/* clear the drawing area to black */
	memset(DATA1, 0x00, OBJWIDTH*(long) OBJHEIGHT * 2L * 3);	/* clear screen to black */


	drawbuf = 0;			/* draw on buffer 1, while displaying buffer 2 */

	CameraInit();

	/* initially all rotation and movement is applied to the object,
	   not the viewer
	 */
	curangles = &(obj.angles);


	/* initialize timing information */
	curframe = _timestamp;			/* timestamp is updated every vblank, and is elapsed time in 300ths of a second */
	framespersecond = 1;

	/* loop forever */
	for(;;) {
		/* select bitmap for drawing */
		curwindow = (drawbuf) ? &scrn2 : &scrn1;

		/* generate transformation matrices from angles */
		CameraUpdate();
		N3DGameObjectUpdate(&obj);
		N3DGameObjectUpdate(&obj2);

		/* clear the current draw buffer */
		N3DClear(curwindow);

		/* now draw the object, timing how long it takes */
		/* NOTE: the clock() function uses unsupported hardware
		 * mechanisms; it happens to work on current developer
		 * machines, but will fail on some Jaguars. If this
		 * were production code, we would have to use a
		 * different timing mechanism!
		 */
		time = clock();

		N3DRender(curwindow, &(obj.n3dobj));
		N3DRender(curwindow, &(obj2.n3dobj));

		time = clock() - time;

		/* Pring some statistics into the draw buffer (curwindow) */
		/* FNTstr draws text; see font.c for details */
		//FNTstr(20, 0, rend[currender].name, curwindow->data, curwindow->blitflags, usefnt, 0x7fff, 0 );

		sprintf(buf, "%d faces/%d fps", obj.n3dobj.data->numpolys, (int)framespersecond);
		FNTstr(20, 12, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0);

		/* there are MHZ * 100 ticks in a second, and drawing 1 poly takes
		 * (time/testobj.data->numpolys) ticks,
		 * so the throughput is 100*MHZ/(time/testobj->data.numpolys)
		 */
		//sprintf(buf, "%ld polys/sec", 100L * ( (MHZ * testobj.data->numpolys)/time) );
		//FNTstr(20, 24, buf, curwindow->data, curwindow->blitflags, usefnt, 0x27ff, 0 );

		//sprintf(buf, "x=%d  y=%d  z=%d", objangles.xpos, objangles.ypos, objangles.zpos);
		//FNTstr(20, 24, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0);

		/* timing statistics */
		sprintf(buf, "%d draw time", time);
		FNTstr(20, 36, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0 );

		/* buts will contain all buttons currently pressed */
		/* shotbuts will contain the ones that are pressed now, but weren't
		   pressed last time JOYget() was called
		 */
		buts = JOYget(JOY1);
		shotbuts = JOYedge(JOY1);


		/* now interpret the user's keypresses */
#define DELTA 4
		if (buts & FIRE_A) {
			curangles->zpos -= 0x10;
		} else if (buts & FIRE_B) {
			curangles->zpos -= 0x02;
		} else if (buts & FIRE_C) {
			curangles->zpos += 0x10;
		} else if (buts & KEY_2) {
			curangles->ypos -= DELTA;
		} else if (buts & KEY_8) {
			curangles->ypos += DELTA;
		} else if (buts & KEY_4) {
			curangles->xpos -= DELTA;
		} else if (buts & KEY_6) {
			curangles->xpos += DELTA;
		}

#define ROTINC 0x10
		if (buts & JOY_UP) {
			curangles->alpha -= ROTINC;
		} else if (buts & JOY_DOWN) {
			curangles->alpha += ROTINC;
		}
		if (buts & JOY_LEFT) {
			curangles->beta -= ROTINC;
		} else if (buts & JOY_RIGHT) {
			curangles->beta += ROTINC;
		}
		if (buts & KEY_1) {
			curangles->gamma -= ROTINC;
		} else if (buts & KEY_3) {
			curangles->gamma += ROTINC;
		}

		/* if the 0 key is held down, move the camera rather than
		 * the object
		 */
		if (buts & KEY_0) {
			curangles = &g_cameraAngles;
		} else {
			curangles = &(obj.angles);
		}

		if (shotbuts & OPTION) {
			N3DGameObjectInit(&obj, N3DNextModel());
		}

		if (shotbuts & KEY_H) {
			N3DToolsNextRenderer();
		}

		if (shotbuts & KEY_S) {
		}

		/* display the buffer we just drew */
		OLPset(drawbuf ? packed_olist2 : packed_olist1);

		/* wait for vblank */
		N3DSwap();

		/* calculate frames per second, etc. */
		framespersecond = 300/(_timestamp - curframe);
		curframe = _timestamp;

		/* switch drawing buffers */
		drawbuf = !drawbuf;
	}

 	GameInit();
	SceneIntro();

 	while (true) {
 		GameReset();
		SceneTitle();

		while (true) {
			SceneOptions();

			GameStart();
			SceneStart();

		  	while (true) {
		 		GameInput();
		 		GameLogic();
	 	  		GameRender();
			}

			SceneResults();
			GameResult();
		}

		GameStop();
		SceneStop();
	}

	return 0;
}
