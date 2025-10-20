#include <SDL2/SDL.h>
#include <math.h>

void draw_circle(SDL_Renderer* renderer, float cx, float cy, float radius, int segments,
                 Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if (dx * dx + dy * dy <= radius * radius)
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
        }
    }
}
