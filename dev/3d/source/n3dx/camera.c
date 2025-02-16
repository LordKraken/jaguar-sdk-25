#include "camera.h"

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

	//g_cameraAngles.gamma = 1024,

	N3DCameraUpdate();
}

//*****************************************************************************

void N3DCameraUpdate(void) {
	mkMatrix(&g_cameraMatrix, &g_cameraAngles);
}

//*****************************************************************************
// sin/cos return values are in PI/1024 => so results should be divived by 325

void N3DCameraForward(short dz) {
	/* Rx 
	g_cameraAngles.xpos += dz * (sin(g_cameraAngles.beta) >> 8);
	g_cameraAngles.zpos += dz * (cos(g_cameraAngles.beta) >> 8);
	*/

	/* Ry
	g_cameraAngles.ypos += dz * (-sin(g_cameraAngles.alpha) >> 8);
	g_cameraAngles.zpos += dz * (cos(g_cameraAngles.alpha) >> 8);
	*/

	// Rx * Ry: value have already been calculated in the camera matrix
	g_cameraAngles.xpos += dz * (g_cameraMatrix.xhead >> 8);
	g_cameraAngles.ypos += dz * (g_cameraMatrix.yhead >> 8);
	g_cameraAngles.zpos += dz * (g_cameraMatrix.zhead >> 8);
}

void N3DCameraStrife(short dz) {
	g_cameraAngles.xpos += dz * (-cos(g_cameraAngles.beta) >> 8); 
	g_cameraAngles.zpos += dz * (sin(g_cameraAngles.beta) >> 8);
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
