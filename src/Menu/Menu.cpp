/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Menu.cpp
*/

#include "Menu/Menu.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{
}

// Menu.cpp
void Menu::load(const std::pair<int, int>& res)
{
    // Load the background image
    sf::Texture& backgroundTexture = textures["background"];
    if (!backgroundTexture.loadFromFile("Resources/UI/Background.jpg")) {
        // Handle error...
    }
    sf::Sprite background(backgroundTexture);
    sprites["background"] = background;

    // Load the font
    sf::Font& font = fonts["sansation"];
    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        // Handle error...
    }

    // Load the buttons
    for (int i = 1; i <= 6; ++i) {
        std::string texturePath = "Resources/UI/Btn0" + std::to_string(i) + ".png";
        sf::Texture& buttonTexture = textures["button" + std::to_string(i)];
        if (!buttonTexture.loadFromFile(texturePath)) {
            // Handle error...
        }
        std::string buttonName = "button" + std::to_string(i);
        buttons.emplace(buttonName, Button(buttonTexture, sf::Vector2f(10 + i * 10, 80), [buttonName](){
            std::cout << "Button " << buttonName << " clicked!" << std::endl;
        }, res));
        buttons[buttonName].setText(std::to_string(i), font, 30); // You need to load the font somewhere before this
    }
}





void Menu::update(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& button : buttons) {
        button.second.handleEvent(event, window);
    }
}


void Menu::draw(sf::RenderWindow& window)
{
    window.draw(sprites["background"]);
    for (auto& button : buttons) {
        button.second.draw(window);
    }
}