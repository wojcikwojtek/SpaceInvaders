export module Pocisk;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import "Game.h";

/** Klasa reprezentujaca pojedynczy Pocisk
*/
export class Pocisk {
private:
	sf::Texture textura;
	sf::Sprite sprite;
	int size = 5;
public:
	/** Konstruktor klasy Pocisk
	* @param nazwa_obrazka nazwa pliku .png z ktorego zaladowac teksture
	*/
	Pocisk(std::string nazwa_obrazka);
	/** Destruktor klasy Pocisk
	*/
	~Pocisk();
	/** Metoda zwracajaca pole sprite
	*/
	sf::Sprite& getSprite();
	/** Metoda zwracajaca rozmiar pocisku
 	*/
	int getSize();
};