#include "gracz.h"
#include <iostream>
#include <SFML/Graphics.hpp>
gracz::gracz(std::string name, int hp, int lifes, std::string fpath) :
	name(name), maxHp(hp), lifes(lifes), Hp(hp), currentFrame(0) {
	if (texture.loadFromFile(fpath)) {
		texture.setSmooth(false);
		sprite.setTexture(texture);
		sprite.setScale(2.f, 2.f);
		ramka = sf::IntRect(0, 0, 126, 126);
		sprite.setTextureRect(ramka);
		sprite.setOrigin(50.f, 100.f);
		sprite.setPosition(200.f, 500.f);
	}
}
void gracz::takeDmg(int dmg) {
	if (Hp > dmg)
		Hp -= dmg;
	else
	{
		Hp = maxHp;
		lifes--;
	}	}
void gracz::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
void gracz::printStatus() const {
	cout << name << Hp << lifes;
}
sf::Vector2f gracz::getPosition() { 
	return sprite.getPosition();
}
void gracz::update() {
	if (!czygleba) {
		velocity += gravity;
	}
	else {
		velocity = 0.f;
	}

	sprite.move(0, velocity);

	if (sprite.getPosition().y > 950.f) {
		sprite.setPosition(sprite.getPosition().x, 950.f);
		czygleba = true;
		velocity = 0.f;
	}
	else {
		czygleba = false;
	}

	if (ruch) {
		ramka.top = 128;
		ramka.height = 128;
		ramka.width = 128;
		if (animationClock.getElapsedTime().asSeconds() > 0.2f) {
			currentFrame++;
			if (currentFrame > 3) 
				currentFrame = 0;
			ramka.left = currentFrame * 126;
			sprite.setTextureRect(ramka);
			animationClock.restart();
		}
	}
	else {
		currentFrame = 0;
		ramka.top = 0;
		ramka.left = 0;
		sprite.setTextureRect(ramka);
	}
}
void gracz::handleInput() {
	ruch = false;
	sf::Vector2f movement(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= speed;
		sprite.setScale(-2.f, 2.f);
		ruch = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += speed;
		sprite.setScale(2.f, 2.f);
		ruch = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && czygleba) {
		velocity = jumpSpeed;
		czygleba = false;
	}
	sprite.move(movement);
}