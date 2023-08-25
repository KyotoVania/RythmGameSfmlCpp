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
#include <iostream>
#include <future>
#include <thread>

using namespace std;

//class GUI;
enum GameState {
    MENU,
    GAME,
    WELCOMEMENU,
    EXIT
};
class Core {
public:
    Core();
    ~Core();
    void run();
    void analyzeBeatmap(const std::string& beatmapPath);

private:
    void loadConfigAndDatabase();
    void applyConfig();
    Config config;
    GUI gui;
    Database database;
    Vizualizer visualizer;
    WithFFT withFFT;
    std::tuple<bool, GameState, GameState> gameStates;
};


#endif /*CORE_HPP_*/