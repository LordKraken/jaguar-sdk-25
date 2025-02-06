#ifndef _RENDER_DEF_H_
#define _RENDER_DEF_H_

//*****************************************************************************

typedef enum RendererType {
	RENDERER_TYPE_WIREFRAME,
	RENDERER_TYPE_GOURAUD,
	RENDERER_TYPE_GOURAUD_PHRASE,
	RENDERER_TYPE_TEXTURE_UNSHADED,
	RENDERER_TYPE_TEXTURE_FLATSHADED,
	RENDERER_TYPE_TEXTURE_GOURAUD,
	RENDERER_TYPE_COUNT,
} ERendererType;

//*****************************************************************************
/* (1) The name of the renderer
 * (2) The GPU package to load
 * (3) Entry point for that
 * (4) Are textures in normal format (0) or relative to 0x80 (1)
 */
typedef struct Renderer {
	ERendererType type;
	long* gpucode;
	void (*gpuenter)();
	short texflag;
	short null;							/* here for padding only */
} SRenderer;

//*****************************************************************************

extern SRenderer* g_renderer;

#endif
