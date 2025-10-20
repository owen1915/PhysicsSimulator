#include "particle.h"

void particle_update(Particle* p, float dt, float gravity) {
    // apply gravity (positive gravity pulls down)
    p->vy += gravity * dt;

    // update position using velocity
    p->x += p->vx * dt;
    p->y += p->vy * dt;

    // simple floor collision
    if (p->y > 600 - p->radius) {
        p->y = 600 - p->radius;
        p->vy *= -0.6f; // bounce with some damping
    }

    // simple wall collision
    if (p->x > 800 - p->radius) {
        p->x = 800 - p->radius;
        p->vx = p->vx * -1;
    }
    else if(p->x < 0 + p->radius) {
        p->x = 0 + p->radius;
        p->vx = p->vx * -1;
    }
}

void particle_collide(Particle* p1, Particle* p2) {
    // find the distance between particles
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    float dist = sqrtf(dx*dx + dy*dy);
    float minDist = p1->radius + p2->radius;

    // no collision
    if (dist == 0.0f || dist >= minDist) return;

    // normalize normal vector
    float nx = dx / dist;
    float ny = dy / dist;

    // push them apart slightly so they don't overlap
    float overlap = 0.5f * (minDist - dist);
    p1->x -= overlap * nx;
    p1->y -= overlap * ny;
    p2->x += overlap * nx;
    p2->y += overlap * ny;

    // --- compute relative velocity ---
    float tx = -ny; // tangent vector
    float ty = nx;

    // project velocities onto the normal and tangent
    float v1n = p1->vx * nx + p1->vy * ny;
    float v1t = p1->vx * tx + p1->vy * ty;
    float v2n = p2->vx * nx + p2->vy * ny;
    float v2t = p2->vx * tx + p2->vy * ty;

    // --- 1D elastic collision along the normal ---
    float m1 = p1->mass;
    float m2 = p2->mass;

    float v1n_after = (v1n * (m1 - m2) + 2.0f * m2 * v2n) / (m1 + m2);
    float v2n_after = (v2n * (m2 - m1) + 2.0f * m1 * v1n) / (m1 + m2);

    // --- convert scalar normal/tangent back to 2D velocity ---
    p1->vx = v1n_after * nx + v1t * tx;
    p1->vy = v1n_after * ny + v1t * ty;
    p2->vx = v2n_after * nx + v2t * tx;
    p2->vy = v2n_after * ny + v2t * ty;
}