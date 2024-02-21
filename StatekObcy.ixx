export module StatekObcy;
import <iostream>;
import <vector>;
import <SFML/Graphics.hpp>;
import <SFML/Window.hpp>;
import <SFML/System.hpp>;
import <SFML/Audio.hpp>;
import <random>;
import <string>;
import <memory>;
import <filesystem>;
import "Game.h";
import Statek;
import Pocisk;

/** Klasa reprezentujaca pojedynczy statek wroga
*/
export class StatekObcy : public Statek {
protected:
	//sf::RectangleShape sprite;
	/*sf::Texture textura1;
	sf::Texture textura2;
	sf::Texture textura_wybuchu;*/
	/*std::vector<std::shared_ptr<sf::Texture>> tekstury;
	sf::Sprite sprite;*/
	//float size = 30;
	sf::Vector2f size;
	bool right;
	bool is_dead;
	int autodestruct;
	int obecna_textura;
	int zmiana_textury;
	float speed;
public:
	/** Konstruktor klasy StatekObcy
	* @param x wspolrzedna x-owa
	* @param y wspolrzedna y-owa
	* @param speed okresla predkosc z jakim porusza sie statek
	*/
	StatekObcy(float x, float y, float speed);
	/** Wirtualny destruktor klasy StatekObcy
	*/
	virtual ~StatekObcy();
	/** Metoda zwracajaca pole sprite
	*/
	sf::Sprite& getSprite();
	/** Metoda sprawdzajaca czy StatekObcy zostal trafiony pociskiem i jesli tak zmienia mu teksture
	* @param p Pocisk dla ktorego sprawdzamy czy trafil statek
	*/
	virtual bool check_death(Pocisk& p);
	/** Metoda poruszajaca statkiem w lewo lub w prawo zaleznie jaka wartosc przyjmie pole right
	*/
	virtual void akcja();
	/** Wirtualna metoda zwracajaca ile punktow mozna zdobyc za trafienie danego statku
	*/
	virtual int getPoints();
	/** Metoda zwracajaca rozmiar statku 
	*/
	sf::Vector2f getSize();
	/** Metoda zwracajaca wspolrzedne centrum spirte'u
	*/
	sf::Vector2f getCentrum();
	/** Metoda ktora sprawia ze statek opada o okreslana ilosc pikseli
	*/
	void movedown();
	/** Metoda ktora po uplywie okreslonego czasu zwraca informacje czy obiekt moze zostac usuniety. Od trafienia obiektu do jego usuniecia musi minac okreslony czas by mozna bylo zobaczyc na ekranie teksture wybuchu
	*/
	bool should_I_autodestruct();
	/** Metoda zmieniajaca predkosc z jaka porusza sie statek
	* @param new_speed nowa predkosc z jaka bedzie poruszal sie statek
	*/
	void changeSpeed(float new_speed);
	/** Metoda zwracajaca pole is_dead
	*/
	bool getIs_dead();
};