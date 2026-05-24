
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "MaszynaStanow.h"
#include "state.h"
#include "gracz.h"
#include "tlo.h"
#include <iostream>

int main()
{
	// ustawienie okna
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Moja gierka"); //sf::Style::Fullscreen
	window.setFramerateLimit(60);
	//background
	tlo mapa1;
	mapa1.seg("P:\\projekt\\Projekt\\Projekt\\background2.jpg");
	mapa1.seg("P:\\projekt\\Projekt\\Projekt\\background.jpg");
	//pod³o¿e
	sf::RectangleShape ground(sf::Vector2f(mapa1.getDlugosc(), 500.f));
	ground.setFillColor(sf::Color::Black);
	ground.setPosition(0.f, 1000.f);
	//inicjalizacja gracza
	gracz player("Kiryu", 100, 3, "P:\\projekt\\Projekt\\Projekt\\kiryu.png");
	player.ustawBariere(mapa1);
	sf::View camera(sf::FloatRect(0, 0, 1920, 1080));
	float velocity = 5.f;
	float gravity = 0.5f;


	//MaszynaStanow machine;
	//sf::Clock clock;

    // Odpalamy pierwszy stan (np. Menu)
    //machine.addState(std::make_unique<MenuState>());

    while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			player.handleInput();
			player.update();

			float cameraX = player.getPosition().x;
			if (cameraX < 960.f) 
				cameraX = 960.f;

			if (cameraX > mapa1.getDlugosc() - 960.f) 
				cameraX = mapa1.getDlugosc() - 960.f;

			camera.setCenter(cameraX, 540);
			ground.setPosition(cameraX - 960.f, 1000.f);

			window.clear();
			window.setView(camera);

			mapa1.draw(window);
			window.draw(ground);
			player.draw(window);
			window.display();
		}
    return 0;
}