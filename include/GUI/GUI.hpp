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

class Core;



class GUI {
	public:
		GUI();
		~GUI();
        void load(const GUIConfig& config);
        void loadBeatmapPanel(Database& database);
        void loadingScreenCreate();
        void updateLoadingScreen(int pourcent);
        void createMenu(Database& database);
        void updateMenu();
        void loop(int state);
        void createGame();
        void updateGame();
        void drawGame();
        void setActive(bool active) {
            window.setActive(active);
        }
        sf::RenderWindow& getWindow() {
            return window;
        }
        sf::Event& getEvent() {
            return event;
        }

protected:
        sf::RenderWindow window;
        sf::Event event;
        sf::Vector2i mousePos;
        sf::Vector2f mousePosF;
        LoadingScreen loadingScreen;

private:
};

#endif /*GUI_HPP_*/