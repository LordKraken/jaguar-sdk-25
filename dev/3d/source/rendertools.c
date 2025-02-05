#include "models.h"

#include "n3d.h"

//*****************************************************************************

/* flag for current texture state */
int texturestate;

//*****************************************************************************
/* Adjust all intensities in a texture so that they are
 * relative to 0x80. This is done for renderers that do
 * shading on textures; because of the way the shading is
 * done, the source data must with intensities as signed
 * offsets to a base intensity (namely 0x80). So before using
 * a renderer that does shading on textures, this function
 * must be called on all textures in the model to be rendered.
 * Note that because of the implementation, calling this
 * function twice yields the original texture back. This is
 * handy because it means that we can switch from unshaded
 * textures to shaded ones and then back again, calling this
 * function each time we switch.
 */				
void RenderToolsFixTexture(Bitmap* texture) {
	long *lsrc;
	long numpixs;
	long i;

	numpixs = ((long)texture->width * (long)texture->height)/4;
	lsrc = (long *)texture->data;

	for (i = 0; i < numpixs; i++) {
		*lsrc++ ^= 0x00800080L;
		*lsrc++ ^= 0x00800080L;
	}
}

//*****************************************************************************
/*
 * Fix up all textures in all models.
 * This is called when switching between renderers;
 * if the new renderer uses a different texture
 * shading model than the old renderer, then we
 * call fixtexture() on every texture in every
 * model.
 */
void RenderToolsFixTextures(int newrender) {
	int i, j;
	N3DObjdata* curobj;
	Bitmap* map;

	if (texturestate != newrender) {
		for (i = 0; i < g_modelsCount; i++) {
			curobj = g_models[i].data;
			for (j = 0; j < curobj->nummaterials; j++) {
				map = curobj->materials[j].tmap;
				if (map)
					RenderToolsFixTexture(map);
			}
		}
		texturestate = newrender;
	}
}
