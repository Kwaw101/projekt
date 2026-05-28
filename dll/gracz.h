#pragma once
#include <SFML/Graphics.hpp>
#include "tlo.h"
enum class Stan { IDLE, BIEG, SKOK, ATAK_1, ATAK_2, ATAK_3, KUCANIE };
class __declspec(dllexport) gracz
{
private:
	float speed = 5.f;
	int maxHp;
	int Hp;
	int lifes;
	std::string name;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture textureAtak;
	sf::Clock animationClock;
	int currentFrame;
	sf::IntRect ramka;
	float velocity = 0.f;
	float gravity = 0.5f;
	float jumpSpeed = -15.f;
	bool czygleba = false;
	float groundLevel = 900.f;
	bool ruch = false;
	float mapaLimit = 0.f;
	Stan obecnyStan = Stan::IDLE;
	sf::Clock attackClock;
	float attackDuration = 0.4f;
	int AttackFrame;
	bool combo = false;
	sf::Vector2f lastMovement;
	bool attackDamageDealt = false;
public:
	gracz(std::string name, int maxHp, int lifes, std::string fpath, std::string fpathAtak);
	void takeDmg(int x);
	void printStatus() const;
	void update();
	void handleInput();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void ustawBariere(const tlo& mapa);
	sf::FloatRect getHitbox() const;
	sf::FloatRect getBodyBounds() const;
	void moveIfPossible(sf::Vector2f velocity, const sf::FloatRect& obstacle);
	bool isAttacking() const;
	sf::Vector2f getMovement() const;
	bool hasDealtDamage() const { return attackDamageDealt; }
	void setDamageDealt(bool status) { attackDamageDealt = status; }
};