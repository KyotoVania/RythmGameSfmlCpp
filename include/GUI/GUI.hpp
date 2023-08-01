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
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "GUI/GUIConfig.hpp"
#include "GraphicElement/LoadingScreen.hpp"
#include "Database/Database.hpp"
#include "Menu/Menu.hpp"

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
        void load(const GUIConfig& config);
        void loadBeatmapPanel(Database& database);
        void loadingScreenCreate();
        void updateLoadingScreen(int pourcent);
        void createMenu();
        void updateMenu();
        void loop();
protected:
        sf::RenderWindow window;
        sf::Event event;
        sf::Vector2i mousePos;
        sf::Vector2f mousePosF;
        int gameState = MAIN_MENU;
        Menu menu;
        LoadingScreen loadingScreen;

private:
};

#endif /*GUI_HPP_*/