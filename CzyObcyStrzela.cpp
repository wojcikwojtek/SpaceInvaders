module CzyObcyStrzela;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import "Game.h";

CzyObcyStrzela::CzyObcyStrzela() : random_nb(0){
	seed = std::mt19937{ std::random_device()() };
	dist = std::uniform_int_distribution<>(1, 2000);
}

CzyObcyStrzela::~CzyObcyStrzela() {}

bool CzyObcyStrzela::CzyMogeStrzelic() {
	random_nb = dist(seed);
	if (random_nb == 2000) {
		return true;
	}
	return false;
}