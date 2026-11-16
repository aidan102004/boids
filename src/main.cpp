#include <SDL.h>
#include "renderer.h"
#include "boid.h"
#include <random>

float random_float(float lo, float hi);
std::vector<boid> boids;

Renderer r;
int main() {
    r.create_window();
    
    boids.reserve(10);
    const float scale = 70.f;
    float half_w = (r.get_width()  / 2.f) / scale;   // 10.0
    float half_h = (r.get_height() / 2.f) / scale;   // ~5.71
    for (int i = 0; i < 10; i++) {
        float x = random_float(-half_w, half_w);
        float y = random_float(-half_h, half_h);
        float s = 0.1f;
        SDL_Point p0 = r.to_screen(x, y+(2*s));
        SDL_Point p1 = r.to_screen(x-s, y-s);
        SDL_Point p2 = r.to_screen(x+s, y-s);
        boids.emplace_back(p0, p1, p2);
    }
    bool running = true;
    while (running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) 
                running = false;
        }
            //update boids

            r.clear();
            for (const auto& boid : boids) {
                boid.draw(r.renderer);
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