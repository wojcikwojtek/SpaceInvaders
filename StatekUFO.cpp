module StatekUFO;
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

StatekUFO::StatekUFO() : spawn_cooldown(30 * 60), size(70.f, 30.f), autodestruct(5), is_dead(false) {
	//sprite.setFillColor(sf::Color::Red);
	//sprite.setSize(sf::Vector2f(size, 30.f));
	//sprite.setPosition(sf::Vector2f(SCREEN_WIDTH + size + 3.f, 40.f));
	std::shared_ptr<sf::Texture> temp = std::make_shared<sf::Texture>();
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites\\UFO.png");
	if (!temp->loadFromFile(sciezka.string())) {
		std::cout << "Blad ladowania textury gracza" << std::endl;
	}
	temp->setSmooth(true);
	tekstury.push_back(temp);
	std::shared_ptr<sf::Texture> temp1 = std::make_shared<sf::Texture>();
	std::filesystem::path sciezka1 = std::filesystem::current_path();
	sciezka1.append("sprites\\explosion.png");
	if (!temp1->loadFromFile(sciezka1.string())) {
		std::cout << "Blad ladowania textury wybuchu" << std::endl;
	}
	temp1->setSmooth(true);
	tekstury.push_back(temp1);
	sprite.setTexture(*tekstury[0]);
	sprite.setPosition(sf::Vector2f(SCREEN_WIDTH + size.x + 3.f, 40.f));
	seed = std::mt19937{ std::random_device()() };
	dist = std::uniform_int_distribution<>(1, 100);
	dist1 = std::uniform_int_distribution<>(6, 10);
}

StatekUFO::~StatekUFO() {}

int StatekUFO::getSpawnCooldown() {
	return spawn_cooldown;
}

void StatekUFO::resetPosition() {
	sprite.setPosition(sf::Vector2f(SCREEN_WIDTH + size.x + 3.f, 10.f));
}

bool StatekUFO::should_I_Spawn() {
	int random_nb = dist(seed);
	if (random_nb == 100 && spawn_cooldown >= 30 * 60) {
		spawn_cooldown = 0;
		return true;
	}
	spawn_cooldown++;
	return false;
}

void StatekUFO::akcja() {
	sprite.move(sf::Vector2f(-2.f, 0.f));
	window.draw(sprite);
}

bool StatekUFO::check_death(Pocisk& p) {
	if (p.getSprite().getPosition().y <= sprite.getPosition().y && p.getSprite().getPosition().x >= sprite.getPosition().x && p.getSprite().getPosition().x <= sprite.getPosition().x + size.x) {
		//this->resetPosition();
		//spawn_cooldown = 0;
		is_dead = true;
		sf::Sprite sprite2;
		sprite2.setTexture(*tekstury[1]);
		sprite2.setPosition(sprite.getPosition());
		sprite = sprite2;
		return true;
	}
	return false;
}

float StatekUFO::get_x_position() {
	return sprite.getPosition().x;
}

int StatekUFO::getPoints() {
	int liczba = dist1(seed);
	return liczba * 10;
}

bool StatekUFO::should_I_autodestruct() {
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