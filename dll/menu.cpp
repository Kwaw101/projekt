#include "menu.h"
#include "gra.h"
#include <fstream>
#include <sstream>
#include <iostream>

menu::menu(sf::RenderWindow& window, MaszynaStanow& machine)
    : _window(window), _machine(machine), _selectedOption(0) {
}

void stworzPlikBinarnyMenu() {
    std::vector<std::string> napisy = { "START", "STEROWANIE", "WYJSCIE" };
    std::ofstream plik("menu.dat", std::ios::binary);

    if (plik.is_open()) {
        size_t liczbaNapisow = napisy.size();
        plik.write(reinterpret_cast<const char*>(&liczbaNapisow), sizeof(liczbaNapisow));

        for (const std::string& s : napisy) {
            size_t dlugosc = s.size();
            plik.write(reinterpret_cast<const char*>(&dlugosc), sizeof(dlugosc));
            plik.write(s.c_str(), dlugosc);
        }
        plik.close();
    }
}

std::string menu::wczytajZPliku(std::string sciezka) {
    std::ifstream plik(sciezka);
    if (!plik.is_open()) return "Nie znaleziono pliku: " + sciezka;

    std::stringstream buffer;
    buffer << plik.rdbuf();
    return buffer.str();
}

void menu::init() {
    if (!_backgroundTexture.loadFromFile("P:\\projekt\\Projekt\\Projekt\\menu.jpg")) {
        std::cout << "B£¥D: Nie mo¿na wczytaæ menu.jpg" << std::endl;
    }
    _backgroundSprite.setTexture(_backgroundTexture);
    float scaleX = 1920.f / _backgroundTexture.getSize().x;
    float scaleY = 1080.f / _backgroundTexture.getSize().y;
    _backgroundSprite.setScale(scaleX, scaleY);

    stworzPlikBinarnyMenu();
    if (!_font.loadFromFile("P:\\projekt\\Projekt\\Projekt\\aerial.ttf")) {
        std::cout << "BLAD: Nie znaleziono aerial.ttf" << std::endl;
    }

    wczytajNapisyZBin();
    _infoText.setFont(_font);
    _infoText.setCharacterSize(24);
    _infoText.setFillColor(sf::Color(200, 200, 200));
    _infoText.setPosition(100.f, 750.f);
}

void menu::wczytajNapisyZBin() {
    std::ifstream plik("menu.dat", std::ios::binary);
    if (!plik) return;

    size_t liczbaNapisow;
    plik.read(reinterpret_cast<char*>(&liczbaNapisow), sizeof(liczbaNapisow));

    for (size_t i = 0; i < liczbaNapisow; ++i) {
        size_t dlugosc;
        plik.read(reinterpret_cast<char*>(&dlugosc), sizeof(dlugosc));

        std::string s(dlugosc, ' ');
        plik.read(&s[0], dlugosc);

        sf::Text text;
        text.setFont(_font);
        text.setString(s);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2.f);

        text.setPosition(150.f, 350.f + (i * 120.f));

        _menuOptions.push_back(text);
    }
    plik.close();
}

void menu::handleInput() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) _window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W) {
                _selectedOption = (_selectedOption - 1 + _menuOptions.size()) % _menuOptions.size();
            }
            if (event.key.code == sf::Keyboard::S) {
                _selectedOption = (_selectedOption + 1) % _menuOptions.size();
            }

            if (event.key.code == sf::Keyboard::Enter) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (_selectedOption == 0) {
                        _machine.addState(std::make_unique<gra>(_window, _machine), true);
                    }
                    else if (_selectedOption == 1) {
                        _infoText.setString(wczytajZPliku("P:\\projekt\\Projekt\\Projekt\\controls.txt"));
                    }
                    else if (_selectedOption == 2) {
                        _window.close();
                    }
                }
            }
        }
    }
}

void menu::update(float dt) {
    for (size_t i = 0; i < _menuOptions.size(); ++i) {
        if (i == _selectedOption)
            _menuOptions[i].setFillColor(sf::Color::Red);
        else
            _menuOptions[i].setFillColor(sf::Color::White);
    }
}

void menu::draw() {
    _window.draw(_backgroundSprite);

    for (auto& t : _menuOptions) {
        _window.draw(t);
    }
    _window.draw(_infoText);
}