/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** GUI.hpp
*/
#ifndef GUI_HPP_
	#define GUI_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum gameState {
    MAIN_MENU,
    SETTINGS,
    GAME,
    PAUSE,
    GAME_OVER,
    CREDITS,
    EXIT
};
class GUI {
	public:
		GUI();
		~GUI();
	protected:
        sf::RenderWindow window;
        sf::Event event;
        sf::Vector2i mousePos;
        sf::Vector2f mousePosF;
        int gameState = MAIN_MENU;
    private:
};

#endif /*GUI_HPP_*/