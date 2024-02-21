module Pocisk;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import "Game.h";

Pocisk::Pocisk(std::string nazwa_obrazka) {
	/*sprite.setFillColor(sf::Color::Red);
	sprite.setRadius(radius);*/
	if (!textura.loadFromFile(nazwa_obrazka)) {
		std::cout << "Blad ladowania tekstury pocisku" << std::endl;
	}
	textura.setSmooth(true);
	sprite.setTexture(textura);
}

Pocisk::~Pocisk() {}

sf::Sprite& Pocisk::getSprite() {
	return sprite;
}

int Pocisk::getSize() {
	return size;
}