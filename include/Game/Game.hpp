/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** Game.hpp
*/
#ifndef GAME_HPP_
	#define GAME_HPP_
#include "Entity/Planet.hpp"
#include "Visualizer/FFT_Game.hpp"
#include <SFML/Graphics.hpp>


class Game {
	public:
		Game();
		~Game();
        void loadTextures();
        void loadTexts();
        void loadSprites();
        void loadEntities();
        void setDifficulty(int difficulty);
        void draw(sf::RenderWindow& window);
//        void update(const sf::Event& event, const sf::RenderWindow& window);
    void update();
	protected:
    //for the moment we will only try to show 3 different projectiles we made, so we will create 3 different pool of projectiles
    //we will have to create a pool of projectiles for each planet for the moement we will only create 1 of each in the constructor
    std::map<std::string, std::vector<PlanetProjectile *>> projectilePools;
    map<string, sf::Text> texts;
    map<string, sf::Texture> textures;
    map<string, sf::Sprite> sprites;
    map<string, sf::Font> fonts;
    pair<int, int> _res = {0, 0};
    int score = 0;
    int difficulty = 0;
    FFT_Game fft;
private:
};

#endif /*GAME_HPP_*/