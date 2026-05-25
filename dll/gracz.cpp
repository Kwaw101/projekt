#include "gracz.h"
#include "tlo.h"
#include <iostream>
#include <SFML/Graphics.hpp>

gracz::gracz(std::string name, int hp, int lifes, std::string fpath, std::string fpathAtak) :
	name(name), maxHp(hp), lifes(lifes), Hp(hp), currentFrame(0), AttackFrame(0) {
	if (texture.loadFromFile(fpath)) {
		texture.setSmooth(false);
		sprite.setTexture(texture);
		sprite.setScale(2.f, 2.f);
		ramka = sf::IntRect(0, 0, 126, 126);
		sprite.setTextureRect(ramka);
		sprite.setOrigin(50.f, 100.f);
		sprite.setPosition(200.f, 900.f);
	}
	sf::Image img;
	if (img.loadFromFile(fpathAtak)) {
		img.createMaskFromColor(sf::Color::White);
		textureAtak.loadFromImage(img);
		textureAtak.setSmooth(false);
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
		sprite.setTexture(textureAtak);
		float skalaAtaku = 1.25f;
		if (sprite.getScale().x < 0) sprite.setScale(-skalaAtaku, skalaAtaku);
		else sprite.setScale(skalaAtaku, skalaAtaku);
		if (attackClock.getElapsedTime().asSeconds() > 0.2f) {
			AttackFrame++;
			if (AttackFrame >= 2) {
				if (combo) {
					obecnyStan = Stan::ATAK_2; 
					AttackFrame = 0;
					combo = false;
				}
				else {
					obecnyStan = Stan::IDLE;
					AttackFrame = 0;
				}
			}
			attackClock.restart();
		}
		ramka.top = 295;
		ramka.left = 60;
		ramka.width = 200;
		ramka.height = 225;
		ramka.left = AttackFrame * 250;
		sprite.setTextureRect(ramka);
		sprite.setOrigin(100.f, 170.f);
	}
	else if (obecnyStan == Stan::ATAK_2) {
		sprite.setTexture(textureAtak);
		float skalaAtaku = 1.25f;
		sprite.setScale(sprite.getScale().x < 0 ? -skalaAtaku : skalaAtaku, skalaAtaku);

		if (attackClock.getElapsedTime().asSeconds() > 0.2f) {
			AttackFrame++;
			if (AttackFrame >= 2) {
				if (combo) {
					obecnyStan = Stan::ATAK_3;
					AttackFrame = 0;
					combo = false;
				}
				else {
					obecnyStan = Stan::IDLE;
					AttackFrame = 0;
				}
			}
				attackClock.restart();
		}
		ramka.top = 555;
		ramka.left = 70;
		ramka.width = 200;
		ramka.height = 225;
		ramka.left = AttackFrame * 250;
		sprite.setTextureRect(ramka);
		sprite.setOrigin(100.f, 170.f);
	}
	else if (obecnyStan == Stan::ATAK_3) {
		sprite.setTexture(textureAtak);
		float skalaAtaku = 1.25f;
		sprite.setScale(sprite.getScale().x < 0 ? -skalaAtaku : skalaAtaku, skalaAtaku);

		if (attackClock.getElapsedTime().asSeconds() > 0.2f) {
			AttackFrame++;
			if (AttackFrame >= 2) { 
				obecnyStan = Stan::IDLE; 
				AttackFrame = 0; 
			}
			attackClock.restart();
		}
		ramka.top = 810;
		ramka.left = 20;
		ramka.width = 210;
		ramka.height = 220;
		ramka.left = AttackFrame * 210;
		sprite.setTextureRect(ramka);
		sprite.setOrigin(70.f, 170.f); 
	}
	else {
		sprite.setTexture(texture);
		sprite.setOrigin(64.f, 100.f);
		if (sprite.getScale().x < 0) sprite.setScale(-2.0f, 2.0f);
		else sprite.setScale(2.0f, 2.0f);

		if (!czygleba) {
			obecnyStan = Stan::SKOK;
			ramka.top = 0;
			ramka.left = 256;
			ramka.width = 128;
			ramka.height = 128;
		}
		else if (ruch) {
			obecnyStan = Stan::BIEG;
			ramka.top = 128;
			ramka.width = 128;
			ramka.height = 128;
			if (animationClock.getElapsedTime().asSeconds() > 0.2f) {
				currentFrame++;
				if (currentFrame > 3) currentFrame = 0;
				ramka.left = currentFrame * 128;
				animationClock.restart();
			}
		}
		else {
			obecnyStan = Stan::IDLE;
			currentFrame = 0;
			ramka.top = 0;
			ramka.left = 0;
			ramka.width = 128;
			ramka.height = 128;
		}
		sprite.setTextureRect(ramka);

		if (sprite.getPosition().x < 100.f) {
			sprite.setPosition(100.f, sprite.getPosition().y);
		}
		if (mapaLimit > 0 && sprite.getPosition().x > mapaLimit - 100.f) {
			sprite.setPosition(mapaLimit - 100.f, sprite.getPosition().y);
		}
	}
}
void gracz::handleInput() {
	lastMovement = sf::Vector2f(0.f, 0.f);
	if (isAttacking()) return;
	ruch = false;
	sf::Vector2f movement(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && obecnyStan == Stan::IDLE) {
		obecnyStan = Stan::ATAK_2;
		attackClock.restart();
		AttackFrame = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && obecnyStan == Stan::IDLE) {
		obecnyStan = Stan::ATAK_3;
		attackClock.restart();
		AttackFrame = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && obecnyStan != Stan::ATAK_1) {
		if (obecnyStan == Stan::IDLE || obecnyStan == Stan::BIEG) {
			obecnyStan = Stan::ATAK_1;
			attackClock.restart();
			AttackFrame = 0;
		}
		else if (obecnyStan == Stan::ATAK_1 || obecnyStan == Stan::ATAK_2) {
			combo = true;
		}
	}

	if (obecnyStan == Stan::ATAK_1 || obecnyStan == Stan::ATAK_2 || obecnyStan == Stan::ATAK_3)
		return;

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

	lastMovement = movement;
}
void gracz::ustawBariere(const tlo& mapa) {
	this->mapaLimit = mapa.dlugosc;
}
sf::FloatRect gracz::getHitbox() const {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	float width = 60.f;
	float height = 40.f;
	float top = bounds.top + 30.f;
	float left;

	if (sprite.getScale().x > 0)
		left = bounds.left + bounds.width - 10.f;
	else
		left = bounds.left - width + 10.f;

	if (obecnyStan == Stan::ATAK_1 || obecnyStan == Stan::ATAK_2 || obecnyStan == Stan::ATAK_3)
		return sf::FloatRect(left, top, width, height);

	return sf::FloatRect(0, 0, 0, 0);
}
sf::FloatRect gracz::getBodyBounds() const {
	sf::FloatRect fullBounds = sprite.getGlobalBounds();

	float trim_back = 50.f;
	float trim_front = 40.f;

	float new_left;
	float new_width = fullBounds.width - (trim_back + trim_front);

	if (sprite.getScale().x > 0) {
		new_left = fullBounds.left + trim_back;
	}
	else {
		new_left = fullBounds.left + trim_front;
	}

	return sf::FloatRect(new_left, fullBounds.top, new_width, fullBounds.height);
}
bool gracz::isAttacking() const {
	return (obecnyStan == Stan::ATAK_1 || obecnyStan == Stan::ATAK_2 || obecnyStan == Stan::ATAK_3);
}
void gracz::moveIfPossible(sf::Vector2f mov, const sf::FloatRect& obstacle) {
	sf::FloatRect futureBounds = getBodyBounds();
	futureBounds.left += mov.x;

	if (!futureBounds.intersects(obstacle) || obecnyStan == Stan::SKOK) {
		sprite.move(mov.x, 0);
	}
}
sf::Vector2f gracz::getMovement() const {
	return lastMovement; }