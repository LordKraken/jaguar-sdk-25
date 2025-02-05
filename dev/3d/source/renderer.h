#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
/* (1) The name of the renderer
 * (2) The GPU package to load
 * (3) Entry point for that
 * (4) Are textures in normal format (0) or relative to 0x80 (1)
 */
typedef struct Renderer {
	char* name;
	long* gpucode;
	void (*gpuenter)();
	short texflag;
	short null;							/* here for padding only */
} SRenderer;

extern SRenderer* g_currentRenderer;

//*****************************************************************************

/* NOTE: clock() is useful only for debugging; it works on
 * current developer consoles, but may fail on production
 * units and/or future Jaguar consoles!
 */
extern unsigned long clock(void);		/* timer function using the PIT */

//*****************************************************************************

extern long params[];					/* long-aligned parameter block for the GPU */
extern long proftime[];					/* timing information */
extern long _timestamp;					/* library count of number of 300ths of a second elapsed */

//*****************************************************************************

extern void N3DInit();
extern void N3DClear();
extern void N3DRender();
extern void N3DSwap();
extern void N3DDebug();

#endif
