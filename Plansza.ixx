export module Plansza;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <string>;
import <filesystem>;
import "Game.h";

/** Klasa reprezentujaca plansze jakie pojawiaja sie na poczatku i na koncu gry
*/
export class Plansza {
private:
	sf::Texture textura;
	sf::Sprite sprite;
public:
	/** Konstruktor klasy Plansza
	* @param nazwa_sprite nazwa pliku .png z ktorego zaladowac teksture, ktora pozniej zostanie ustawiona jako sprite
	*/
	Plansza(std::string nazwa_sprite);
	/** Destruktor klasy Plansza
	*/
	~Plansza();
	/** Metoda zwracajaca sprite 
	*/
	sf::Sprite& getSprite();
	/** Metoda ktora sprawdza jaki przycisk na klawiaturze zostal nacisniety. Jesli Enter to wywoluje gameLoop klasy Game, a jesli Esc to zamyka okno
	*/
	void akcja();
};