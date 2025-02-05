#include "models.h"

//*****************************************************************************

extern N3DObjdata globedata, cubedata, castledata, knightdata, robotdata, shipdata, torusdata;

SModel g_models[] = {
	{ &globedata, 0, 0, 400, 0 },
	{ &cubedata, 0, 0, 400, 0 },
	{ &castledata, 0, 0, 400, 0 },
	{ &knightdata, 0, 0, 600, 0 },
	{ &robotdata, 0, 0, 800, 0 },
	{ &shipdata, 0, 0, 1500, 0 },
	{ &torusdata, 0, 0, 2024, 0 },
};

const int g_modelsCount = sizeof(g_models) / sizeof(SModel);
