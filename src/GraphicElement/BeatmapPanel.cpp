/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** beatmappanell.cpp
*/

#include "GraphicElement/BeatmapPanel.hpp"

BeatmapPanel::BeatmapPanel(){

}

BeatmapPanel::BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, std::string Grade)
{
    sprite.setTexture(texturePanel);
    sprite.setPosition(position);

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
    window.draw(coverSprite);
    window.draw(gradeText);
       std::cout << "Drawing panel" << std::endl;
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

void BeatmapPanel::adjust(float scale, float opacity, const sf::Vector2f& offset) {
    std::cout << "Adjusting panel" << std::endl;
    sprite.setScale(scale, scale);
    sprite.setColor(sf::Color(255, 255, 255, opacity));
    sprite.setPosition(position + offset);

    // Adjust the cover and text as well
    coverSprite.setScale(scale, scale);
    coverSprite.setColor(sf::Color(255, 255, 255, opacity));
    coverSprite.setPosition(position + offset);

    gradeText.setCharacterSize(gradeText.getCharacterSize() * scale);
    gradeText.setPosition(position + offset);
}