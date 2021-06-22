#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "display.h"
#include "l_draw.h"

bool g_drawing = false;

void ensureDrawing(lua_State *l)
{
	if(g_drawing)
		return;
	luaL_error(l, "drawing functions must take place in slge.draw");
	fprintf(stderr, "%s\n", lua_tostring(l, -1));
	endSDL();
	exit(1);
}

int l_drawTexture(lua_State *l)
{
	ensureDrawing(l);
	int id = lua_tointeger(l, 1);
	SDL_Rect dst;
	SDL_QueryTexture(g_textures[id], NULL, NULL, &dst.w, &dst.h);
	dst.x = lua_tointeger(l, 2);
	dst.y = lua_tointeger(l, 3);
	lua_pop(l, 3);
	SDL_RenderCopy(g_renderer, g_textures[id], NULL, &dst);
	return 0;
}

int l_drawTextureRegion(lua_State *l)
{
	ensureDrawing(l);
	int id = lua_tointeger(l, 1);
	SDL_Rect src, dst;
	src.x = lua_tointeger(l, 2);
	src.y = lua_tointeger(l, 3);
	src.w = lua_tointeger(l, 4);
	src.h = lua_tointeger(l, 5);
	dst.x = lua_tointeger(l, 6);
	dst.y = lua_tointeger(l, 7);
	dst.w = lua_tointeger(l, 8);
	dst.h = lua_tointeger(l, 9);
	lua_pop(l, 9);
	SDL_RenderCopy(g_renderer, g_textures[id], &src, &dst);
	return 0;
}

void addDrawFunctions(lua_State *l)
{
	lua_pushcfunction(l, l_drawTexture);
	lua_setglobal(l, "draw_texture");
	lua_pushcfunction(l, l_drawTextureRegion);
	lua_setglobal(l, "draw_texture_region");
}

void doDraw(lua_State *l)
{
	g_drawing = true;
	SDL_RenderClear(g_renderer);
	if(luaL_dostring(l, "if slge.draw~=nil then slge.draw() end"))
	{
		fprintf(stderr, "%s\n", lua_tostring(l, -1));
		endSDL();
		exit(1);
	}
	SDL_RenderPresent(g_renderer);
	g_drawing = false;
}
