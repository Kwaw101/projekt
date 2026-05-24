#include "tlo.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
void tlo::seg(const std::string& file) {
	auto texture = std::make_unique<sf::Texture>();
	if (texture->loadFromFile(file)) {
		tekstury.push_back(std::move(texture));
		sf::Sprite sprite;
		sprite.setTexture(*tekstury.back());
		float skalaY = 1080.f / (float)sprite.getLocalBounds().height;
		sprite.setScale(skalaY, skalaY);
		sprite.setPosition(std::floor(dlugosc), 0.f);

		float scaling = sprite.getLocalBounds().width * skalaY;
		dlugosc += scaling;
		sprity.push_back(sprite);
	}
}
void tlo::draw(sf::RenderWindow& window) {
	for (auto& s : sprity) {
		window.draw(s);
	}
}
float tlo::getDlugosc() const {
	return dlugosc;
}