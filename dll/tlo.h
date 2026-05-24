#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
class gracz;
class __declspec(dllexport) tlo
{
private:
	std::vector <std::unique_ptr<sf::Texture>> tekstury;
	std::vector <sf::Sprite> sprity;
	float dlugosc = 0.f;
	friend class gracz;
public:
	tlo() = default;
	void seg(const std::string& file);
	void draw(sf::RenderWindow& window);
	float getDlugosc() const;
	tlo(const tlo&) = delete;
	tlo& operator=(const tlo&) = delete;
};

