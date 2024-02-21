module StatekObcy;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <SFML/Audio.hpp>;
import <random>;
import <string>;
import <memory>;
import <filesystem>;
import "Game.h";
import Pocisk;
import Statek;

StatekObcy::StatekObcy(float x, float y, float speed) : speed(speed), right(true), is_dead(false), autodestruct(5), size(28.f, 21.f), obecna_textura(1), zmiana_textury(10) {
	/*sprite.setFillColor(sf::Color::Magenta);
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setSize(sf::Vector2f(size, size));*/
	/*
	if (!textura1.loadFromFile("invader.png")) {
		std::cout << "Blad ladowania textury" << std::endl;
	}
	textura1.setSmooth(true);
	if (!textura2.loadFromFile("invader1.png")) {
		std::cout << "Blad ladowania textury" << std::endl;
	}
	textura2.setSmooth(true);
	*/
	std::shared_ptr<sf::Texture> temp = std::make_shared<sf::Texture>();
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites\\explosion.png");
	if (!temp->loadFromFile(sciezka.string())) {
		std::cout << "Blad ladowania textury wybuchu" << std::endl;
	}
	temp->setSmooth(true);
	tekstury.push_back(temp);
	sprite.setPosition(sf::Vector2f(x, y));
	/*
	sprite.setTexture(textura1);
	sprite.setPosition(sf::Vector2f(x, y));
	*/
}

StatekObcy::~StatekObcy() {}

//sf::RectangleShape& StatekObcy::getSprite() {
//	return sprite;
//}

sf::Sprite& StatekObcy::getSprite() {
	return sprite;
}

bool StatekObcy::check_death(Pocisk& p) {
	if (p.getSprite().getPosition().y <= sprite.getPosition().y + size.y && p.getSprite().getPosition().y >= sprite.getPosition().y && p.getSprite().getPosition().x + p.getSize() >= sprite.getPosition().x && p.getSprite().getPosition().x <= sprite.getPosition().x + size.x) {
		sprite.setTexture(*tekstury[0]);
		is_dead = true;
		return true;
	}
	return false;
}

bool StatekObcy::should_I_autodestruct() {
	if (is_dead == true && autodestruct == 0) {
		return true;
	}
	else if (is_dead == true && autodestruct != 0) {
		autodestruct--;
		return false;
	}
	else {
		return false;
	}
}

void StatekObcy::akcja() {
	if (right == true) {
		sprite.move(sf::Vector2f(speed, 0.f));
	}
	else {
		sprite.move(sf::Vector2f(-speed, 0.f));
	}
	if (zmiana_textury == 0 && is_dead == false) {
		if (obecna_textura == 1) {
			sprite.setTexture(*tekstury[2]);
			obecna_textura++;
		}
		else {
			sprite.setTexture(*tekstury[1]);
			obecna_textura--;
		}
		zmiana_textury = 10;
	}
	else {
		zmiana_textury--;
	}
}

sf::Vector2f StatekObcy::getSize() {
	return size;
}

sf::Vector2f StatekObcy::getCentrum() {
	return sf::Vector2f(sprite.getPosition().x + size.x / 2, sprite.getPosition().y + size.y / 2);
}

void StatekObcy::movedown() {
	right = !right;
	sprite.move(sf::Vector2f(0.f, 30.f));
}

int StatekObcy::getPoints() {
	return 0;
}

void StatekObcy::changeSpeed(float new_speed) {
	speed = new_speed;
}

bool StatekObcy::getIs_dead() {
	return is_dead;
}