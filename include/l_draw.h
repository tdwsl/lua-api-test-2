#ifndef SLGE_UPDATE
#define SLGE_UPDATE

#include <lua.h>
#include "display.h"

void addDrawFunctions(lua_State *l);
void doDraw(lua_State *l);

#endif
