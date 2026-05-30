
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MaszynaStanow.h"
#include "state.h"
#include "gracz.h"
#include "tlo.h"
#include "bezdomny.h"
#include "enemy.h"
#include "menu.h"
#include <iostream>
#include <vector>

int main()
{
    // 1. Inicjalizacja okna
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Moja gierka");
    window.setFramerateLimit(60);

    // 2. Inicjalizacja Maszyny Stanów
    MaszynaStanow machine;
    sf::Clock clock;

    // 3. Dodanie stanu pocz¹tkowego - MENU
    machine.addState(std::make_unique<menu>(window, machine));

    // 4. G£ÓWNA PÊTLA - teraz jest bardzo krótka
    while (window.isOpen()) {
        machine.processStateChanges();

        float dt = clock.restart().asSeconds();

        auto& activeState = machine.getActiveState();

        activeState->handleInput();
        activeState->update(dt);

        window.clear();
        activeState->draw();
        window.display();
    }

    return 0;
}