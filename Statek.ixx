export module Statek;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import "Game.h";
import Pocisk;

/** Klasa abstrakcyjna reprezentujaca pojedynczy statek
*/
export class Statek : public Game {
protected:
	std::vector<std::shared_ptr<sf::Texture>> tekstury;
	sf::Sprite sprite;
	//sf::Vector2f size;
public:
	/** Konstruktor klasy Statek
	*/
	Statek() {}
	/** Destruktor klasy Statek
	*/
	~Statek() {}
	/** Metoda czysto wirtualna
	*/
	virtual void akcja() = 0;
	/** Metoda czysto wirtualna
	* @param p obiekt klasy Pocisk
	*/
	virtual bool check_death(Pocisk& p) = 0;
};