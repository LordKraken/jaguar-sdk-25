#include "models.h"

//*****************************************************************************

extern N3DObjdata globedata, cube2data, castledata, knightdata, robotdata, shipdata, radardata;

N3DModel g_models[] = {
	{ &globedata, 0, 0, 320, 0 },
	{ &cube2data, 0, 0, 512, 0 },
	{ &castledata, 0, 0, 8096, 0 },
	{ &knightdata, 0, 0, 1800, 0 },
	{ &robotdata, 0, 0, 2048, 0 },
	{ &shipdata, 0, 0, 1024, 0 },
	{ &radardata, 0, 0, 512, 0 },
};

const int g_modelsCount = sizeof(g_models) / sizeof(N3DModel);

N3DModel* g_currentModel;
short _currentModelId;

//*****************************************************************************

N3DModel* N3DGetModel(short id) {
	_currentModelId = id % g_modelsCount;
	g_currentModel = &g_models[_currentModelId];
	return g_currentModel;
}

//*****************************************************************************

N3DModel* N3DNextModel(void) {
	return N3DGetModel(_currentModelId + 1);
}
