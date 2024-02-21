module StatekGracz;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <SFML/Audio.hpp>;
import <random>;
import <string>;
import "Game.h";
import Pocisk;
import Oslona;
import StatekUFO;
import FlotaObcych;
import Statek;

StatekGracz::StatekGracz() : points(0), size(100.f, 76.f), respawn_cooldown(30), is_dead(false) {
	/*sprite.setFillColor(sf::Color::White);
	sprite.setRadius(50.f);
	sprite.setPosition(window.getSize().x / 2 - sprite.getRadius(), window.getSize().y - sprite.getRadius() * 2 - 10.f);*/
	std::shared_ptr<sf::Texture> temp = std::make_shared<sf::Texture>();
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites\\playertexture.png");
	if (!temp->loadFromFile(sciezka.string())) {
		std::cout << "Blad ladowania textury gracza" << std::endl;
	}
	temp->setSmooth(true);
	tekstury.push_back(temp);
	std::shared_ptr<sf::Texture> temp1 = std::make_shared<sf::Texture>();
	std::filesystem::path sciezka1 = std::filesystem::current_path();
	sciezka1.append("sprites\\playerdeath.png");
	if (!temp1->loadFromFile(sciezka1.string())) {
		std::cout << "Blad ladowania textury gracza" << std::endl;
	}
	temp1->setSmooth(true);
	tekstury.push_back(temp1);
	sprite.setTexture(*tekstury[0]);
	sprite.setPosition(window.getSize().x / 2 - size.x/2, window.getSize().y - size.y);
	std::shared_ptr<sf::SoundBuffer> temp2 = std::make_shared<sf::SoundBuffer>();
	std::filesystem::path sciezkaaudio = std::filesystem::current_path();
	sciezkaaudio.append("audio\\8-bit-explosion_F.wav");
	if (!temp2->loadFromFile(sciezkaaudio.string())) {
		std::cout << "Nie zaladowano dzwieku" << std::endl;
	}
	buffers.push_back(temp2);
	std::shared_ptr<sf::SoundBuffer> temp3 = std::make_shared<sf::SoundBuffer>();
	std::filesystem::path sciezkaaudio1 = std::filesystem::current_path();
	sciezkaaudio1.append("audio\\laser1.wav");
	if (!temp3->loadFromFile(sciezkaaudio1.string())) {
		std::cout << "Nie zaladowano dzwieku" << std::endl;
	}
	buffers.push_back(temp3);
	dzwiek_wybuch.setBuffer(*buffers[0]);
	dzwiek_strzal.setBuffer(*buffers[1]);
	float pos = SCREEN_WIDTH - 3 * 30 - 10;
	for (int i = 0; i < 3; i++) {
		/*sf::CircleShape circle;
		circle.setFillColor(sf::Color::White);
		circle.setRadius(10.f);
		circle.setPosition(sf::Vector2f(pos, 10.f));
		life.push_back(circle);*/
		//sf::Sprite* life_icon = new sf::Sprite();
		std::shared_ptr<sf::Sprite> life_icon = std::make_shared<sf::Sprite>();
		life_icon.get()->setTexture(*tekstury[0]);
		life_icon.get()->setScale(sf::Vector2f(0.3f, 0.3f));
		life_icon.get()->setPosition(sf::Vector2f(pos, 10.f));
		life.push_back(life_icon);
		pos += 30;
	}
}

StatekGracz::~StatekGracz() {}

//sf::CircleShape& StatekGracz::getSprite() {
//	return sprite;
//}

sf::Sprite& StatekGracz::getSprite() {
	return sprite;
}

void StatekGracz::akcja() {
	for (int i = 0; i < pociski.size(); i++) {
		pociski[i]->getSprite().move(0.f, -10.f);
		if (pociski[i]->getSprite().getPosition().y <= 0) {
			pociski.erase(pociski.begin());
		}
	}
	if (is_dead == true) {
		if (respawn_cooldown == 0) {
			this->respawn();
		}
		else {
			respawn_cooldown--;
		}
		return;
	}
	centrum = sf::Vector2f(sprite.getPosition().x + size.x/2, sprite.getPosition().y + size.y/2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x + size.x < window.getSize().x) {
		sprite.move(sf::Vector2f(4.f, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > 0) {
		sprite.move(sf::Vector2f(-4.f, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pociski.empty() == true) {
		dzwiek_strzal.play();
		std::filesystem::path sciezka = std::filesystem::current_path();
		sciezka.append("sprites\\pocisk_gracza.png");
		std::shared_ptr<Pocisk> p = std::make_shared<Pocisk>(sciezka.string());
		p.get()->getSprite().setPosition(centrum);
		pociski.push_back(p);
	}
}

void StatekGracz::draw_pocisk(FlotaObcych& en, std::vector<Oslona>& o, std::vector<StatekUFO>& ufos) {
	for (int i = 0; i < life.size(); i++) {
		window.draw(*life[i]);
	}
	if (ufos.size() > 0 && ufos[0].should_I_autodestruct() == true) {
		ufos.clear();
	}
	window.draw(sprite);
	for (int i = 0; i < pociski.size(); i++) {
		if (en.check_collision(*pociski[i]) == true) {
			pociski.erase(pociski.begin()+i);
			points += en.getPoints();
		}
		else if (ufos.size() > 0 && ufos[0].check_death(*pociski[i]) == true) {
			pociski.erase(pociski.begin()+i);
			dzwiek_wybuch.play();
			points += ufos[0].getPoints();
		}
		else {
			for (int j = 0; j < o.size(); j++) {
				if (o[j].check_collision(*pociski[i]) == true) {
					pociski.erase(pociski.begin()+i);
					return;
				}
			}
			window.draw(pociski[i]->getSprite());
		}
	}
}

bool StatekGracz::check_death(Pocisk& p) {
	if (is_dead == true) {
		return false;
	}
	if (p.getSprite().getPosition().y >= sprite.getPosition().y && p.getSprite().getPosition().x >= sprite.getPosition().x && p.getSprite().getPosition().x <= sprite.getPosition().x + size.x) {
		life.erase(life.begin());
		dzwiek_wybuch.play();
		sf::Sprite sprite2;
		sprite2.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y+28.f));
		sprite2.setTexture(*tekstury[1]);
		sprite = sprite2;
		is_dead = true;
		return true;
	}
	return false;
}

std::string StatekGracz::getPoints() {
	return std::to_string(points);
}

bool StatekGracz::isLifeEmpty() {
	if (life.size() == 0) {
		return true;
	}
	return false;
}

void StatekGracz::respawn() {
	if (life.size() == 0) {
		saveHighScore(*this, highscore_str);
		end(this->getPoints());
		return;
	}
	respawn_cooldown = 30;
	is_dead = false;
	sf::Sprite sprite2;
	sprite2.setTexture(*tekstury[0]);
	sprite = sprite2;
	sprite.setPosition(window.getSize().x / 2 - size.x / 2, window.getSize().y - size.y);
}