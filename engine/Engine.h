#pragma once

#include <SDL3/SDL.h>

class Engine {
public:
    bool init(const char *title, int width, int height);
    void run();
    void shutdown();

private:
    SDL_Window *window = nullptr;
    SDL_GLContext gl_context = nullptr;
    bool running = false;
};
