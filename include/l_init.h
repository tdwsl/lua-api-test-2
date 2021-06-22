#ifndef SLGE_INIT
#define SLGE_INIT

#include <lua.h>
#include "display.h"

extern int init_windowWidth, init_windowHeight;
extern char init_texturePaths[MAX_TEXTURES][40], init_windowTitle[40];

void doInit(lua_State *l);

#endif
