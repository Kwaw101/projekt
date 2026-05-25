#pragma once
#include <SFML/Graphics.hpp>
class __declspec(dllexport) bezdomny
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect ramka;
    sf::Clock animClock;
    int currentFrame = 0;
    sf::Clock hurtClock;
    float hp = 100.f;
    bool red = false;
public:
    bezdomny(std::string fpath, sf::Vector2f pos);
    void update();
    void draw(sf::RenderWindow& window);
    void takeDmg(float dmg);
    sf::FloatRect getBounds() const;
};

