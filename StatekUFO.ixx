export module StatekUFO;
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

/** Klasa reprezentujaca UFO ktore co jakis czas przelatuje przez ekran
*/
export class StatekUFO : public Statek {
private:
	//sf::RectangleShape sprite;
	/*sf::Texture textura;
	sf::Texture textura_wybuchu;*/
	/*std::vector<std::shared_ptr<sf::Texture>> tekstury;
	sf::Sprite sprite;*/
	sf::Vector2f size;
	int spawn_cooldown;
	std::mt19937 seed;
	std::uniform_int_distribution<> dist;
	std::uniform_int_distribution<> dist1;
	bool is_dead;
	int autodestruct;
public:
	/** Konstruktor klasy StatekUFO
	*/
	StatekUFO();
	/** Destruktor klasy StatekUFO
	*/
	~StatekUFO();
	/** Metoda zwracajaca pole spawn_cooldown
	*/
	int getSpawnCooldown();
	/** Metoda resetujaca pozycje UFO na sam skraj ekranu
	*/
	void resetPosition();
	/** Metoda okreslajaca czy UFO moze zaczac przelatywac przez ekran. Jest to determinowane jesli minie spawn_cooldown i zostanie wylosowana liczba 100 z przedzialu od 1 do 100
	*/
	bool should_I_Spawn();
	/** Metoda ktora przesuwa w lewo UFO
	*/
	void akcja();
	/** Metoda ktora sprawdza czy UFO zostalo trafione pociskiem i jesli tak to zmienia jego teksture
	* @param p Pocisk dla ktorego sprawdzamy czy trafil UFO
	*/
	bool check_death(Pocisk& p);
	/** Metoda zwracajaca najbardziej polozona na lewo wspolrzedna x sprite'u
	*/
	float get_x_position();
	/** Metoda zwracajaca ile punktow powinien uzyskac gracz za zestrzelenie UFO. Punkty sa przydzielane losowo
	*/
	int getPoints();
	/** Metoda okrelajaca czy UFO powinno zostac usuniete jesli minie odpowiednio czasu od jego zestrzelenia 
	*/
	bool should_I_autodestruct();
};