#include "gra.h"
#include "menu.h"

gra::gra(sf::RenderWindow& window, MaszynaStanow& machine)
    : _window(window), _machine(machine),
    player("Kiryu", 100, "P:\\projekt\\Projekt\\Projekt\\kiryu.png", "P:\\projekt\\Projekt\\Projekt\\kiryuatak.png") {
}

void gra::init() {
    mapa1.seg("P:\\projekt\\Projekt\\Projekt\\begin.jpg");
    mapa2.seg("P:\\projekt\\Projekt\\Projekt\\background2.jpg");
    mapa2.seg("P:\\projekt\\Projekt\\Projekt\\background.jpg");

    ground.setSize(sf::Vector2f(mapa2.getDlugosc(), 500.f));
    ground.setFillColor(sf::Color::Black);
    ground.setPosition(0.f, 1000.f);

    _komunikat.setFont(_font);
    _komunikat.setCharacterSize(60);
    _komunikat.setFillColor(sf::Color::Yellow);
    _komunikat.setOutlineColor(sf::Color::Black);
    _komunikat.setOutlineThickness(3.f);

    _etap = 1;
    player.ustawBariere(mapa1);
    camera.setSize(1920, 1080);

    enemi.push_back(std::make_unique<bezdomny>(
        "P:\\projekt\\Projekt\\Projekt\\homeless_1\\Idle_2.png", sf::Vector2f(1100.f, 975.f) ));
}

void gra::handleInput() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) _window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _machine.removeState();
        }
    }
    player.handleInput();
}

void gra::update(float dt) {

    sf::FloatRect przeszkodaDlaGracza(0, 0, 0, 0);

    for (int i = 0; i < enemi.size(); i++) {
        enemy* ptrEnemy = dynamic_cast<enemy*>(enemi[i].get());
        if (ptrEnemy) ptrEnemy->update(player.getPosition());
        else enemi[i]->update();

        if (!enemi[i]->isDeadStatus()) {
            if (player.getBodyBounds().intersects(enemi[i]->getBounds())) {
                przeszkodaDlaGracza = enemi[i]->getBounds();
            }
        }

        if (player.isAttacking() && !player.hasDealtDamage()) {
            if (player.getHitbox().intersects(enemi[i]->getBounds())) {
                enemi[i]->takeDmg(player.AD());
                player.setDamageDealt(true);
            }
        }

        if (enemi[i]->getRemoveStatus()) {
            enemi.erase(enemi.begin() + i);
            i--;
            continue;
        }
    }

    player.moveIfPossible(player.getMovement(), przeszkodaDlaGracza);
    player.update();

    float cameraX = player.getPosition().x;
    if (cameraX < 960.f) cameraX = 960.f;

    float maxDlugosc = (_etap == 1) ? mapa1.getDlugosc() : mapa2.getDlugosc();
    if (cameraX > maxDlugosc - 960.f) cameraX = maxDlugosc - 960.f;

    camera.setCenter(cameraX, 540);

    if (enemi.empty() && !_wyswietlajKomunikat) {
        if (_etap == 1) {
            _wyswietlajKomunikat = true;
            _komunikat.setString("Well done, now go get'em tiger");
            _komunikat.setPosition(player.getPosition().x - 300.f, 400.f);
            _komunikatTimer.restart();
        }
    }

    if (_wyswietlajKomunikat && _komunikatTimer.getElapsedTime().asSeconds() > 3.0f) {
        if (_etap == 1) {
            _etap = 2;
            _wyswietlajKomunikat = false;

            player.setPosition(100.f, 950.f);
            player.ustawBariere(mapa2);

            enemi.push_back(std::make_unique<enemy>(
                "homeless_1/Idle_2.png", "Walk.png", "Attack.png", "Dead.png",
                sf::Vector2f(1200.f, 975.f), 150.f, 2.5f, 15.f
            ));
        }
    }
}

void gra::draw() {
    _window.setView(camera);

    if (_etap == 1) mapa1.draw(_window);
    else mapa2.draw(_window);

    _window.draw(ground);

    for (auto& wrog : enemi) wrog->draw(_window);
    player.draw(_window);

    if (_wyswietlajKomunikat) {
        _window.draw(_komunikat);
    }
}