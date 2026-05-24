#include "gracz.h"
#include "tlo.h"
#include <iostream>
#include <SFML/Graphics.hpp>
gracz::gracz(std::string name, int hp, int lifes, std::string fpath) :
	name(name), maxHp(hp), lifes(lifes), Hp(hp), currentFrame(0), AttackFrame(0) {
	if (img.loadFromFile(fpath)) {
		img.createMaskFromColor(sf::Color(255, 0, 255));
		texture.loadFromImage(img);
		texture.setSmooth(false);
		sprite.setTexture(texture);
		sprite.setScale(2.5f, 2.5f);
		ramka = sf::IntRect(10, 10, 64, 64);
		sprite.setTextureRect(ramka);
		sprite.setOrigin(32.f, 64.f);
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
	std::cout << name << Hp << lifes;
}
sf::Vector2f gracz::getPosition() { 
	return sprite.getPosition();
}
void gracz::update() {
	if (!czygleba) velocity += gravity;
	else velocity = 0.f;

	sprite.move(0, velocity);

	if (sprite.getPosition().y > 950.f) {
		sprite.setPosition(sprite.getPosition().x, 950.f);
		czygleba = true;
		velocity = 0.f;
	}

	if (obecnyStan == Stan::ATAK_1) {
		if (attackClock.getElapsedTime().asSeconds() > attackDuration) {
			AttackFrame++;
			if (AttackFrame >= 4) {
				obecnyStan = Stan::IDLE;
				AttackFrame = 0;
			}
			attackClock.restart();
		}
		ramka.top = 2715;
		ramka.width = 110;
		ramka.height = 120;
		ramka.left = AttackFrame * 110;
		sprite.setTextureRect(ramka);
	}
	else if (!czygleba) {
		obecnyStan = Stan::SKOK;
		ramka.top = 0;
		ramka.left = 256;
		ramka.width = 128;
		ramka.height = 128;
		sprite.setTextureRect(ramka);
	}
	else if (ruch) {
		obecnyStan = Stan::BIEG;
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
	else if (!ruch && czygleba) { 
		ramka.top = 110;
		ramka.left = 2480;
		ramka.width = 64;
		ramka.height = 64;
		if (animationClock.getElapsedTime().asSeconds() > 0.2f) {
			currentFrame++;
			if (currentFrame > 3)
				currentFrame = 0;
			ramka.left = currentFrame * 126;
			sprite.setTextureRect(ramka);
			animationClock.restart();
	}
	
	sprite.setTextureRect(ramka);

	currentFrame = 0;
	ramka.top = 0;
	ramka.left = 0;
	sprite.setTextureRect(ramka);

	if (sprite.getPosition().x < 100.f) {
		sprite.setPosition(100.f, sprite.getPosition().y);
	}
	if (mapaLimit > 0 && sprite.getPosition().x > mapaLimit - 100.f) {
		sprite.setPosition(mapaLimit - 100.f, sprite.getPosition().y);
	}
}
void gracz::handleInput() {
	if (obecnyStan == Stan::ATAK_1) 
		return;
	ruch = false;
	sf::Vector2f movement(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && obecnyStan != Stan::ATAK_1) {
		obecnyStan = Stan::ATAK_1;
		attackClock.restart();
		currentFrame = 0; 
	}
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
void gracz::ustawBariere(const tlo& mapa) {
	this->mapaLimit = mapa.dlugosc;
}