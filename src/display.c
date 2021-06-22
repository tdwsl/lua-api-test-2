#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.h"
#include "l_init.h"
#include "l_draw.h"

SDL_Renderer *g_renderer = NULL;
SDL_Window *g_window = NULL;
SDL_Texture *g_textures[MAX_TEXTURES] = {NULL};

void initSDL()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "failed to initialize sdl\nerror: %s\n", SDL_GetError());
		exit(1);
	}

	g_window = SDL_CreateWindow(init_windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, init_windowWidth, init_windowHeight, SDL_WINDOW_SHOWN);
	if(!g_window)
	{
		fprintf(stderr, "failed to create window\nerror: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_SOFTWARE);
	if(!g_renderer)
	{
		fprintf(stderr, "failed to create renderer\nerror: %s\n", SDL_GetError());
		SDL_DestroyWindow(g_window);
		g_window = NULL;
		SDL_Quit();
		exit(1);
	}
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xff);
}

void endSDL()
{
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	SDL_DestroyRenderer(g_renderer);
	g_renderer = NULL;

	for(int i = 0; i < MAX_TEXTURES; i++)
		if(g_textures[i])
		{
			SDL_DestroyTexture(g_textures[i]);
			g_textures[i] = NULL;
		}

	SDL_Quit();
}

int loadTexture(const char *filename)
{
	SDL_Surface *loadedSurface = SDL_LoadBMP(filename);
	if(!loadedSurface)
	{
		fprintf(stderr, "failed to load \"%s\"\n", filename);
		endSDL();
		exit(1);
	}
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xff, 0x00, 0xff));

	int i;
	for(i = 0; g_textures[i] != NULL; i++);
	g_textures[i] = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	if(!g_textures[i])
	{
		fprintf(stderr, "failed to create texture from \"%s\"\n", filename);
		endSDL();
		exit(1);
	}

	return i;
}
