/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** LoadingScreen.cpp
*/

#include "GraphicElement/LoadingScreen.hpp"

LoadingScreen::LoadingScreen() {
}

LoadingScreen::~LoadingScreen() {
}

void LoadingScreen::load(std::pair<int, int> res) {
    // Load the texture
    if (!texture.loadFromFile("Resources/UI/Arrows03.png")) {
        // Handle error...
        std::cout << "Error loading Arrows03.png" << std::endl;

    }
    sprite.setTexture(texture);
    sprite.setPosition((res.first * 70 /100), (res.second * 70 / 100));

    // Load the font
    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        std::cout << "Error loading sansation.ttf" << std::endl;
        // Handle error...
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition((res.first * 70 /100 + ARROW_03_SIZE_X/2), (res.second * 70 / 100 + ARROW_03_SIZE_Y/2));
}

void LoadingScreen::update(int percent) {
    // Update the text
    text.setString(std::to_string(percent) + "%");
}

void LoadingScreen::draw(sf::RenderWindow& window) {
    // Draw the sprite and the text
    window.draw(sprite);
    window.draw(text);
}
