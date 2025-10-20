#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>

typedef struct {
    float x;
    float y;
    float vx;
    float vy;
    float radius;
    float mass;
    SDL_Color color;
} Particle;

void particle_update(Particle* p, float dt, float gravity);
void particle_collide(Particle* p1, Particle* p2);
#endif
