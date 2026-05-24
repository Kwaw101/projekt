#pragma once
#include <SFML/Graphics.hpp>
#include "tlo.h"
enum class Stan { IDLE, BIEG, SKOK, ATAK_1 };
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
	sf::Image img;
public:
	gracz(std:: string name, int maxHp, int lifes, std::string fpath);
	void takeDmg(int x);
	void printStatus() const;
	void update();
	void handleInput();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void ustawBariere(const tlo& mapa);
};

