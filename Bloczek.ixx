export module Bloczek;
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

/**Klasa reprezentujaca pojedynczy bloczek ktory wchodzi w sklad oslony 
*/
export class Bloczek {
private:
	sf::Texture textura;
	sf::Sprite square;
	float size = 25;
	int wytrzymalosc = 4;
	int typ_bloku;
public:
	/** Konstruktor klasy Bloczek
	* @param x wspolrzedna x-owa
	* @param y wspolrzedna y-owa
	* @param typ_bloku jakiego typu jest blok. W zaleznosci jaka liczbe tu podamy zostanie wczytana inna tekstura
	*/
	Bloczek(float x, float y, int typ_bloku);
	/** Destruktor klasy Bloczek
	*/
	~Bloczek();
	/** Metoda ktora sprawdza czy nie doszlo do kolizji pocisku z bloczkiem. Jesli tak to zostaje zwrocone true, wytrzynalosc zostaje zdekrementowana i zostaje zmieniona tekstura odpowiadajaca temu ile zostalo wytrzymalosci bloczkowi
	* @param p Pocisk dla ktorego sprawdzamy czy doszlo do kolizji
	*/
	bool check_collision(Pocisk& p);
	/** Metoda zwracajaca wytrzymalosc Bloczka
	*/
	int getWytrzymalosc();
	/** Metoda zwracajaca rozmiar Bloczka
	*/
	float getSize();
	/** Metoda zwracajaca pole square 
	*/
	sf::Sprite& getSquare();
};