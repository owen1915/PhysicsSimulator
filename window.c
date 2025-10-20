#include "window.h"
#include <stdio.h>

int init_window(GameWindow* gw, const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gw->window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width, height,
                                  SDL_WINDOW_SHOWN);
    if (!gw->window) return 0;

    gw->renderer = SDL_CreateRenderer(gw->window, -1, SDL_RENDERER_ACCELERATED);
    if (!gw->renderer) return 0;

    return 1;
}

void window_update(GameWindow* gw) {
    SDL_SetRenderDrawColor(gw->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gw->renderer);
    SDL_RenderPresent(gw->renderer);
}

void close_window(GameWindow* gw) {
    SDL_DestroyRenderer(gw->renderer);
    SDL_DestroyWindow(gw->window);
    SDL_Quit();
}
