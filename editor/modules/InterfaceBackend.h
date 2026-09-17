#pragma once
#include <algorithm>
#include <vector>
#include "Engine.h"
#include "EventType.h"
#include "interfaces/InterfaceBase.h"
#include "modules/Event.h"
#include "SDL3/SDL_events.h"

class InterfaceBackend {
public:
    void InitializeInterface();
    void Update();

    void ProcessInput(const InputEvent &e);

    void AddInterface(InterfaceBase* interface) { interfaces.push_back(interface); }
    void RemoveInterface(InterfaceBase* interface) {interfaces.erase(std::remove(interfaces.begin(), interfaces.end(), interface), interfaces.end());}


private:
    std::vector<InterfaceBase*> interfaces;
    Event::Connection inputEvent;
};
