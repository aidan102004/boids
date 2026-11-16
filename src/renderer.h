#pragma once
#include <SDL.h>


class Renderer {
private:
    static constexpr int width = 1400;
    static constexpr int height = 800;
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    void create_window() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("boids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
    }

    void present() {
        SDL_RenderPresent(renderer);
    }

    ~Renderer() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw_point(int x, int y, int size) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = { x - size / 2, y - size / 2, size, size };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_Point to_screen(float x, float y, float scale = 70.0f) {
        return { (int)(x * scale) + width / 2, (int)(-y * scale) + height / 2 };
    }

    int get_width() const {
        return width;
    }
    int get_height() const {
        return height;
    }
};