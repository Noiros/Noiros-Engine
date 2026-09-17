//
// Created by noiro on 16-01-26.
//

#ifndef CUSTOM_GAME_ENGINE_INTERFACEBASE_H
#define CUSTOM_GAME_ENGINE_INTERFACEBASE_H


class InterfaceBase {
    public:
    virtual ~InterfaceBase() = default;
    virtual void Update() {}
    virtual void Render() {}
};


#endif //CUSTOM_GAME_ENGINE_INTERFACEBASE_H