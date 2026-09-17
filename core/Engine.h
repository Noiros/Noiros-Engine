#pragma once
#include <memory>

#include "Window.h"

class Engine {
public:
    Engine() = default;
    ~Engine() = default;

    void Initialize();
    void Run();
    void MainLoop();

    Window* GetMainWindow() { return mainWindow.get(); }

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

private:
    std::unique_ptr<Window> mainWindow;
    bool running = false;
};
