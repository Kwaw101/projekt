#include "bezdomny.h"
#include <iostream>
#include <SFML/Graphics.hpp>
bezdomny::bezdomny(std::string fpath, sf::Vector2f pos) {

    if (texture.loadFromFile(fpath)) {
        sprite.setTexture(texture);
        ramka = sf::IntRect(0, 0, 128, 128);
        sprite.setTextureRect(ramka);
        sprite.setOrigin(64.f, 120.f);
        sprite.setPosition(pos);
        sprite.setScale(-3.5f, 3.5f);
    }
}
void bezdomny::update() {
    if (animClock.getElapsedTime().asSeconds() > 0.25f) {
        currentFrame++;
        if (currentFrame >= 10) currentFrame = 0;
        ramka.left = currentFrame * 128;
        sprite.setTextureRect(ramka);
        animClock.restart();
    }

    if (red && hurtClock.getElapsedTime().asSeconds() > 0.1f) {
        sprite.setColor(sf::Color::White);
        red = false;
    }
}

void bezdomny::takeDmg(float dmg) {
    hp -= dmg;
    sprite.setColor(sf::Color::Red);
    red = true;
    hurtClock.restart();
}

void bezdomny::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect bezdomny::getBounds() const {
    sf::FloatRect fullBounds = sprite.getGlobalBounds();

    float off_left = 180.f;
    float off_right = 135.f;

    return sf::FloatRect(fullBounds.left + off_left,
        fullBounds.top,
        fullBounds.width - (off_left + off_right),
        fullBounds.height);
}

