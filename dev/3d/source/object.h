#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//*****************************************************************************

#include "n3d.h"

#include "decl/math.h"
#include "decl/model.h"

//*****************************************************************************

typedef struct GameObject {
	N3DObject n3dobj;
	N3DModel* model;
	N3DAngles angles;
} N3DGameObject;

//*****************************************************************************

extern void N3DGameObjectInit(N3DGameObject*, N3DModel*);
extern void N3DGameObjectUpdate();

#endif
