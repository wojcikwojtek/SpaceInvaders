module Bloczek;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import <filesystem>;
import "Game.h";
import Pocisk;

Bloczek::Bloczek(float x, float y, int typ_bloku) : typ_bloku(typ_bloku) {
	//square.setFillColor(sf::Color::Green);
	//square.setSize(sf::Vector2f(size, size));
	//square.setPosition(sf::Vector2f(x, y));
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites\\Bloczek");
	std::string nazwa = sciezka.string() + std::to_string(typ_bloku) + ".png";
	if (!textura.loadFromFile(nazwa)) {
		std::cout << "Blad ladowania textury bloczku" << std::endl;
	}
	textura.setSmooth(true);
	square.setTexture(textura);
	square.setPosition(sf::Vector2f(x, y));
}

Bloczek::~Bloczek() {}

bool Bloczek::check_collision(Pocisk& p) {
	if (p.getSprite().getPosition().y >= square.getPosition().y && p.getSprite().getPosition().y <= square.getPosition().y + size && p.getSprite().getPosition().x + 2 * p.getSize() >= square.getPosition().x && p.getSprite().getPosition().x <= square.getPosition().x + size) {
		wytrzymalosc--;
		std::filesystem::path sciezka = std::filesystem::current_path();
		sciezka.append("sprites\\Bloczek");
		std::string nazwa = sciezka.string();
		switch (wytrzymalosc) {
		case 3:
			nazwa += "A" + std::to_string(typ_bloku) + ".png";
			break;
		case 2:
			nazwa += "B" + std::to_string(typ_bloku) + ".png";
			break;
		case 1:
			nazwa += "C" + std::to_string(typ_bloku) + ".png";
			break;
		default:
			nazwa += std::to_string(typ_bloku) + ".png";
			break;
		}
		if (!textura.loadFromFile(nazwa)) {
			std::cout << "Blad ladowania textury bloczku" << std::endl;
		}
		textura.setSmooth(true);
		square.setTexture(textura);
		return true;
	}
	return false;
}

int Bloczek::getWytrzymalosc() {
	return wytrzymalosc;
}

float Bloczek::getSize() {
	return size;
}

sf::Sprite& Bloczek::getSquare() {
	return square;
}