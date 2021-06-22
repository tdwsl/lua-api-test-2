#ifndef SLGE_DISPLAY
#define SLGE_DISPLAY

#include <SDL2/SDL.h>

#define MAX_TEXTURES 25

extern SDL_Renderer *g_renderer;
extern SDL_Window *g_window;
extern SDL_Texture *g_textures[MAX_TEXTURES];

void initSDL();
void endSDL();
int loadTexture(const char *filename);

#endif
