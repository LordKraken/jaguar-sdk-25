//*****************************************************************************
// PROJECT TOP GEAR
//*****************************************************************************

#include "joypad.h"

#include "decl/globals.h"
#include "decl/fonts.h"
#include "decl/math.h"

#include "camera.h"
#include "object.h"
#include "models.h"
#include "renderer.h"
#include "rendertools.h"
#include "screen.c"

#include "game.h"
#include "scene.h"
#include "tools.h"

//*****************************************************************************

/* storage for packed object lists */
int packed_olist1[160];
int packed_olist2[160];

//*****************************************************************************

int main() {
		int drawbuf;			/* flag: 0 means first buffer, 1 means second */
	long buts, shotbuts;		/* joystick buttons pushed */
	long curframe;			/* current frame counter */
	long framespersecond;		/* frames per second counter */
	long time;			/* elapsed time */
	char buf[256];			/* scratch buffer for sprintf */

	N3DGameObject obj, obj2;
	N3DGameObjectInit(&obj, N3DGetModel(1));
	N3DGameObjectInit(&obj2, N3DGetModel(3));

	/* build packed versions of the two object lists */
	/* (output is double buffered)			 */
	OLbldto(g_olistScreen1, packed_olist1);
	OLbldto(g_olistScreen2, packed_olist2);

	/* initialize the video */
	OLPset(packed_olist2);
	
	/* clear the drawing area to black */
	memset(SCREEN_BUFFER_1, 0x00, 320 * (long) 240 * 3);	/* clear screen to black */
	memset(SCREEN_BUFFER_2, 0x00, 320 * (long) 240 * 3);

	N3DInit();

	drawbuf = 0;			/* draw on buffer 1, while displaying buffer 2 */

	N3DCameraInit();
	N3DCameraMove(0, -0x100, -0x400);
	N3DCameraRotate(-0x20, 0, 0);

	/* initialize timing information */
	curframe = _timestamp;			/* timestamp is updated every vblank, and is elapsed time in 300ths of a second */
	framespersecond = 1;

	GameInit();
	SceneIntro();

 	while (true) {
 		GameReset();
		SceneTitle();

		while (!IsGameOver()) {
			SceneOptions();

			GameStart();
			SceneStart();

			while (!IsLevelOver()) {
				/* select bitmap for drawing */
				Bitmap* curwindow = (drawbuf) ? &g_bitmapScreen2 : &g_bitmapScreen1;
				Bitmap* debugWindow = (drawbuf) ? &g_debugScreen2 : &g_debugScreen1;

				obj2.angles.beta += 0x10;

				/* generate transformation matrices from angles */
				N3DCameraUpdate();
				N3DGameObjectUpdate(&obj);
				N3DGameObjectUpdate(&obj2);

				/* clear the current draw buffer */
				N3DClear(curwindow);
				N3DClear(debugWindow);

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

				sprintf(buf, "%d faces/%d fps", obj.n3dobj.data->numpolys + obj2.n3dobj.data->numpolys, (int)framespersecond);
				FNTstr(20, 12, buf, debugWindow->data, debugWindow->blitflags, usefnt, 0xf0ff, 0);

				/* there are MHZ * 100 ticks in a second, and drawing 1 poly takes
				 * (time/testobj.data->numpolys) ticks,
				 * so the throughput is 100*MHZ/(time/testobj->data.numpolys)
				 */
				//sprintf(buf, "%ld polys/sec", 100L * ( (MHZ * testobj.data->numpolys)/time) );
				//FNTstr(20, 24, buf, curwindow->data, curwindow->blitflags, usefnt, 0x27ff, 0 );

				sprintf(buf, "x=%d  y=%d  z=%d", g_cameraAngles.xpos, g_cameraAngles.ypos, g_cameraAngles.zpos);
				//FNTstr(20, 24, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0);
				//sprintf(buf, "rx=%d  ry=%d  rz=%d", g_cameraAngles.alpha, g_cameraAngles.beta, g_cameraAngles.gamma);
				//FNTstr(20, 36, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0);

				/* timing statistics */
				//sprintf(buf, "%d draw time", time);
				//FNTstr(20, 36, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0 );

				/* buts will contain all buttons currently pressed */
				/* shotbuts will contain the ones that are pressed now, but weren't
				   pressed last time JOYget() was called
				 */
				buts = JOYget(JOY1);
				shotbuts = JOYedge(JOY1);
				int dz = 1;

				if (buts & FIRE_B) {
					if (buts & JOY_UP) {
						N3DCameraMove(0, 0x10, 0);
					}
					else if (buts & JOY_DOWN) {
						N3DCameraMove(0, -0x10, 0);
					}
				}
				else if (buts & FIRE_C) {
					dz = 4;
				}
				
				if (buts & FIRE_A) {
					if (buts & JOY_UP) {
						N3DCameraRotate(0x10, 0, 0);
					}
					else if (buts & JOY_DOWN) {
						N3DCameraRotate(-0x10, 0, 0);
					}

					if (buts & JOY_LEFT) {
						N3DCameraRotate(0, -0x10, 0);
					}
					else if (buts & JOY_RIGHT) {
						N3DCameraRotate(0, 0x10, 0);
					}
				}
				else {
					if (buts & JOY_UP) {
						N3DCameraForward(dz);
					}
					else if (buts & JOY_DOWN) {
						N3DCameraForward(-dz);
					}

					if (buts & JOY_LEFT) {
						N3DCameraStrife(dz);
					}
					else if (buts & JOY_RIGHT) {
						N3DCameraStrife(-dz);
					}
				}

				if (shotbuts & OPTION) {
					N3DGameObjectInit(&obj, N3DNextModel());
				}

				if (shotbuts & KEY_H) {
					N3DToolsNextRenderer();
				}

				if (shotbuts & KEY_S) {
					N3DGameObjectInit(&obj, N3DGetModel(1));
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


			  	if (!IsGamePaused()) {
			 		GameInput();
			 		GameLogic();
				}

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
