#include "camera.h"

//*****************************************************************************

N3DAngles g_cameraAngles;
Matrix g_cameraMatrix;

//*****************************************************************************

void CameraInit(void) {
	//memset
	g_cameraAngles.alpha = 0;
	g_cameraAngles.beta = 0;
	g_cameraAngles.gamma = 0;

	g_cameraAngles.xpos = 0;
	g_cameraAngles.ypos = 0;
	g_cameraAngles.zpos = 0;

	CameraUpdate();
}

//*****************************************************************************

void CameraUpdate(void) {
	mkMatrix(&g_cameraMatrix, &g_cameraAngles);
}
