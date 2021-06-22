#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "display.h"
#include "l_init.h"

int init_windowWidth = 640, init_windowHeight = 480;
char init_texturePaths[MAX_TEXTURES][40] = {""}, init_windowTitle[40] = "SLGE Game";

int l_setInitWindowSize(lua_State *l)
{
	init_windowWidth = lua_tointeger(l, 1);
	init_windowHeight = lua_tointeger(l, 2);
	lua_pop(l, 2);
	return 0;
}

int l_setInitWindowTitle(lua_State *l)
{
	sprintf(init_windowTitle, "%s", lua_tostring(l, 1));
	lua_pop(l, 1);
	return 0;
}

int l_queueLoadTexture(lua_State *l)
{
	int i;
	for(i = 0; init_texturePaths[i][0] != 0; i++);
	sprintf(init_texturePaths[i], "%s", lua_tostring(l, 1));
	lua_pop(l, 1);
	lua_pushinteger(l, i);
	return 1;
}

void doInit(lua_State *l)
{
	lua_pushcfunction(l, l_setInitWindowSize);
	lua_setglobal(l, "set_window_size");
	lua_pushcfunction(l, l_setInitWindowTitle);
	lua_setglobal(l, "set_window_title");
	lua_pushcfunction(l, l_queueLoadTexture);
	lua_setglobal(l, "load_texture");

	if(luaL_dostring(l, "if slge.init~=nil then slge.init() end"))
	{
		fprintf(stderr, "%s\n", lua_tostring(l, -1));
		lua_close(l);
		exit(1);
	}

	lua_getglobal(l, "set_window_size");
	lua_getglobal(l, "set_window_title");
	lua_getglobal(l, "load_texture");
	lua_pop(l, 3);
}
