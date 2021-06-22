#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "display.h"
#include "l_init.h"
#include "l_draw.h"

int main(int argc, char **args)
{
	char filename[40];
	sprintf(filename, "main.lua");

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	lua_newtable(lua);
	lua_setglobal(lua, "slge");
	luaL_dofile(lua, filename);
	doInit(lua);
	addDrawFunctions(lua);

	initSDL();
	for(int i = 0; init_texturePaths[i][0] != 0; i++)
		loadTexture(init_texturePaths[i]);
	int lastUpdate = SDL_GetTicks();
	SDL_Event event;
	bool quit = false;
	bool redraw = true;

	while(!quit)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}

		int currentTime = SDL_GetTicks();
		while(currentTime - lastUpdate > 10)
		{
			redraw = true;
			lastUpdate += 10;
		}
		if(redraw)
		{
			doDraw(lua);
			redraw = false;
		}
	}

	lua_close(lua);
	endSDL();
	return 0;
}
