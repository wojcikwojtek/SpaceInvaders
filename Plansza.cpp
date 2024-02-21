module Plansza;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <string>;
import <filesystem>;
import "Game.h";

Plansza::Plansza(std::string nazwa_sprite) {
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites");
	sciezka.append(nazwa_sprite);
	if (!textura.loadFromFile(sciezka.string())) {
		std::cout << "Nie udalo sie zaladowac obrazka planszy" << std::endl;
	}
	textura.setSmooth(true);
	sprite.setTexture(textura);
}

Plansza::~Plansza() {}

sf::Sprite& Plansza::getSprite() {
	return sprite;
}

void Plansza::akcja() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		Game::gameLoop();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		Game::closewindow();
	}
}