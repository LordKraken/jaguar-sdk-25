#include "rendertools.h"

#include "decl/renderdef.h"
#include "models.h"
#include "renderer.h"

//*****************************************************************************

int _lastTextureMode;

//*****************************************************************************

void N3DToolsInit(void) {
	_lastTextureMode = TEXTURE_MODE_NORMAL;
}

//*****************************************************************************

void N3DToolsNextRenderer(void) {
	ERenderMode mode = g_renderer->mode;
	mode = (mode + 1) % RENDER_MODE_COUNT;
	N3DLoad(mode);
}

//*****************************************************************************
/* Adjust all intensities in a texture so that they are relative to 0x80.
 * This is done for renderers that do shading on textures; because of the way 
 * the shading is done, the source data must with intensities as signed offsets
 * to a base intensity (namely 0x80). So before using a renderer that does 
 * shading on textures, this function must be called on all textures in the 
 * model to be rendered. Note that because of the implementation, calling this
 * function twice yields the original texture back. This is handy because it
 * means that we can switch from unshaded textures to shaded ones and then back
 * again, calling this function each time we switch.
 */				
void N3DToolsFixTexture(Bitmap* texture) {
	long* lsrc;
	long numpixs;
	long i;
	numpixs = ((long) texture->width * (long) texture->height) / 4;
	lsrc = (long*) texture->data;

	for (i = 0; i < numpixs; i++) {
		*lsrc++ ^= 0x00800080L;
		*lsrc++ ^= 0x00800080L;
	}
}

//*****************************************************************************
/* Fix up all textures in all models.
 * This is called when switching between renderers; if the new renderer uses 
 * a different texture shading model than the old renderer, then we call
 * fixtexture() on every texture in every model.
 */

void N3DToolsFixAllTextures(int textureMode) {
	if (textureMode == _lastTextureMode) {
		return;
	}

	int i, j;
	for (i = 0; i < g_modelsCount; i++) {
		N3DObjdata* objData = g_models[i].n3ddata;
		for (j = 0; j < objData->nummaterials; j++) {
			Bitmap* bm = objData->materials[j].tmap;
			if (bm) {
				N3DToolsFixTexture(bm);
			}
		}
	}
	_lastTextureMode = textureMode;
}
