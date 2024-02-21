module FlotaObcych;
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
import <thread>;
import "Game.h";
import Pocisk;
import StatekObcy;
import Oslona;
import StatekGracz;
import ObcyWersjaA;
import ObcyWersjaB;
import ObcyWersjaC;

FlotaObcych::FlotaObcych(float x, float y) : right(true), points(0), ile_zniszczono(0) {
	std::shared_ptr<sf::SoundBuffer> temp = std::make_shared<sf::SoundBuffer>();
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("audio\\8-bit-explosion_F.wav");
	if (!temp->loadFromFile(sciezka.string())) {
		std::cout << "Nie zaladowano dzwieku" << std::endl;
	}
	buffers.push_back(temp);
	std::shared_ptr<sf::SoundBuffer> temp1 = std::make_shared<sf::SoundBuffer>();
	std::filesystem::path sciezka1 = std::filesystem::current_path();
	sciezka1.append("audio\\laser2.wav");
	if (!temp1->loadFromFile(sciezka1.string())) {
		std::cout << "Nie zaladowano dzwieku" << std::endl;
	}
	buffers.push_back(temp1);
	dzwiek_wybuch.setBuffer(*buffers[0]);
	dzwiek_strzal.setBuffer(*buffers[1]);
	for (int i = 0; i < 5; i++) {
		float temp_x = x;
		std::vector<std::shared_ptr<StatekObcy>> temp_vec;
		for (int j = 0; j < 11; j++) {
			if (i == 0) {
				std::shared_ptr<StatekObcy> temp = std::make_shared<ObcyWersjaA>(temp_x, y, starting_speed);
				temp_vec.push_back(temp);
			}
			else if (i == 1 or i == 2) {
				std::shared_ptr<StatekObcy> temp = std::make_shared<ObcyWersjaB>(temp_x, y, starting_speed);
				temp_vec.push_back(temp);
			}
			else {
				std::shared_ptr<StatekObcy> temp = std::make_shared<ObcyWersjaC>(temp_x, y, starting_speed);
				temp_vec.push_back(temp);
			}
			temp_x += 28.f + 15.f;
		}
		sprites.push_back(temp_vec);
		y += 35.f;
	}
}

FlotaObcych::~FlotaObcych() {}

void FlotaObcych::akcja() {
	if (sprites.size() == 0) {
		return;
	}
	auto move_obcy = [](std::vector<std::vector<std::shared_ptr<StatekObcy>>> sprites) {
		for (int i = 0; i < sprites.size(); i++) {
			for (int j = 0; j < sprites[i].size(); j++) {
				sprites[i][j]->akcja();
			}
		}
	};
	auto movedown_obcy = [](std::vector<std::vector<std::shared_ptr<StatekObcy>>> sprites) {
		for (int i = 0; i < sprites.size(); i++) {
			for (int j = 0; j < sprites[i].size(); j++) {
				sprites[i][j]->movedown();
			}
		}
	};
	auto obcy_strzela = [this](std::vector<std::vector<std::shared_ptr<StatekObcy>>> sprites) {
		for (int i = 0; i < sprites.size(); i++) {
			for (int j = 0; j < sprites[i].size(); j++) {
				this->strzelaj(sprites[i][j]);
			}
		}
	};
	if (ile_zniszczono == 11) {
		ile_zniszczono = 0;
		starting_speed += 0.1f;
		for (int i = 0; i < sprites.size(); i++) {
			for (int j = 0; j < sprites[i].size(); j++) {
				sprites[i][j]->changeSpeed(starting_speed);
			}
		}
	}
	if (right == true) {
		std::shared_ptr<StatekObcy> en = this->most_right();
		if (en.get()->getSprite().getPosition().x + en.get()->getSize().x >= window.getSize().x) {
			right = false;
			/*for (int i = 0; i < sprites.size(); i++) {
				for (int j = 0; j < sprites[i].size(); j++) {
					sprites[i][j].get()->movedown();
					this->strzelaj(sprites[i][j]);
				}
			}*/
			std::thread th1(movedown_obcy, sprites);
			std::thread th2(obcy_strzela, sprites);
			th1.join();
			th2.join();
		}
		else {
			/*for (int i = 0; i < sprites.size(); i++) {
				for (int j = 0; j < sprites[i].size(); j++) {
					sprites[i][j].get()->akcja();
					this->strzelaj(sprites[i][j]);
				}
			}*/
			std::thread th1(move_obcy, sprites);
			std::thread th2(obcy_strzela, sprites);
			th1.join();
			th2.join();
		}
		//delete en;
	}
	else {
		std::shared_ptr<StatekObcy> en = this->most_left();
		if (en.get()->getSprite().getPosition().x <= 0) {
			right = true;
			/*for (int i = 0; i < sprites.size(); i++) {
				for (int j = 0; j < sprites[i].size(); j++) {
					sprites[i][j].get()->movedown();
					this->strzelaj(sprites[i][j]);
				}
			}*/
			std::thread th1(movedown_obcy, sprites);
			std::thread th2(obcy_strzela, sprites);
			th1.join();
			th2.join();
		}
		else {
			/*for (int i = 0; i < sprites.size(); i++) {
				for (int j = 0; j < sprites[i].size(); j++) {
					sprites[i][j].get()->akcja();
					this->strzelaj(sprites[i][j]);
				}
			}*/
			std::thread th1(move_obcy, sprites);
			std::thread th2(obcy_strzela, sprites);
			th1.join();
			th2.join();
		}
		//delete en;
	}
	/*for (int i = 0; i < sprites.size(); i++) {
		for (int j = 0; j < sprites[i].size(); j++) {
			random_nb = dist(seed);
			if (random_nb == 2000) {
				std::shared_ptr<Pocisk> p = std::make_shared<Pocisk>("pocisk_obcego.png");
				p->getSprite().setPosition(sprites[i][j].get()->getCentrum());
				pociski.push_back(p);
			}
		}
	}*/
	for (int i = 0; i < pociski.size(); i++) {
		pociski[i]->getSprite().move(0.f, 10.f);
		if (pociski[i]->getSprite().getPosition().y >= SCREEN_HEIGHT) {
			pociski.erase(pociski.begin() + i);
		}
	}
}

void FlotaObcych::strzelaj(std::shared_ptr<StatekObcy> obcy) {
	if (czy_strzelic.CzyMogeStrzelic()==true && obcy->getIs_dead() == false) {
		dzwiek_strzal.play();
		std::filesystem::path sciezka = std::filesystem::current_path();
		sciezka.append("sprites\\pocisk_obcego.png");
		std::shared_ptr<Pocisk> p = std::make_shared<Pocisk>(sciezka.string());
		p->getSprite().setPosition(obcy->getCentrum());
		pociski.push_back(p);
	}
}

void FlotaObcych::draw(StatekGracz& player, std::vector<Oslona>& o) {
	if (sprites.size() == 0) {
		return;
	}
	if (kolejka_usuwania.size() != 0) {
		for (int i = 0; i < kolejka_usuwania.size(); i++) {
			if (kolejka_usuwania[i][2] == 0) {
				sprites[kolejka_usuwania[i][0]].erase(sprites[kolejka_usuwania[i][0]].begin() + kolejka_usuwania[i][1]);
				kolejka_usuwania.erase(kolejka_usuwania.begin());
			}
			else {
				kolejka_usuwania[i][2]--;
			}
		}
	}
	for (int i = 0; i < sprites.size(); i++) {
		for (int j = 0; j < sprites[i].size(); j++) {
			window.draw(sprites[i][j]->getSprite());
		}
	}
	if (this->getLowestYCord() >= player.getSprite().getPosition().y) {
		saveHighScore(player, highscore_str);
		end(player.getPoints());
	}
	for (int i = 0; i < pociski.size(); i++) {
		if (player.check_death(*pociski[i])) {
			pociski.erase(pociski.begin() + i);
			//if (player.isLifeEmpty()) {
			//	/*saveHighScore(player, highscore_str);
			//	end(player.getPoints());*/
			//}
			//else {
			//	pociski.erase(pociski.begin() + i);
			//}
		}
		else {
			bool usuwamy = false;
			for (int j = 0; j < o.size(); j++) {
				if (o[j].check_collision(*pociski[i]) == true) {
					pociski.erase(pociski.begin() + i);
					usuwamy = true;
					break;
				}
			}
			if (usuwamy == false) {
				window.draw(pociski[i]->getSprite());
			}
		}
	}
}

bool FlotaObcych::check_collision(Pocisk& p) {
	for (int i = 0; i < sprites.size(); i++) {
		for (int j = 0; j < sprites[i].size(); j++) {
			if (sprites[i][j]->check_death(p) == true) {
				/*delete sprites[i][j];
				sprites[i].erase(sprites[i].begin() + j);*/
				dzwiek_wybuch.play();
				ile_zniszczono++;
				std::vector<int> temp{ i, j, 5 };
				kolejka_usuwania.push_back(temp);
				points = sprites[i][j]->getPoints();
				return true;
			}
		}
	}
	return false;
}

std::shared_ptr<StatekObcy> FlotaObcych::most_left() {
	std::shared_ptr<StatekObcy> en = std::make_shared<StatekObcy>(SCREEN_WIDTH, 0.f, 0.f);
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i].size() == 0) {
			continue;
		}
		if (sprites[i][0].get()->getSprite().getPosition().x < en.get()->getSprite().getPosition().x) {
			en = sprites[i][0];
		}
	}
	return en;
}

std::shared_ptr<StatekObcy> FlotaObcych::most_right() {
	std::shared_ptr<StatekObcy> en = std::make_shared<StatekObcy>(0.f, 0.f, 0.f);
	for (int i = 0; i < sprites.size(); i++) {
		if (sprites[i].size() == 0) {
			continue;
		}
		if (sprites[i][sprites[i].size() - 1].get()->getSprite().getPosition().x > en.get()->getSprite().getPosition().x) {
			en = sprites[i][sprites[i].size() - 1];
		}
	}
	return en;
}

bool FlotaObcych::is_empty() {
 	for (int i = 0; i < 5; i++) {
		if (sprites[i].size() != 0) {
			return false;
		}
	}
	return true;
}

void FlotaObcych::respawn(float x, float y) {
   	right = true;
	starting_speed = starting_speed - 0.3f;
	for (int i = 0; i < 5; i++) {
		float temp_x = x;
		for (int j = 0; j < 11; j++) {
			if (i == 0) {
				std::shared_ptr<StatekObcy> temp = std::make_shared<ObcyWersjaA>(temp_x, y, starting_speed);
				sprites[i].push_back(temp);
			}
			else if (i == 1 or i == 2) {
				std::shared_ptr<StatekObcy> temp = std::make_shared<ObcyWersjaB>(temp_x, y, starting_speed);
				sprites[i].push_back(temp);
			}
			else {
				std::shared_ptr<StatekObcy> temp = std::make_shared<ObcyWersjaC>(temp_x, y, starting_speed);
				sprites[i].push_back(temp);
			}
			temp_x += 28.f + 15.f;
		}
		y += 35.f;
	}
}

float FlotaObcych::getLowestYCord() {
	int i = 4;
	while (sprites[i].size() == 0) {
		if (i <= 0) {
			return 0.f;
		}
		i--;
	}
	return sprites[i][0]->getSprite().getPosition().y + sprites[i][0]->getSize().y;
}

int FlotaObcych::getPoints() {
	int temp = points;
	points = 0;
	return temp;
}