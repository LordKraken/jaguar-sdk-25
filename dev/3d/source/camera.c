#include "camera.h"

#include "decl/math.h"

//*****************************************************************************

N3DAngles g_cameraAngles;
Matrix g_cameraMatrix;

//*****************************************************************************

void N3DCameraInit(void) {
	//memset
	g_cameraAngles.alpha = 0;
	g_cameraAngles.beta = 0;
	g_cameraAngles.gamma = 0;

	g_cameraAngles.xpos = 0;
	g_cameraAngles.ypos = 0;
	g_cameraAngles.zpos = 0;

	N3DCameraUpdate();
}

//*****************************************************************************

void N3DCameraUpdate(void) {
	mkMatrix(&g_cameraMatrix, &g_cameraAngles);
}

//*****************************************************************************

void N3DCameraForward(short dz) {
	g_cameraAngles.xpos += dz * sin(g_cameraAngles.beta) / 325;
	g_cameraAngles.zpos += dz * cos(g_cameraAngles.beta) / 325;
}

//*****************************************************************************

void N3DCameraMove(short dx, short dy, short dz) {
	g_cameraAngles.xpos += dx;
	g_cameraAngles.ypos += dy;
	g_cameraAngles.zpos += dz;
}

//*****************************************************************************

void N3DCameraRotate(short rx, short ry, short rz) {
	g_cameraAngles.alpha += rx;
	g_cameraAngles.beta += ry;
	g_cameraAngles.gamma += rz;
}
