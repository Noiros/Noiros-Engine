//
// Created by nicolas on 17-09-26.
//

#pragma once
#include <SDL3/SDL.h>

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool IsValid() const { return window != nullptr && gl_context != nullptr; }
    bool IsEventTarget(const SDL_Event& e) const { return e.window.windowID == SDL_GetWindowID(window); }
    void GetPixelSize(int& width, int& height) const { SDL_GetWindowSizeInPixels(window, &width, &height); }
    void Swap() const { SDL_GL_SwapWindow(window); }

    SDL_Window* window = nullptr;
    SDL_GLContext gl_context = nullptr;
};
