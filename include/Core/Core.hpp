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
#include <iostream>
#include <future>
#include <thread>

using namespace std;



class Core {
public:
    Core();
    ~Core();
    void run();

private:
    void loadConfigAndDatabase();
    void applyConfig();
    Config config;
    GUI gui;
    Database database;
    std::tuple<bool, GameState, GameState> gameStates;
};


#endif /*CORE_HPP_*/