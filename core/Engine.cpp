#include "Engine.h"

#include <glad/gl.h>

void Engine::Initialize() {
    SDL_Log("Initializing Engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return;
    }

    SDL_Log("Creating Window");
    mainWindow = std::make_unique<Window>("Noiros Engine", 1280, 720);
    if (!mainWindow->IsValid()) {
        SDL_Quit();
        return;
    }

    Run();
}

void Engine::Run() {
    SDL_Log("Running Engine");

    running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT ||
                (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && mainWindow->IsEventTarget(e))) {
                running = false;
            }
        }

        MainLoop();
    }

    mainWindow.reset();
    SDL_Quit();
}

void Engine::MainLoop() {
    int width, height;
    mainWindow->GetPixelSize(width, height);
    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainWindow->Swap();
}
