#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <string>
#include <ranges>
#include <filesystem>
#include <regex>
#include <fstream>
#include "Game.h"
import StatekGracz;
import Pocisk;
import Bloczek;
import Oslona;
import StatekUFO;
import StatekObcy;
import FlotaObcych;
import Plansza;

sf::RenderWindow Game::window;
std::string Game::highscore_str = "0";

void init_text(sf::Text& text, sf::Font& font, float x, float y, std::string caption) {
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setString(caption);
	text.setPosition(sf::Vector2f(x, y));
}

std::string readHighScore() {
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("dodatkowe_dane\\highscore.txt");
	std::regex reg("[0-9]+");
	std::vector<std::string> dane;
	std::ifstream PLIK(sciezka.string());
	if (PLIK.is_open()) {
		std::ranges::copy(std::ranges::istream_view<std::string>(PLIK), std::back_inserter(dane));
		if (dane.size() == 0) {
			return "0";
		}
		for (int i = 0; i < dane.size(); i++) {
			if (std::regex_match(dane[i], reg)) {
				return dane[i];
			}
		}
		return "0";
	}
	else {
		return "0";
	}
}

void saveHighScore(StatekGracz& player, std::string& highscore_str) {
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("dodatkowe_dane\\highscore.txt");
	std::string playerscore = player.getPoints();
	if (std::stoi(playerscore) > std::stoi(highscore_str)) {
		std::ofstream PLIK(sciezka.string());
		if (PLIK.is_open()) {
			std::vector<std::string> outVec;
			outVec.push_back(playerscore);
			std::ranges::copy(outVec, std::ostream_iterator<std::string>(PLIK, " "));
		}
		PLIK.close();
	}
}

void Game::start() {
	if (window.isOpen()) {
		return;
	}
	window.create(sf::VideoMode(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, 32), "Space Invaders", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	/*sf::Texture obrazek;
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites\\start.png");
	if (!obrazek.loadFromFile(sciezka.string())) {
		std::cout << "Nie udalo sie zaladowac obrazka startowego" << std::endl;
	}
	sf::Sprite startSprite;
	startSprite.setTexture(obrazek);
	window.draw(startSprite);
	window.display();
	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			gameLoop();
		}
	}*/
	Plansza planszaStartowa("start.png");
	window.draw(planszaStartowa.getSprite());
	window.display();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		planszaStartowa.akcja();
	}
	//gameLoop();
}

void Game::gameLoop() {
	StatekGracz player;
	FlotaObcych przeciwnicy(0.f, 80.f);
	std::vector<Oslona> oslony;
	highscore_str = readHighScore();
	sf::Text score, playerscore, highscore_text, highscore;
	sf::Font font;
	std::filesystem::path sciezkafont = std::filesystem::current_path();
	sciezkafont.append("dodatkowe_dane\\Retro_Gaming.ttf");
	if (!font.loadFromFile(sciezkafont.string())) {
		std::cout << "Blad wczytywania fontu" << std::endl;
	}
	init_text(score, font, 10.f, 10.f, "SCORE: ");
	init_text(playerscore, font, 120.f, 10.f, "0");
	init_text(highscore_text, font, 250.f, 10.f, "HI-SCORE: ");
	init_text(highscore, font, 410.f, 10.f, highscore_str);
	float odstep = 40;
	for (int i = 0; i < 4; i++) {
		Oslona osl(odstep, SCREEN_HEIGHT - 200.f);
		oslony.push_back(osl);
		odstep += 150.f;
	}
	StatekUFO ufo;
	std::vector<StatekUFO> ufos;
	while (window.isOpen()) {
		window.clear(sf::Color::Black);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (ufo.should_I_Spawn() == true && ufos.size() == 0) {
			ufos.push_back(ufo);
		}
		player.akcja();
		player.draw_pocisk(przeciwnicy, oslony, ufos);
		przeciwnicy.akcja();
		przeciwnicy.draw(player, oslony);
		for (int i = 0; i < oslony.size(); i++) {
			oslony[i].draw();
		}
		if (ufos.size() > 0) {
			if (ufos[0].get_x_position() < -70.f) {
				ufos.clear();
			}
			else {
				ufos[0].akcja();
			}
		}
		window.draw(score);
		window.draw(highscore_text);
		window.draw(highscore);
		playerscore.setString(player.getPoints());
		window.draw(playerscore);
		window.display();
		if (przeciwnicy.is_empty()) {
			przeciwnicy.respawn(0.f, 80.f);
		}
	}
}

void Game::end(std::string score) {
	window.clear();
	/*sf::Texture obrazek_konca;
	std::filesystem::path sciezka = std::filesystem::current_path();
	sciezka.append("sprites\\end.png");
	if (!obrazek_konca.loadFromFile(sciezka.string())) {
		std::cout << "Nie zaladowano obrazka" << std::endl;
	}
	obrazek_konca.setSmooth(true);
	sf::Sprite sprite;
	sprite.setTexture(obrazek_konca);*/
	Plansza planszaKoncowa("end.png");
	sf::Text final_score;
	sf::Font font;
	std::filesystem::path sciezkafont = std::filesystem::current_path();
	sciezkafont.append("dodatkowe_dane\\Retro_Gaming.ttf");
	if (!font.loadFromFile(sciezkafont.string())) {
		std::cout << "Blad wczytywania fontu" << std::endl;
	}
	init_text(final_score, font, 340.f, 332.f, score);
	final_score.setCharacterSize(30);
	window.draw(planszaKoncowa.getSprite());
	window.draw(final_score);
	window.display();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		planszaKoncowa.akcja();
	}
}

void Game::closewindow() {
	window.close();
}