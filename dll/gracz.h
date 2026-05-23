#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
class __declspec(dllexport) gracz
{
private:
	float speed = 5.f;
	int maxHp;
	int Hp;
	int lifes;
	string name;
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
public:
	gracz(string name, int maxHp, int lifes, string fpath);
	void takeDmg(int x);
	void printStatus() const;
	void update();
	void handleInput();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
};

