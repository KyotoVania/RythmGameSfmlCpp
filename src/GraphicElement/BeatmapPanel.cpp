/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** beatmappanell.cpp
*/

#include "GraphicElement/BeatmapPanel.hpp"
#include <cmath>


BeatmapPanel::BeatmapPanel(){

}

BeatmapPanel::BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, std::string Grade)
{
    // Normalize the position
    float normalizedX = std::fmod(position.x, 10.0f) / 10.0f;
    float normalizedY = std::fmod(position.y, 10.0f) / 10.0f;

    // Calculate the screen position
    float screenX = normalizedX * res.first - texturePanel.getSize().x / 2;
    float screenY = normalizedY * res.second - texturePanel.getSize().y / 2;

    sprite.setTexture(texturePanel);
    sprite.setPosition(screenX, screenY);
    std::cout << "Creating panel position : " << screenX << " " << screenY << std::endl;
    std::cout << "position are set to : " << position.x << " " << position.y << std::endl;
    this->position = sf::Vector2f(screenX, screenY);
    // Assuming the cover is a smaller sprite displayed on the panel
    coverSprite.setTexture(textureCover);
    coverSprite.setPosition(position); // Adjust this as needed

    // Assuming grade is a text displayed on the panel
    gradeText.setString(Grade);
    gradeText.setPosition(position); // Adjust this as needed
    // Don't forget to set the font and character size for the text
}

BeatmapPanel::~BeatmapPanel(){

}

void BeatmapPanel::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    //window.draw(coverSprite);
   // window.draw(gradeText);
    //       std::cout << "Drawing panel" << std::endl;
}

void BeatmapPanel::setText(const std::string& text, const sf::Font& font, unsigned int characterSize) {
    gradeText.setString(text);
    gradeText.setFont(font);
    gradeText.setCharacterSize(characterSize);
    // Center the text in the button
    sf::FloatRect textRect = gradeText.getLocalBounds();
    gradeText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    gradeText.setPosition(sf::Vector2f(position.x + size.x/2.0f, position.y + size.y/2.0f));
}

void BeatmapPanel::adjust(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {
    float normalizedOffsetX = std::fmod(offset.x, 10.0f) / 10.0f;
    float normalizedOffsetY = std::fmod(offset.y, 10.0f) / 10.0f;

    // Calculate the screen offset
    float screenOffsetX = normalizedOffsetX * res.first;
    float screenOffsetY = normalizedOffsetY * res.second;

    std::cout << "Adjusting panel" << std::endl;
    sprite.setScale(scale, scale);
    sprite.setColor(sf::Color(255, 255, 255, opacity));
    std::cout << "position was : " << position.x << " " << position.y << std::endl;
    std::cout << "offset was : " << offset.x << " " << offset.y << std::endl;
    sprite.setPosition(screenOffsetX, screenOffsetY); // Set the position to the screen offset, not the current position
    std::cout << "position is now : " << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;

    // Adjust the cover and text as well
    coverSprite.setScale(scale, scale);
    coverSprite.setColor(sf::Color(255, 255, 255, opacity));
    coverSprite.setPosition(screenOffsetX, screenOffsetY); // Also set the position to the screen offset

    gradeText.setCharacterSize(gradeText.getCharacterSize() * scale);
    gradeText.setPosition(screenOffsetX, screenOffsetY); // Also set the position to the screen offset
}
