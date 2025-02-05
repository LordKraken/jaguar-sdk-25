//*****************************************************************************
// PROJECT TOP GEAR
//*****************************************************************************

#include "decl/globals.h"
#include "decl/fonts.h"
#include "decl/math.h"

#include "renderer.h"
#include "rendertools.h"

#include "models.h"

#include "demo.c"
#include "game.h"
#include "scene.h"

//*****************************************************************************

/****************************************************************
 *	External GPU references					*
 ****************************************************************/

extern long wfcode[], 
	gourcode[], 
	gourphrcode[],
	texcode[], 
	flattexcode[], 
	gstexcode[];

extern void wfenter(), 
	gourenter(), 
	gourphrenter(),
	texenter(), 
	flattexenter(), 
	gstexenter();

/* renderers supported */
SRenderer rend[] = {
	{"Wire Frames", wfcode, wfenter, 0},
	{"Gouraud Only", gourcode, gourenter, 0},
	{"Phrase Mode Gouraud", gourphrcode, gourphrenter, 0},
	{"Unshaded Textures", texcode, texenter, 0},
	{"Flat Shaded Textures", flattexcode, flattexenter, 0},
	{"Gouraud Shaded Textures", gstexcode, gstexenter, 1},
};
#define maxrenderer (sizeof(rend)/sizeof(SRenderer))

/* storage for packed object lists */
int packed_olist1[160];
int packed_olist2[160];

SAngles camangles, objangles;

N3DObject testobj;

//*****************************************************************************

int main() {
		int drawbuf;			/* flag: 0 means first buffer, 1 means second */
	Bitmap *curwindow;		/* pointer to output bitmap */
	Matrix cammatrix;		/* camera matrix */
	SAngles* curangles;	/* which set of angles (viewer or camera) are being manipulated */
	long buts, shotbuts;		/* joystick buttons pushed */
	long curframe;			/* current frame counter */
	long framespersecond;		/* frames per second counter */
	long time;			/* elapsed time */
	int currender;			/* current renderer in use (index into table) */
	int curmodel;			/* current model in use (index into table) */
	char buf[256];			/* scratch buffer for sprintf */

	/* build packed versions of the two object lists */
	/* (output is double buffered)			 */
	OLbldto(buf1_olist, packed_olist1);
	OLbldto(buf2_olist, packed_olist2);

	/* initialize the video */
	OLPset(packed_olist2);
	
	N3DInit();

	/* clear the drawing area to black */
	memset(DATA1, 0x00, OBJWIDTH*(long)OBJHEIGHT*2L*3);	/* clear screen to black */


	drawbuf = 0;			/* draw on buffer 1, while displaying buffer 2 */
	currender = 0;			/* initial render package to use */
	curmodel = 0;			/* initial model to draw */

	/* initialize the test object */
	memset(&testobj, 0, sizeof(testobj));
	testobj.data = g_models[curmodel].data;
	objangles.xpos = g_models[curmodel].initx;	/* get initial position */
	objangles.ypos = g_models[curmodel].inity;
	objangles.zpos = g_models[curmodel].initz;

	/* no rotation, initially */
	objangles.alpha = objangles.beta = objangles.gamma = 0;

	/* set up the viewer's position */
	camangles.alpha = camangles.beta = camangles.gamma = 0;
	camangles.xpos = camangles.ypos = 0;
	camangles.zpos = 0;
	mkMatrix(&cammatrix, &camangles);

	/* initially all rotation and movement is applied to the object,
	   not the viewer
	 */
	curangles = &objangles;


	/* initialize timing information */
	curframe = _timestamp;			/* timestamp is updated every vblank, and is elapsed time in 300ths of a second */
	framespersecond = 1;

	/* initially textures are unshaded */
	texturestate = 0;



	/* set up the textures for the first renderer */
	RenderToolsFixTextures(rend[currender].texflag);

	/* loop forever */
	for(;;) {
		/* select bitmap for drawing */
		curwindow = (drawbuf) ? &scrn2 : &scrn1;

		/* generate transformation matrices from angles */
		mkMatrix(&testobj.M, &objangles);

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

		N3DRender(curwindow, &testobj, &cammatrix, &rend[currender]);

		time = clock() - time;

		/* Pring some statistics into the draw buffer (curwindow) */
		/* FNTstr draws text; see font.c for details */
		//FNTstr(20, 0, rend[currender].name, curwindow->data, curwindow->blitflags, usefnt, 0x7fff, 0 );

		sprintf(buf, "%d faces/%d fps", testobj.data->numpolys, (int)framespersecond);
		FNTstr(20, 12, buf, curwindow->data, curwindow->blitflags, usefnt, 0x27ff, 0 );

		/* there are MHZ * 100 ticks in a second, and drawing 1 poly takes
		 * (time/testobj.data->numpolys) ticks,
		 * so the throughput is 100*MHZ/(time/testobj->data.numpolys)
		 */
		//sprintf(buf, "%ld polys/sec", 100L * ( (MHZ * testobj.data->numpolys)/time) );
		//FNTstr(20, 24, buf, curwindow->data, curwindow->blitflags, usefnt, 0x27ff, 0 );


		/* timing statistics */
		//sprintf(buf, "%08lx draw time", time);
		//FNTstr(20, 36, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0 );

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
			curangles = &camangles;
			mkMatrix(&cammatrix, &camangles);
		} else {
			curangles = &objangles;
			mkMatrix(&cammatrix, &camangles);
		}

		if (shotbuts & OPTION) {
			curmodel++;
			if (curmodel >= g_modelsCount)
				curmodel = 0;
			testobj.data = g_models[curmodel].data;

			objangles.xpos = g_models[curmodel].initx;
			objangles.ypos = g_models[curmodel].inity;
			objangles.zpos = g_models[curmodel].initz;
			objangles.alpha = objangles.beta = objangles.gamma = 0;
		}

		if (shotbuts & KEY_H) {
			currender++;
			if (currender >= maxrenderer)
				currender = 0;
			RenderToolsFixTextures(rend[currender].texflag);
		}

		if (shotbuts & KEY_S) {
			if (currender == 0)
				currender = maxrenderer;
			currender--;
			RenderToolsFixTextures(rend[currender].texflag);
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
