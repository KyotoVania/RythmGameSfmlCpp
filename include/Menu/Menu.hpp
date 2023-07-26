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
using namespace std;
#include "GraphicElement/RectangleButton.hpp"
//#include "GraphicElement/TriangleButton.hpp"
//TODO: BANNER



class Menu {
public:
Menu();
~Menu();

protected:
    vector<map<string, pair<Button *, std::function<void(int)>>>> buttons;
    vector<map<string, sf::Text>> texts;
    vector<map<string, sf::Texture>> textures;
    vector<map<string, sf::Sprite>> sprites;
    int theme = 0;
private:
};

#endif /*MENU_HPP_*/