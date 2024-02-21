export module StatekGracz;
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

/** Klasa reprezentujaca statek ktorym steruje gracz
*/
export class StatekGracz : public Statek {
private:
	//sf::CircleShape sprite;
	/*sf::Texture textura;
	sf::Texture textura_wybuchu;*/
	/*std::vector<std::shared_ptr<sf::Texture>> tekstury;
	sf::Sprite sprite;*/
	std::vector<std::shared_ptr<sf::SoundBuffer>> buffers;
	//sf::SoundBuffer buffer;
	sf::Sound dzwiek_wybuch;
	sf::Sound dzwiek_strzal;
	sf::Vector2f size;
	std::vector<std::shared_ptr<Pocisk>> pociski;
	sf::Vector2f centrum;
	int points;
	std::vector<std::shared_ptr<sf::Sprite>> life;
	int respawn_cooldown;
	bool is_dead;
public:
	/** Konstruktor klasy StatekGracz
	*/
	StatekGracz();
	/** Destruktor klasy StatekGracz
	*/
	~StatekGracz();
	/** Metoda zwracajaca pole spirte
	*/
	sf::Sprite& getSprite();
	/** Metoda odpowiadajaca za poruszanie sie i strzelanie gracza po nacisnieciu odpowiednich przyciskow na klawiaturze
	*/
	virtual void akcja();
	/** Metoda rysujaca na ekranie spirte Gracza i wystrzelone przez niego pociski. Przy okazji sprawdza czy dany pocisk nie trafil czegos, jesli tak to pocisk jest usuniety
	* @param en obiekt klasy FlotaObcych, sprawdzamy czy nie traflilismy w jakiegos wroga pociskiem
	* @param o vector Oslon, sprawdzamy czy nie trafilismy jakiejs oslony 
	* @param ufos sprawdzamy czy nie trafilismy StatkuUFO
	*/
	void draw_pocisk(FlotaObcych& en, std::vector<Oslona>& o, std::vector<StatekUFO>& ufos);
	/** Metoda sprawdzajaca czy StatekGracza nie zostal trafiony jakims pociskiem i jesli tak to zmienia jego teksture
	* @param p Pocisk dla ktorego sprawdzamy czy tafil gracza
	*/
	virtual bool check_death(Pocisk& p);
	/** Metoda zwracajaca liczbe punktow jaka uzyskal gracz jako string
	*/
	std::string getPoints();
	/** Metoda sprawdzajaca czy gracz nie ma juz zyc
	*/
	bool isLifeEmpty();
	/** Metoda odradzajaca gracza
	*/
	void respawn();
};