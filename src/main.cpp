#include <SDL.h>
#include "renderer.h"

Renderer r;
int main() {
    r.create_window();

    bool running = true;
    while (running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) 
                running = false;
            r.clear();
            SDL_Point p = r.to_screen(0.0f, 0.0f);
            r.draw_point(p.x, p.y, 20);
            r.present();
        }
    }
}