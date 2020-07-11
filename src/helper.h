#ifndef _HELPER_H_
#define _HELPER_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Window *Window;
extern SDL_Renderer *Renderer;
// extern bool running;

void init(void);
void exit_(void);

#endif
