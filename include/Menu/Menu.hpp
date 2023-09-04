/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Menu.hpp
*/
#ifndef MENU_HPP_
	#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <string>
//create a global map to associate a int with a note with is a string
#include <vector>
#include <tuple>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
#include "GraphicElement/Button.hpp"
#include "Database/Database.hpp"
#include "GraphicElement/BeatmapPanel.hpp"
#include "Visualizer/FFT.hpp"
#include "Visualizer/FFT_Menu.hpp"
//#include "GraphicElement/TriangleButton.hpp"
//TODO: BANNER
enum MenuState {
    SONGSELECT,
    PLAYWAITING,
    BACKWAITING
};

class Menu {
public:
    Menu();
    ~Menu();
    void load(const std::pair<int, int>& res, Database& database);
    void loadTextures(Database& database);
    int update(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void loadBeatmaps(Database& database);
    void slideLeft();
    void slideRight();
    void onAnalyzeButtonClicked(const std::string& beatmapPath);
    int getDifficulty();
    std::string getActualSongName();
    void setDifficulty(int difficulty);
protected:
    int selectedPanelIndex = 0; // Add this line
    map<string, Button> buttons;
    map<string, ButtonConfig> buttonConfigs;
    map<string, sf::Text> texts;
    map<string, sf::Texture> textures;
    map<string, sf::Sprite> sprites;
    //add the beatmap panel
    std::vector<std::unique_ptr<BeatmapPanel>> beatmapPanel;
    map<string, sf::Font> fonts;
    int state = SONGSELECT;
    pair<int, int> _res = {0, 0};
    int theme = 0;
    //add the fft
    FFT_Menu fft;
private:
};

#endif /*MENU_HPP_*/