/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Config.cpp
*/
#include "Config/Config.hpp"

Config::Config(string path) {
    this->path = path;
    this->load(path);
}

Config::~Config() {
}


void Config::load(const std::string& file) {
    libconfig::Config cfg;

    // Read the file. If there is an error, report it and exit.
    try {
        cfg.readFile(file.c_str());
    }
    catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    catch(const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return;
    }

    // Get the GUI configuration
    const libconfig::Setting& gui = cfg.lookup("GUI");
    guiConfig.load(gui);

    // Get the player configuration
    const libconfig::Setting& player = cfg.lookup("player");
    playerConfig.load(player);
}

void Config::print() {
    std::cout << "GUI:" << std::endl;
    guiConfig.print();
    std::cout << "Player:" << std::endl;
    playerConfig.print();
}