#pragma once
#include "state.h"
#include "gracz.h"
#include "tlo.h"
#include "enemy.h"
#include "MaszynaStanow.h"
#include <vector>
#include <memory>

class __declspec(dllexport) gra : public state {
private:
    sf::RenderWindow& _window;
    MaszynaStanow& _machine;

    gracz player;
    tlo mapa1, mapa2;
    sf::RectangleShape ground;
    sf::View camera;
    std::vector<std::unique_ptr<bezdomny>> enemi;

    sf::Font _font;
    int _etap = 1;
    sf::Text _komunikat;
    sf::Clock _komunikatTimer;
    bool _wyswietlajKomunikat = false;

public:
    gra(sf::RenderWindow& window, MaszynaStanow& machine);

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw() override;
};