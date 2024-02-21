#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <random>
#include <string>
#include <ranges>
#include <filesystem>
#include <regex>
#include <fstream>

/** Klasa ktora odpowiada za najwazniejsze funkcje programu takie jak inicjalizacja okna jak i sama logike gry
*/
class Game {
protected:
	static sf::RenderWindow window;
	static std::string highscore_str;
	const static int SCREEN_WIDTH = 640;
	const static int SCREEN_HEIGHT = 720;
public:
	/** Metoda inicjalizuje okno i wysiwetla ekran startowy
	*/
	static void start();
	/** Glowna petla gry. Na poczatku inicjalizuje wszystkie potrzebne obiekty, a nastepnie w kolejnych iteracjach petli while aktualizuje i wyswietla na ekranie wszytskie obiekty z uzyciem potrzebnych metod
	*/
	static void gameLoop();
	/** Metoda ktora zamyka okno
	*/
	static void closewindow();
	/** Metoda wywolywana kiedy gra sie konczy, wyswietla ekran koncowy i ostateczny wynik 
	* @param score uzyskany przez gracza wynik w postaci stringa
	*/
	static void end(std::string score);
};

class StatekGracz;

class Pocisk;

class Bloczek;

class Oslona;

class StatekUFO;

class StatekObcy;

class ObcyWersjaA;

class ObcyWersjaB;

class ObcyWersjaC;

class FlotaObcych;

class CzyObcyStrzela;

class Plansza;

/** Funkcja inicjalizujaca obiekty klasy sf::Text
* @param text inicjalizowany Text
* @param font font jakiego chcemy uzyc dla naszego tekstu
* @param x wspolrzedna x-owa
* @param y wspolrzedna y-owa
* @param caption napis jaki chcemy by nasz text wyswietlil
*/
void init_text(sf::Text& text, sf::Font& font, float x, float y, std::string caption);

/** Funkcja sluzaca do odczytania z pliku najwyzszego wyniku
*/
std::string readHighScore();

/** Funkcja sluzaca do zapisu najwyzszego wyniku do pliku 
* @param player gracz ktorego punkty porownamy z highscore
* @param highscore_str najwyzszy wynik zapisany w strigu
*/
void saveHighScore(StatekGracz& player, std::string& highscore_str);