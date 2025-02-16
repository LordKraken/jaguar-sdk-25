#ifndef _N3D_ENGINE_CONFIG_H_
#define _N3D_ENGINE_CONFIG_H_


//*****************************************************************************
// DEFAULT ENGINE CONFIG
//*****************************************************************************

// *** ENGINE CUSTOMIZATION ***
//#define N3D_RENDER_QUALITY_

// *** ENGINE FONT OPTIONS ****

// *** SOUND/MUSIC OPTIONS ***

// *** DEBUG OPTIONS ***
//#define N3D_DEBUG_MODE
//#define N3D_DEBUG_CONSOLE
//#define N3D_DEBUG_FPS
//#define N3D_DEBUG_BBOX

// *** GAME OPTIONS ****
//#define N3D_CHEAT_MODE
//#define N3D_CHEAT_IMMORTAL


//*****************************************************************************
// GAME SPECIFIC CONFIG
//*****************************************************************************

#define N3D_GAME_CONFIG_DEFAULT


//*****************************************************************************
// DEFAULT
//*****************************************************************************

#ifdef N3D_GAME_CONFIG_DEFAULT

//#define N3D_DEBUG_MODE
#ifdef N3D_DEBUG_MODE
#define N3D_DEBUG_CONSOLE
#define N3D_DEBUG_FPS
//#define N3D_DEBUG_BBOX
#endif

//#define N3D_CHEAT_MODE
#ifdef N3D_CHEAT_MODE
//#define N3D_CHEAT_IMMORTAL
#endif

#endif

#endif
