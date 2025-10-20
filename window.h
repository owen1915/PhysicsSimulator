#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} GameWindow;

int init_window(GameWindow* gw, const char* title, int width, int height);
void close_window(GameWindow* gw);
void window_update(GameWindow* gw);

#endif
