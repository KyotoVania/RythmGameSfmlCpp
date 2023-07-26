/*
** EPITECH PROJECT, 2023
** newtry
** File description:
** PlayerConfig.hpp
*/
#ifndef PLAYERCONFIG_HPP_
	#define PLAYERCONFIG_HPP_
#include "PlayerIngame.hpp"
#include <libconfig.h++>
#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <string>
#include <iostream>
using namespace std;
class PlayerConfig {
	public:
		PlayerConfig();
		~PlayerConfig();
        void setId(int id);
        void setName(string name);
        void setAccuracy(int accuracy);
        sf::Keyboard::Key stringToKey(const std::string& key);
        void setKeyBindings(map<string, sf::Keyboard::Key> keyBindings);
        int getId();
        string getName();
        int getAccuracy();
        map<string, sf::Keyboard::Key> getKeyBindings();
        void load(const libconfig::Setting& playerSetting);
        void save(const libconfig::Setting& playerSetting);
        void print();
	protected:
	int Id;
    string Name;
    int Accuracy;
    map<string, sf::Keyboard::Key> keyBindings;
    //TODO:
    //do score map beatmap
private:
};

#endif /*PLAYERCONFIG_HPP_*/