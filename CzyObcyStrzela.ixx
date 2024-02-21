export module CzyObcyStrzela;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import "Game.h";

/** Klasa ktorej zadaniem jest okreslenie czy StatekObcy moze w obecnej klatce wystrzelic Pocisk
*/
export class CzyObcyStrzela {
private:
	std::mt19937 seed;
	std::uniform_int_distribution<> dist;
	int random_nb;
public:
	/** Konstruktor klasy CzyObcyStrzela
	*/
	CzyObcyStrzela();
	/** Destruktor klasy CzyObcyStrzela
	*/
	~CzyObcyStrzela();
	/** Metoda ktora z pomoca generatora liczb losowych mt19937 losuje liczbe z zakresu od 1 do 2000 i jesli zostanie wylosowana liczba 2000 oznacza to ze obcy moze strzelic i zwracane jest wtedy true
	*/
	bool CzyMogeStrzelic();
};