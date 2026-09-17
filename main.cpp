#include "engine/Engine.h"

int main(int, char **) {
    Engine engine;
    if (!engine.init("Noiros Engine", 1280, 720)) {
        engine.shutdown();
        return 1;
    }
    engine.run();
    engine.shutdown();
    return 0;
}
