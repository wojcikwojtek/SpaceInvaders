module ObcyWersjaB;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import "Game.h";
import Statek;
import StatekObcy;

ObcyWersjaB::ObcyWersjaB(float x, float y, float speed) : StatekObcy(x, y, speed), points(20) {
	std::shared_ptr<sf::Texture> t1 = std::make_shared<sf::Texture>();
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites\\invaderB.png");
	if (!t1->loadFromFile(sciezka.string())) {
		std::cout << "Blad ladowania textury" << std::endl;
	}
	t1->setSmooth(true);
	tekstury.push_back(t1);
	std::shared_ptr<sf::Texture> t2 = std::make_shared<sf::Texture>();
	std::filesystem::path sciezka1 = std::filesystem::current_path();
	sciezka1.append("sprites\\invaderB1.png");
	if (!t2->loadFromFile(sciezka1.string())) {
		std::cout << "Blad ladowania textury" << std::endl;
	}
	t2->setSmooth(true);
	tekstury.push_back(t2);
	sprite.setTexture(*tekstury[1]);
}

ObcyWersjaB::~ObcyWersjaB() {}

int ObcyWersjaB::getPoints() {
	return points;
}