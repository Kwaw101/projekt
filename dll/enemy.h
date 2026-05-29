#pragma once
#include "bezdomny.h"
#include <string>
#include <SFML/Graphics.hpp>

class __declspec(dllexport) enemy : public bezdomny {
private:
    sf::Texture textureWalk;
    sf::Texture textureAttack;

    float moveSpeed;
    float attackRange;
    float detectionRange;
    float damage;

    bool isAttacking;
    sf::Clock attackCooldown;
    float cooldownTime;

    bool hasDealtDamage;

public:
    enemy(std::string pathIdle, std::string pathWalk, std::string pathAttack, std::string pathDead,
        sf::Vector2f pos, float hpIn, float speedIn, float dmgIn);

    void update(const sf::Vector2f& playerPos);
    bool getIsAttacking() const { return isAttacking; }
    int getCurrentFrame() const { return currentFrame; }
    float getDamage() const { return damage; }
    bool getHasDealtDamage() const { return hasDealtDamage; }
    void setHasDealtDamage(bool val) { hasDealtDamage = val; }

private:
    void animateWalk();
    void animateAttack();
    void animateIdle();
};
