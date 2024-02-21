module Oslona;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import "Game.h";
import Pocisk;
import Bloczek;

Oslona::Oslona(float x, float y) {
	for (int i = 0; i < wiersze; i++) {
		float x1 = x;
		std::vector<std::shared_ptr<Bloczek>> vec;
		if (i == 0) {
			int tab[] = { 2, 1, 1, 3 };
			for (int j = 0; j < kolumny; j++) {
				std::shared_ptr<Bloczek> blok = std::make_shared<Bloczek>(x1, y, tab[j]);
				vec.push_back(blok);
				x1 += blok->getSize();
			}
			shape.push_back(vec);
			y += 25;
		}
		else if (i == 1) {
			for (int j = 0; j < kolumny; j++) {
				std::shared_ptr<Bloczek> blok = std::make_shared<Bloczek>(x1, y, 1);
				vec.push_back(blok);
				x1 += blok->getSize();
			}
			shape.push_back(vec);
			y += 25;
		}
		else {
			int tab[] = { 1, 4, 5, 1 };
			for (int j = 0; j < kolumny; j++) {
				std::shared_ptr<Bloczek> blok = std::make_shared<Bloczek>(x1, y, tab[j]);
				vec.push_back(blok);
				x1 += blok->getSize();
			}
			shape.push_back(vec);
			y += 25;
		}
	}
}

Oslona::~Oslona() {}

void Oslona::draw() {
	if (shape.size() == 0) {
		return;
	}
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[i].size(); j++) {
			window.draw(shape[i][j]->getSquare());
		}
	}
}

bool Oslona::check_collision(Pocisk& p) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[i].size(); j++) {
			if (shape[i][j]->check_collision(p) == true) {
				if (shape[i][j]->getWytrzymalosc() == 0) {
					shape[i].erase(shape[i].begin() + j);
				}
				return true;
			}
		}
	}
	return false;
}