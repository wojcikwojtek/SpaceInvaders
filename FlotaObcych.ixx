export module FlotaObcych;
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
import <thread>;
import "Game.h";
import Pocisk;
import StatekObcy;
import Oslona;
import StatekGracz;
import CzyObcyStrzela;

/** Klasa reprezentujaca wszystkie wrogie statki jakie sa na ekranie
*/
export class FlotaObcych : public Game {
private:
	std::vector<std::vector<std::shared_ptr<StatekObcy>>> sprites;
	std::vector<std::shared_ptr<Pocisk>> pociski;
	std::vector<std::vector<int>> kolejka_usuwania;
	bool right;
	CzyObcyStrzela czy_strzelic;
	int points;
	std::vector<std::shared_ptr<sf::SoundBuffer>> buffers;
	sf::Sound dzwiek_wybuch;
	sf::Sound dzwiek_strzal;
	float starting_speed = 0.3f;
	int ile_zniszczono;
public:
	/** Konstruktor klasy FlotaObcych
	* @param x wspolrzedna x-owa 
	* @param y wspolrzedna y-owa
	*/
	FlotaObcych(float x, float y);
	/** Destruktor klasy FlotaObcych
	*/
	~FlotaObcych();
	/** Metoda ktora odpowiada za przemieszczanie sie wszystkich przeciwnikow po ekranie oraz wywolania metody strzelaj. Wykonywane jest to na dwoch watkach
	*/
	void akcja();
	/** Metoda odpowiedzialna za wystrzelenie pocisku przez pojedynczy StatekObcy. Strzelenie jest mozliwe wtedy kiedy metoda CzyMogeStrzelic pola czy_strzelic zwroci true i wybrany obcy nie zostal zniszczony
	* @param obcy pojedynczy StatekObcy dla ktorego sprawdzamy czy moze strzelic
	*/
	void strzelaj(std::shared_ptr<StatekObcy> obcy);
	/** Metoda rysujaca na ekranie wszystkich wrogow i wszystkie wystrzelone pociski, a przy okazji sprawdza czy nie doszlo do kolizji pocisku z innym obiektem
	* @param player StatekGracza dla ktorego sprawdzamy czy nie zostal zestrzelony
	* @param o vector Oslon dla ktorego sprawdzamy czy jakas nie zostala trafiona
	*/
	void draw(StatekGracz& player, std::vector<Oslona>& o);
	/** Metoda sprawdzajaca czy ktorykolwiek z wrogow nie zostal trafiony pociskiem
	* @param p Pocisk dla ktorego sprawdzamy czy nie doszlo do kolizji
	*/
	bool check_collision(Pocisk& p);
	/** Metoda zwracajaca wskaznik na najbardziej na lewo StatekObcy
	*/
	std::shared_ptr<StatekObcy> most_left();
	/** Metoda zwracajaca wskaznik na najbardziej na prawo StatekObcy
	*/
	std::shared_ptr<StatekObcy> most_right();
	/** Metoda sprawdzajaca czy vector sprites jest pusty. Jak tak oznacza to ze wszyscy wrogowie zostali zestrzeleni
	*/
	bool is_empty();
	/** Metoda odradzajaca wszystkich wrogow
	* @param x wsporzedna x-owa
	* @param y wsporzedna y-owa
	*/
	void respawn(float x, float y);
	/** Metoda zwracajaca y-owa wsporzedna najnizej znajdujacego sie wroga
	*/
	float getLowestYCord();
	/** Metoda zwraca ilosc punktow przechowywane w polu points
	*/
	int getPoints();
};