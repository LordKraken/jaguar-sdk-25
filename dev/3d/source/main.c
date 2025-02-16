//*****************************************************************************
// PROJECT N3D for ATARI JAGUAR
//*****************************************************************************

#include "n3dx/globals.h"
#include "n3dx/camera.h"
#include "n3dx/gameobject.h"
#include "n3dx/math.h"
#include "n3dx/modeldata.h"
#include "n3dx/renderbuffers.h"
#include "n3dx/rendertools.h"
#include "n3dx/renderer.h"

#include "misc/fonts.h"

#include "game.h"
#include "scene.h"
#include "tools.h"

// 1/100th of the clock speed
#define MHZ 							265900L

//*****************************************************************************

/* storage for packed object lists */
// union olist = 36 bytes
void* packed_olist1;
void* packed_olist2;

//*****************************************************************************

int main() {
	int drawbuf;			/* flag: 0 means first buffer, 1 means second */
	long buts, shotbuts;		/* joystick buttons pushed */
	long curframe;			/* current frame counter */
	long framespersecond;		/* frames per second counter */
	long time;			/* elapsed time */
	char buf[256];			/* scratch buffer for sprintf */

	N3DInit();

	/* build packed versions of the two object lists */
	/* (output is double buffered) */
	packed_olist1 = OLbuild(g_olistScreen1);
	packed_olist2 = OLbuild(g_olistScreen2);
	//OLbldto(g_olistScreen1, packed_olist1);
	//OLbldto(g_olistScreen2, packed_olist2);

	/* initialize the video */
	OLPset(packed_olist2);
	
	N3DGameObject obj, obj2;
	N3DGameObjectInit(&obj, N3DGetModel(1));
	N3DGameObjectInit(&obj2, N3DGetModel(3));
//while (true);
	drawbuf = 0;			/* draw on buffer 1, while displaying buffer 2 */

	// Scene specific
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

				// Animation test
				obj2.angles.beta += 0x10;
				N3DGameObjectUpdate(&obj2);

				/* generate transformation matrices from angles */
				N3DCameraUpdate();

				/* clear the current draw buffer */
				N3DScreenClear(g_screen);
#ifdef N3D_DEBUG_CONSOLE
				N3DScreenClear(g_screenDebug);
#endif
				/* now draw the object, timing how long it takes */
				/* NOTE: the clock() function uses unsupported hardware
				 * mechanisms; it happens to work on current developer
				 * machines, but will fail on some Jaguars. If this
				 * were production code, we would have to use a
				 * different timing mechanism!
				 */
				time = clock();

				N3DRender(g_screen, &(obj.n3dobj));
				N3DRender(g_screen, &(obj2.n3dobj));

				time = clock() - time;

				sprintf(buf, "%d faces/%d fps", obj.n3dobj.data->numpolys + obj2.n3dobj.data->numpolys, (int)framespersecond);
				//FNTstr(20, 12, buf, debugWindow->data, debugWindow->blitflags, usefnt, 0xf0ff, 0);

				/* there are MHZ * 100 ticks in a second, and drawing 1 poly takes (time/testobj.data->numpolys) ticks,
				 * so the throughput is 100*MHZ/(time/testobj->data.numpolys) */
				//sprintf(buf, "%ld polys/sec", 100L * ( (MHZ * testobj.data->numpolys)/time) );
				//sprintf(buf, "rx=%d  ry=%d  rz=%d", g_cameraAngles.alpha, g_cameraAngles.beta, g_cameraAngles.gamma);
				//FNTstr(20, 36, buf, curwindow->data, curwindow->blitflags, usefnt, 0xf0ff, 0 );

				buts = JOYget(JOY1);
				shotbuts = JOYedge(JOY1);
				int dz = 1;

				if (buts & JOY_FIRE_B) {
					if (buts & JOY_UP) {
						N3DCameraMove(0, 0x10, 0);
					}
					else if (buts & JOY_DOWN) {
						N3DCameraMove(0, -0x10, 0);
					}
				}
				else if (buts & JOY_FIRE_C) {
					dz = 4;
				}
				
				if (buts & JOY_FIRE_A) {
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

				if (shotbuts & JOY_OPTION) {
					N3DGameObjectInit(&obj, N3DNextModel());
				}

				if (shotbuts & KEY_HASH) {
					N3DToolsNextRenderer();
				}

				if (shotbuts & KEY_STAR) {
					N3DGameObjectInit(&obj, N3DGetModel(1));
				}


				/* display the buffer we just drew */
				OLPset(drawbuf ? packed_olist2 : packed_olist1);

				/* wait for vblank */
				N3DScreenSwap();

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
