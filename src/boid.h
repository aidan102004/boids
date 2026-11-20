#pragma once

#include <SDL.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "vector.h"

const float speed = 1.0f;

class boid {
public:
    vec2 pos;
    vec2 dir;   //unit vector the way the triangle points
    float max_speed = 1.0f;

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

        //edge wrapping
        if (pos.x() > half_w) pos = vec2({-half_w, pos.y()});
        if (pos.x() < -half_w) pos = vec2({half_w, pos.y()});
        if (pos.y() > half_h) pos = vec2({pos.x(), -half_h});
        if (pos.y() < -half_h) pos = vec2({pos.x(), half_h});

    }

    void seperation() {

    }

    vec2 alignment(const std::vector<boid>& boids) const {
        float perception = 1; //radius of perception
        int total = 0; //count for how many times we increment average
        auto avg = vec2(); //empty avg vector
        for (const auto& other : boids) {
            float d = distance(this->pos, other.pos);
            if (&other != this && d < perception) {
                avg += other.dir;
                total++;
            }
        }
        if (total == 0) return vec2();
        avg /= total;
        return avg - dir;
    }

    void steer(vec2 s, float dt) {
        vec2 nd = dir + s * (5.f * dt);
        if (nd.len() > 1e-6f) {
            nd.normalise();
            dir = nd;
        }
    }

    void cohesion() {

    }

};