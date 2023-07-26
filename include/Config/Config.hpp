/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Config.hpp
*/
#ifndef CONFIG_HPP_
	#define CONFIG_HPP_
#include <string>
#include <map>
#include <libconfig.h++>
#include <iostream>
#include "Player/PlayerConfig.hpp"
#include "GUI/GUIConfig.hpp"
#include "Beatmap/BeatmapConfig.hpp"
using namespace std;

class Config {
public:
    Config(string file);
    ~Config();
    void load(const std::string& file);
    void save(const std::string& file);
    void print();
private:
    // Static members to store the configuration values
    string path;
    PlayerConfig playerConfig;
    GUIConfig guiConfig;
};

#endif /*CONFIG_HPP_*/

