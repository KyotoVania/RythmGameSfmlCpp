/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Core.hpp
*/
#ifndef CORE_HPP_
	#define CORE_HPP_

#include <SFML/Graphics.hpp>
#include "Menu/Menu.hpp"
#include "GUI/GUI.hpp"
#include "Config/Config.hpp"
#include "Database/Database.hpp"
#include "Visualizer/Vizualizer.hpp"
#include "Visualizer/FFT.hpp"
#include "Visualizer/FFT_Menu.hpp"
#include "Visualizer/FFT_Game.hpp"
#include "Menu/Menu.hpp"
#include "Game/Game.hpp"
#include <iostream>
#include <future>
#include <thread>

using namespace std;

//class GUI;
enum GameState {
    MENU,
    GAME,
    WELCOMEMENU,
    EXIT,
    ENDT
};
class Core {
public:
    Core();
    ~Core();
    void run();
    void analyzeBeatmap(const std::string& beatmapPath);
    void updateState(sf::Event event);
    void drawState();
    void transition();
private:
    void loadConfigAndDatabase();
    void applyConfig();
    Config config;
    GUI gui;
    Menu menu;
    Database database;
    Vizualizer visualizer;
    FFT_Game fft;
    Game game;
    /*we will use a truple logic of gamestates
    the first bool will be used to know if the transition is done
    the first gamestate is the previous gamestate
    the second is the current gamestate
    the third is the next gamestate
    */
     std::tuple<bool, GameState, GameState, GameState> gameStates;
};


#endif /*CORE_HPP_*/