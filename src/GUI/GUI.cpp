/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** GUI.cpp
*/

#include "GUI/GUI.hpp"

GUI::GUI() {

}

GUI::~GUI() {

}

void GUI::load(const GUIConfig& config)
{
    sf::VideoMode videoMode(config.getResolution().first, config.getResolution().second);
    window.create(videoMode, config.getTitle());
    window.setFramerateLimit(config.getFPS());
    //event
    event = sf::Event();
    //mouse
    mousePos = sf::Vector2i(0, 0);
    mousePosF = sf::Vector2f(0, 0);

}

void GUI::loadingScreenCreate() {
    //this function will create the loading screen
    //create a pair of int for the resolution
    pair<int, int> res;
    res.first = window.getSize().x;
    res.second = window.getSize().y;
    loadingScreen.load(res);
}

void GUI::updateLoadingScreen(int percent) {
    loadingScreen.update(percent);
    window.clear();
    loadingScreen.draw(window);
    window.display();
}

void GUI::loadBeatmapPanel(Database& database)
{
    //this function will create the beatmap panel
    menu.loadBeatmaps(database);
}

void GUI::createMenu()
{
    //this function will create the menu
    //create a pair of int for the resolution
    pair<int, int> res;
    res.first = window.getSize().x;
    res.second = window.getSize().y;
    menu.load(res);
}

void GUI::updateMenu()
{
    //this function will update the menu
    //update the mouse position
    mousePos = sf::Mouse::getPosition(window);
    mousePosF = sf::Vector2f(mousePos.x, mousePos.y);
    //update the menu
    menu.update(event, window);
    window.clear();
    menu.draw(window);
    window.display();
}

void GUI::loop()
{
    //for the moment only call the menu update
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else
                menu.update(event, window);
        }
        window.clear();
        menu.draw(window);
        window.display();
    }
}
