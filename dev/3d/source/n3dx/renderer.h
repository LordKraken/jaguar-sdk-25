#ifndef _N3D_RENDERER_H_
#define _N3D_RENDERER_H_

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
extern void N3DMode();
extern void N3DBuild();
extern void N3DRender();
extern void N3DDebug();

#endif
