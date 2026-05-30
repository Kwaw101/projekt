#pragma once
#include <SFML/Graphics.hpp>

class __declspec(dllexport) state {
public:
    virtual ~state() = default;

    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    virtual void pause() {}
    virtual void resume() {}
};