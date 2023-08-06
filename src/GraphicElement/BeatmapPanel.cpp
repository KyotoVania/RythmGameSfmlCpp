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

BeatmapPanel::BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, std::string Grade, sf::Font fonts)
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
    _font = sf::Font(fonts);
    gradeText.setFont(_font);
    std::cout << "Creating grade text" << std::endl;
    // Assuming grade is a text displayed on the panel
    //load font "Resources/Fonts/sansation.ttf"
    textSize = 250;
    gradeText.setCharacterSize(textSize); // Adjust this as needed
    gradeText.setString("S");
    gradeText.setPosition(0, 0); // Adjust this as needed
        // Don't forget to set the font and character size for the text
    std::cout << "Creating grade text" << std::endl;
}

BeatmapPanel::~BeatmapPanel(){

}

void BeatmapPanel::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(coverSprite);
    gradeText.setFont(_font);
    window.draw(gradeText);
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

void BeatmapPanel::adjustPanel(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {

}

void BeatmapPanel::adjustCover(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {
}
void BeatmapPanel::adjustGrade(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {
}
void BeatmapPanel::adjust(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {
    //we need to split the res by 10 to get the real resolution
    float screenOffsetX = std::fmod(offset.x, 10.0f) / 10.0f * res.first;
    float screenOffsetY = std::fmod(offset.y, 10.0f) / 10.0f * res.second;
    float PercentX = res.first / 100.0f;
    float PercentY = res.second / 100.0f;
    std::cout << "PercentX : " << PercentX << " PercentY : " << PercentY << std::endl;
    // Adjust the panel
    sprite.setScale(scale, scale);
    sprite.setColor(sf::Color(255, 255, 255, opacity));
    screenOffsetX = screenOffsetX - (sprite.getTexture()->getSize().x * scale) / 2;
    screenOffsetY = screenOffsetY - (sprite.getTexture()->getSize().y * scale) / 2;
    sprite.setPosition(screenOffsetX, screenOffsetY); // Also set the position to the screen offset
    // Adjust the cover and text as well
    coverSprite.setScale(scale, scale);
    coverSprite.setColor(sf::Color(255, 255, 255, opacity));
    coverSprite.setPosition(screenOffsetX + PercentX * 5, screenOffsetY + PercentY * 5); // Also set the position to the screen offset
    gradeText.setCharacterSize(textSize * scale);
    gradeText.setPosition(screenOffsetX + PercentX * 15, screenOffsetY + PercentY * 10); // Also set the position to the screen offset
}
