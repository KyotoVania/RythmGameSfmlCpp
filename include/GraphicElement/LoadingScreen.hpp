/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** LoadingScreen.hpp
*/
#ifndef LOADINGSCREEN_HPP_
	#define LOADINGSCREEN_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#define ARROW_03_SIZE_X 197
#define ARROW_03_SIZE_Y 75

class LoadingScreen {
public:
    LoadingScreen();
    ~LoadingScreen();

    void load(std::pair<int, int> res);
    void update(int percent);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text text;
};

#endif /*LOADINGSCREEN_HPP_*/