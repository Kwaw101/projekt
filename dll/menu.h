#pragma once
#include "state.h"
#include "MaszynaStanow.h"
#include <vector>

class __declspec(dllexport) menu : public state {
private:
    sf::RenderWindow& _window;
    MaszynaStanow& _machine;
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;

    sf::Font _font;
    std::vector<sf::Text> _menuOptions;
    int _selectedOption = 0;
    std::string wczytajZPliku(std::string sciezka);
    sf::Text _infoText;

    void wczytajNapisyZBin();

public:
    menu(sf::RenderWindow& window, MaszynaStanow& machine);

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw() override;
};