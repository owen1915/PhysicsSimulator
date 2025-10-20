#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "window.h"
#include "particle.h"
#include "draw.h"


// forward declaration (if draw_circle is in another file)
void draw_circle(SDL_Renderer* renderer, float cx, float cy, float radius, int segments,
                 Uint8 r, Uint8 g, Uint8 b, Uint8 a);

int main() {
    GameWindow window;
    if (!init_window(&window, "Physics Simulation", 800, 600))
        return 1;

    srand(time(NULL)); // seed random

    int amnt_of_particles = 100;
    Particle particles[amnt_of_particles];
    for (int i = 0; i < amnt_of_particles; i++) {
        particles[i].x = rand() % 800;
        particles[i].y = 100;
        particles[i].radius = (rand() % 30) + 5;
        particles[i].mass = particles[i].radius * 0.5f; 
        particles[i].vx = (rand() % 400 - 100);  // random x velocity
        particles[i].vy = (rand() % 200 - 100);  // random y velocity   
        particles[i].color = (SDL_Color){255, 0, 0, 255};
    }

    int running = 1;
    SDL_Event event;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                running = 0;

        // clear screen
        SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
        SDL_RenderClear(window.renderer);

        // main loop
        float dt = 1.0f / 60.0f;
        float gravity = 500.0f;
        int substeps = 8;          // << increase for stability
        float sub_dt = dt / substeps;

        for (int s = 0; s < substeps; s++) {
            for (int i = 0; i < amnt_of_particles; i++)
                particle_update(&particles[i], sub_dt, gravity);

            for (int i = 0; i < amnt_of_particles; i++) {
                for (int j = i + 1; j < amnt_of_particles; j++)
                    particle_collide(&particles[i], &particles[j]);
            }
        }
        
        // draw all particles
        for (int i = 0; i < amnt_of_particles; i++) {
            draw_circle(window.renderer,
                        particles[i].x,
                        particles[i].y,
                        particles[i].radius,
                        particles[i].mass,
                        particles[i].color.r,
                        particles[i].color.g,
                        particles[i].color.b,
                        particles[i].color.a);
        }

        SDL_RenderPresent(window.renderer);

        // cap framerate
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    close_window(&window);
    return 0;
}
