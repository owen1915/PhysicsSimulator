#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

void draw_circle(SDL_Renderer* renderer, float cx, float cy, float radius, int segments,
                 Uint8 r, Uint8 g, Uint8 b, Uint8 a);

#endif
