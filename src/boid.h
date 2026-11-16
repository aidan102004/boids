#pragma once

#include <SDL.h>

class boid {
private:
    SDL_Point a, b, c;
public:
    boid(SDL_Point a, SDL_Point b, SDL_Point c) : a(a), b(b), c(c) {}

    void draw(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
        SDL_RenderDrawLine(renderer, b.x, b.y, c.x, c.y);
        SDL_RenderDrawLine(renderer, c.x, c.y, a.x, a.y);
    }
};