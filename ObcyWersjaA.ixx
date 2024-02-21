export module ObcyWersjaA;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <random>;
import <string>;
import <filesystem>;
import "Game.h";
import Statek;
import StatekObcy;

/** Klasa reprezentujaca typ kosmity ktory zwraca 40 punktow
*/
export class ObcyWersjaA : public StatekObcy {
private:
	int points;
public:
	/** Konstruktor klasy ObcyWersjaA
	* @param x wsporzedna x-owa
	* @param y wsporzedna y-owa
	* @param speed zmienna okreslajaca predkosc z jaka porusza sie obcy
	*/
	ObcyWersjaA(float x, float y, float speed);
	/** Destruktor klasy ObcyWersjaA
	*/
	~ObcyWersjaA();
	/** metoda zwracajaca ile punktow mozna zyskac za zestrzelenie tego typu Obecego
	*/
	virtual int getPoints();
};