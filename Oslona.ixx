export module Oslona;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import <memory>;
import "Game.h";
import Pocisk;
import Bloczek;

/** Klasa reprezentujaca Oslone znajdujaca sie u dolu ekranu. Pojedyncza oslona zlozona jest z kilku bloczkow
*/
export class Oslona : public Game {
private:
	std::vector<std::vector<std::shared_ptr<Bloczek>>> shape;
	int wiersze = 3;
	int kolumny = 4;
public:
	/** Konstruktor klasy Oslona 
	* @param x wsporzedna x-owa
	* @param y wsporzedna y-owa
	*/
	Oslona(float x, float y);
	/** Destruktor klasy Oslona
	*/
	~Oslona();
	/** Metoda rysujaca na ekran wszystkie bloczki z ktorych sklada sie Oslona
	*/
	void draw();
	/** Metoda sprawdzajaca czy nie doszlo do kolizji z pociskiem 
	* @param p Pocisk dla ktorego sprawdzamy czy nie doszlo do kolizji 
	*/
	bool check_collision(Pocisk& p);
};