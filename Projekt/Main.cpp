
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MaszynaStanow.h"
#include "state.h"
#include "gracz.h"
#include "tlo.h"
#include "bezdomny.h"
#include <enemy.h>
#include <iostream>
#include <vector>

int main()
{
    // 1. Ustawienie okna
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Moja gierka");
    window.setFramerateLimit(60);

    // 2. T³o i pod³o¿e
    tlo mapa1;
    mapa1.seg("P:\\projekt\\Projekt\\Projekt\\begin.jpg");
    tlo mapa2;
    mapa2.seg("P:\\projekt\\Projekt\\Projekt\\background2.jpg");
    mapa2.seg("P:\\projekt\\Projekt\\Projekt\\background.jpg");

    sf::RectangleShape ground(sf::Vector2f(mapa2.getDlugosc(), 500.f));
    ground.setFillColor(sf::Color::Black);
    ground.setPosition(0.f, 1000.f);

    // 3. Inicjalizacja gracza
    gracz player("Kiryu", 100, 3, "P:\\projekt\\Projekt\\Projekt\\kiryu.png", "P:\\projekt\\Projekt\\Projekt\\kiryuatak.png");
    player.ustawBariere(mapa2);

    sf::View camera(sf::FloatRect(0, 0, 1920, 1080));

    // 4. Inicjalizacja wektora przeciwników
    std::vector<std::unique_ptr<bezdomny>> enemi;
    enemi.push_back(std::make_unique<bezdomny>("P:\\projekt\\Projekt\\Projekt\\homeless_1\\Idle_2.png", sf::Vector2f(1100.f, 975.f)));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.handleInput();

        sf::FloatRect aktualnaPrzeszkoda(0, 0, 0, 0);

        for (int i = 0; i < enemi.size(); i++) {
            enemy* ptrEnemy = dynamic_cast<enemy*>(enemi[i].get());

            if (ptrEnemy) {
                ptrEnemy->update(player.getPosition());

                if (ptrEnemy->getIsAttacking() && !ptrEnemy->getHasDealtDamage()) {
                    if (ptrEnemy->getCurrentFrame() == 3) {
                        if (ptrEnemy->getBounds().intersects(player.getBodyBounds())) {
                            player.takeDmg(ptrEnemy->getDamage());
                            ptrEnemy->setHasDealtDamage(true);
                        }
                    }
                }
            }
            else {
                enemi[i]->update();
            }

            if (player.isAttacking() && !player.hasDealtDamage()) {
                if (player.getHitbox().intersects(enemi[i]->getBounds())) {
                    float dmg = player.AD();
                    enemi[i]->takeDmg(dmg);
                    player.setDamageDealt(true);
                }
            }

            if (!enemi[i]->isDeadStatus()) {
                if (player.getBodyBounds().intersects(enemi[i]->getBounds())) {
                    aktualnaPrzeszkoda = enemi[i]->getBounds();
                }
            }

            if (enemi[i]->getRemoveStatus()) {
                enemi.erase(enemi.begin() + i);
                i--;
                continue;
            }
        }

        player.moveIfPossible(player.getMovement(), aktualnaPrzeszkoda);
        player.update();

        float cameraX = player.getPosition().x;
        if (cameraX < 960.f) cameraX = 960.f;
        if (cameraX > mapa1.getDlugosc() - 960.f) cameraX = mapa1.getDlugosc() - 960.f;

        camera.setCenter(cameraX, 540);
        ground.setPosition(cameraX - 960.f, 1000.f);

        window.clear();
        window.setView(camera);

        mapa1.draw(window);
        window.draw(ground);

        for (auto& wrog : enemi) {
            wrog->draw(window);
        }

        player.draw(window);
        window.display();
    }
    return 0;
}