#include "gameobject.h"

#include "globals.h"

//*****************************************************************************

void N3DGameObjectInit(N3DGameObject* go, N3DModel* model) {
	memset(go, 0, sizeof(N3DGameObject));

	if (model) {
		go->n3dobj.data = model->n3ddata;
		go->model = model;
		go->angles.xpos = go->model->initx;
		go->angles.ypos = go->model->inity;
		go->angles.zpos = go->model->initz;
	}

	N3DGameObjectUpdate(go);
}

//*****************************************************************************

void N3DGameObjectUpdate(N3DGameObject* go) {
	mkMatrix(&(go->n3dobj.M), &(go->angles));
}
