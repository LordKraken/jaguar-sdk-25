#ifndef _RENDER_DEF_H_
#define _RENDER_DEF_H_

//*****************************************************************************

typedef enum TextureMode {
	TEXTURE_MODE_NORMAL = 0,
	TEXTURE_MODE_SHADING = 1,
} ETextureMode;

typedef enum RenderMode {
	RENDER_MODE_WIREFRAME,
	RENDER_MODE_GOURAUD,
	RENDER_MODE_GOURAUD_PHRASE,
	RENDER_MODE_TEXTURE_UNSHADED,
	RENDER_MODE_TEXTURE_FLATSHADED,
	RENDER_MODE_TEXTURE_GOURAUD,
	RENDER_MODE_COUNT,
} ERenderMode;

//*****************************************************************************
/* (1) The name of the renderer
 * (2) The GPU package to load
 * (3) Entry point for that
 * (4) Are textures in normal format (0) or relative to 0x80 (1)
 */
typedef struct Renderer {
	ERenderMode mode;
	ETextureMode texmode;
	long* gpucode;
	void (*gpuenter)();
} SRenderer;

//*****************************************************************************

extern SRenderer* g_renderer;

#endif
