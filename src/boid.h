#pragma once

#include <SDL.h>
#include <cmath>
#include "vector.h"

const float speed = 1.0f;

class boid {
public:
    vec2 pos;
    vec2 dir;   //unit vector the way the triangle points

    boid(vec2 pos, float angle) : pos(pos), dir{std::cos(angle), std::sin(angle)} {}

    void draw(Renderer& r) const {
        const float s = 0.05f;

        //perpendicular to dir
        vec2 side{ -dir.y(), dir.x() };

        auto to_world = [&](float fwd, float lat) {
            return vec2{ pos.x() + dir.x() * fwd + side.x() * lat,
                         pos.y() + dir.y() * fwd + side.y() * lat };
        };

        vec2 a = to_world( 2 * s,  0);
        vec2 b = to_world(-s,      s);
        vec2 c = to_world(-s,     -s);

        SDL_Point pa = r.to_screen(a.x(), a.y());
        SDL_Point pb = r.to_screen(b.x(), b.y());
        SDL_Point pc = r.to_screen(c.x(), c.y());

        SDL_SetRenderDrawColor(r.renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(r.renderer, pa.x, pa.y, pb.x, pb.y);
        SDL_RenderDrawLine(r.renderer, pb.x, pb.y, pc.x, pc.y);
        SDL_RenderDrawLine(r.renderer, pc.x, pc.y, pa.x, pa.y);
    }

    void update(float dt, float half_w, float half_h) {
        float step = dt * speed;
        pos = vec2({pos.x() + dir.x() * step, pos.y() + dir.y() * step});
    }

};