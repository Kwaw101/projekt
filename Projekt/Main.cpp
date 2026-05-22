
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MaszynaStanow.h"
#include "state.h"

int main()
{
	// ustawienie okna
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Moja gierka");
	sf::RectangleShape ground(sf::Vector2f(1920.f, 500.f));
	window.setFramerateLimit(60);
	ground.setFillColor(sf::Color::Black);
	ground.setPosition(0.f, 1000.f);
	//inicjalizacja gracza
	sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
	player.setFillColor(sf::Color::Red);
	player.setPosition(375.f, 100.f);
	float velocity = 5.f;
	float gravity = 0.5f;
	float speed = 5.f;
	MaszynaStanow machine;
	sf::Clock clock;

    // Odpalamy pierwszy stan (np. Menu)
    //machine.addState(std::make_unique<MenuState>());

    while (window.isOpen()) {

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			velocity += gravity;
			player.move(0.f, velocity);
			sf::Vector2f movement(0.f, 0.f);
			if (player.getGlobalBounds().intersects(ground.getGlobalBounds())) {
				velocity = 0.f;
				player.setPosition(player.getPosition().x, ground.getPosition().y - player.getSize().y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;
			player.move(movement);

			window.clear(sf::Color::Magenta);
			window.draw(ground);
			window.draw(player);
			window.display();
		}
    }
    return 0;
}