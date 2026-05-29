#include "enemy.h"
#include <cmath>

enemy::enemy(std::string pathIdle, std::string pathWalk, std::string pathAttack, std::string pathDead,
    sf::Vector2f pos, float hpIn, float speedIn, float dmgIn)
    : bezdomny(pathIdle, pos)
{
    textureWalk.loadFromFile(pathWalk);
    textureAttack.loadFromFile(pathAttack);
    textureDead.loadFromFile(pathDead);

    this->hp = hpIn;
    this->moveSpeed = speedIn;
    this->damage = dmgIn;

    this->attackRange = 90.f;
    this->detectionRange = 800.f;
    this->cooldownTime = 1.5f;

    this->isAttacking = false;
    this->hasDealtDamage = false;

    sprite.setScale(-3.0f, 3.0f);
}

void enemy::update(const sf::Vector2f& playerPos) {
    if (isDead) {
        if (deadFrame < 3) {
            if (deathAnimClock.getElapsedTime().asSeconds() > 0.15f) {
                deadFrame++;
                ramka.left = deadFrame * 128;
                sprite.setTextureRect(ramka);
                deathAnimClock.restart();
            }
        }
        else {
            if (deathAnimClock.getElapsedTime().asSeconds() > 3.0f) {
                remove = true;
            }
        }
        return;
    }

    float distance = playerPos.x - sprite.getPosition().x;
    float absDistance = std::abs(distance);

    if (isAttacking) {
        animateAttack();
    }
    else if (absDistance < attackRange) {
        if (attackCooldown.getElapsedTime().asSeconds() > cooldownTime) {
            isAttacking = true;
            currentFrame = 0;
            hasDealtDamage = false;
        }
    }
    else if (absDistance < detectionRange) {
        float direction = (distance > 0) ? 1.f : -1.f;
        sprite.move(direction * moveSpeed, 0.f);

        sprite.setScale(direction * 3.0f, 3.0f);

        animateWalk();
    }
    else {
        animateIdle();
    }

    if (red && hurtClock.getElapsedTime().asSeconds() > 0.1f) {
        sprite.setColor(sf::Color::White);
        red = false;
    }
}

void enemy::animateWalk() {
    if (animClock.getElapsedTime().asSeconds() > 0.1f) {
        currentFrame = (currentFrame + 1) % 10;
        ramka.left = currentFrame * 128;
        sprite.setTexture(textureWalk);
        sprite.setTextureRect(ramka);
        animClock.restart();
    }
}

void enemy::animateAttack() {
    if (animClock.getElapsedTime().asSeconds() > 0.12f) {
        currentFrame++;
        if (currentFrame >= 5) {
            isAttacking = false;
            currentFrame = 0;
            attackCooldown.restart();
        }
        ramka.left = currentFrame * 128;
        sprite.setTexture(textureAttack);
        sprite.setTextureRect(ramka);
        animClock.restart();
    }
}

void enemy::animateIdle() {
    if (animClock.getElapsedTime().asSeconds() > 0.2f) {
        currentFrame = (currentFrame + 1) % 10;
        ramka.left = currentFrame * 128;
        sprite.setTexture(texture);
        sprite.setTextureRect(ramka);
        animClock.restart();
    }
}
