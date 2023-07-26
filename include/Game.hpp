#ifndef GAME_HPP
#define GAME_HPP
/*
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <complex>
#include <valarray>
#include "Player.hpp"
#include "Space.hpp"
#include "Visualizer/Vizualizer.hpp"
#include "Visualizer/FFT.hpp"
#include "Menu/Menu.hpp"

enum WINORLOSE
{
	INGAME,
	WIN,
	LOOSE,
	INMENU
};
	

class Game
{
public:
    sf::Clock colorChangeClock;
    Game(char **argv, int argc);
    void run();
	void checkMenuButton(sf::Event& event);
	void checkBackButton(sf::Event& event);
	void handleCollision();
private:

    sf::RenderWindow window;

    std::string active_song = "Stage1.wav";

    std::string active_mode = "Space";
    void initialize_mode(const std::string& mode_name, const std::string& song_name);
    void initialize_player();
    std::unique_ptr<Vizualizer> vizualizer;
    std::unique_ptr<Player> player;
	int score = 0;
	std::map<int, std::string> grades;
	std::string getGradeFromScore(int score);
	float invincibilityTime = 1.5f; // The length of the invincibility period in seconds
	float invincibilityTimer = 0.0f; // The current state of the timer
	int WinOrLoss = INMENU;
	sf::RectangleShape healthBar;
	float health = 1000.0f;
	const float maxHealth = 1000.0f;
    bool is_menu_active = true;
	void getMovements();
	sf::Clock clock;
	sf::Time frameTime;
    sf::Font font;
    Menu menu;
    sf::Text scoreText;
};

*/

#endif // GAME_HPP
