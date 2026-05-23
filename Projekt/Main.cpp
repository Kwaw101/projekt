
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MaszynaStanow.h"
#include "state.h"
#include "gracz.h"
#include <iostream>

int main()
{
	// ustawienie okna
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Moja gierka"); //sf::Style::Fullscreen
	sf::RectangleShape ground(sf::Vector2f(1920.f, 500.f));
	window.setFramerateLimit(60);
	ground.setFillColor(sf::Color::Black);
	ground.setPosition(0.f, 1000.f);
	sf::View camera(sf::FloatRect(0, 0, 1920, 1080));
	//background
	sf::Texture teksturabackground;
	if (!teksturabackground.loadFromFile("P:\\projekt\\Projekt\\Projekt\\background.jpg")) {
		cout << "DEBUG: Nie udalo sie zaladowac background.jpg!" << endl;
		system("pause");
	}
	sf::Sprite background;
	background.setTexture(teksturabackground);
	background.setScale(
		1920.f / background.getLocalBounds().width,
		1080.f / background.getLocalBounds().height
	);
	//inicjalizacja gracza
	gracz player("Kiryu", 100, 3, "P:\\projekt\\Projekt\\Projekt\\kiryu.png");
	float velocity = 5.f;
	float gravity = 0.5f;
	//MaszynaStanow machine;
	//sf::Clock clock;

    // Odpalamy pierwszy stan (np. Menu)
    //machine.addState(std::make_unique<MenuState>());

    while (window.isOpen()) {
			//sf::FloatRect granica = player.getGlobalBounds();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			player.handleInput();
			player.update();

			float cameraX = player.getPosition().x;
			if (cameraX < 960.f) cameraX = 960.f;

			camera.setCenter(cameraX, 540);

			window.clear();
			window.setView(camera);

			window.draw(background);
			window.draw(ground);
			player.draw(window);
			window.display();
		}
    return 0;
}