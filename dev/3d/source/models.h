#ifndef _GAME_MODELS_H_
#define _GAME_MODELS_H_

//*****************************************************************************

#include "decl/model.h"

//*****************************************************************************

extern N3DModel g_models[];
extern const int g_modelsCount;
extern N3DModel* g_currentModel;

//*****************************************************************************

extern N3DModel* N3DGetModel(short);
extern N3DModel* N3DNextModel();

#endif
