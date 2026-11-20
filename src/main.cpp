#include <SDL.h>
#include "renderer.h"
#include "boid.h"
#include "vector.h"
#include <random>

float random_float(float lo, float hi);
std::vector<boid> boids;

Renderer r;
int main() {
    r.create_window();
    
    boids.reserve(100);
    const float scale = 70.f;
    float half_w = (r.get_width()  / 2.f) / scale;   // 10.0
    float half_h = (r.get_height() / 2.f) / scale;   // ~5.71
    const float two_pi = 6.2831853f;
    for (int i = 0; i < 100; i++) {
        float x     = random_float(-half_w, half_w);
        float y     = random_float(-half_h, half_h);
        float angle = random_float(0.f, two_pi);
        boids.emplace_back(vec2{x, y}, angle);
    }
    bool running = true;
    Uint32 last = SDL_GetTicks();
    while (running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) 
                running = false;
            }
            Uint32 now = SDL_GetTicks();
            float dt = (now-last) / 1000.0f;
            last = now;
            //update boids
            r.clear();
            std::vector<vec2> steers(boids.size());
            for (size_t i = 0; i < boids.size(); i++) {
                steers[i] = boids[i].alignment(boids);
            }
            for (size_t i = 0; i < boids.size(); i++)  {
                boids[i].steer(steers[i], dt);
                boids[i].update(dt, half_w, half_h);
                boids[i].draw(r);
            }
            r.present();
            SDL_Delay(16); 
    }
    return 0;
}

float random_float(float lo, float hi) {
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> dist(lo, hi);
    return dist(rng);
}