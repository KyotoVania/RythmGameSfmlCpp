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

void GUI::createMenu(Database& database)
{
    //this function will create the menu
    //create a pair of int for the resolution
    pair<int, int> res;
    res.first = window.getSize().x;
    res.second = window.getSize().y;
    menu.load(res, database);
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
void GUI::updateState(int state, sf::Event event)
{
    if (state == MENU){
        menu.update(event, window);
    } else if (state == GAME){
        //game.update(event, window);
    }
}

void GUI::drawState(int state)
{
    if (state == MENU){
        menu.draw(window);
    } else if (state == GAME){
        //game.draw(window);
    }
}

void GUI::loop(int state)
{
    //for the moment only call the menu update
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || state == EXIT)
                window.close();
            else
                updateState(state, event);
        }
        window.clear();
        drawState(state);
        window.display();
    }
}
