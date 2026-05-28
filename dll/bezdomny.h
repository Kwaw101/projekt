#pragma once
#include <SFML/Graphics.hpp>
class __declspec(dllexport) bezdomny
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect ramka;
    sf::Clock animClock;
    int currentFrame = 0;
    sf::Clock hurtClock;
    float hp = 100.f;
    bool red = false;
    sf::Texture textureDead;
    bool isDead = false;
    int deadFrame = 0;
    sf::Clock deathAnimClock;
    bool remove = false;
public:
    bezdomny(std::string fpath, sf::Vector2f pos);
    void update();
    void draw(sf::RenderWindow& window);
    void takeDmg(float dmg);
    sf::FloatRect getBounds() const;
    bool isDeadStatus() const { return isDead; }
    bool getRemoveStatus() const { return remove; }
};

