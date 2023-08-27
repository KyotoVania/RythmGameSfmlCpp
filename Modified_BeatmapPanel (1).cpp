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

BeatmapPanel::BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureArrowLeft, const sf::Texture& textureArrowRight, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, const BeatmapConfig& beatmapConfig, const sf::Font& fonts) {
    // Normalize the position
    float normalizedX = std::fmod(position.x, 10.0f) / 10.0f;
    float normalizedY = std::fmod(position.y, 10.0f) / 10.0f;

    // Calculate the screen position
    float screenX = normalizedX * res.first - texturePanel.getSize().x / 2;
    float screenY = normalizedY * res.second - texturePanel.getSize().y / 2;


    std::cout << "Creating panel position : " << screenX << " " << screenY << std::endl;
    std::cout << "position are set to : " << position.x << " " << position.y << std::endl;
    this->position = sf::Vector2f(screenX, screenY);
    // Assuming the cover is a smaller sprite displayed on the panel
    //check if the cover is not empty
    if (textureCover.getSize().x == 0 || textureCover.getSize().y == 0)
        std::cout << "Cover is empty" << std::endl;
    sprites["cover"].setTexture(textureCover);
    coverSprite.setPosition(position); // Adjust this as needed
    std::cout << "Creating grade text" << std::endl;
    // Assuming grade is a text displayed on the panel
    //load font "Resources/Fonts/sansation.ttf"
    textSize = 35;
    // Calculate the starting position for the text based on the cover's right edge
    float textStartX = coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + 10; // 10 is a margin, adjust as needed
    float textStartY = coverSprite.getPosition().y;

    // Set up the text elements
    texts["title"].setFont(fonts);
    texts["title"].setCharacterSize(20); // Adjust as needed
    texts["title"].setString("Title : " + beatmapConfig.getName());
    texts["title"].setPosition(textStartX, textStartY);

    texts["artist"].setFont(fonts);
    texts["artist"].setCharacterSize(20); // Adjust as needed
    texts["artist"].setString("Artist : " + beatmapConfig.getArtist());
    texts["artist"].setPosition(textStartX, textStartY + texts["title"].getGlobalBounds().height + 5); // 5 is spacing between texts

    texts["difficulty"].setFont(fonts);
    texts["difficulty"].setCharacterSize(20); // Adjust as needed
    texts["difficulty"].setString("Difficulty : " + std::to_string(beatmapConfig.getDifficulty()));
    texts["difficulty"].setPosition(textStartX, texts["artist"].getPosition().y + texts["artist"].getGlobalBounds().height + 5);

    texts["grade"].setFont(fonts);
    texts["grade"].setCharacterSize(20); // Adjust as needed
    texts["grade"].setString("Grade : S");
    texts["grade"].setPosition(textStartX, texts["difficulty"].getPosition().y + texts["difficulty"].getGlobalBounds().height + 5);

}

BeatmapPanel::~BeatmapPanel(){

}

void BeatmapPanel::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(coverSprite);
    window.draw(titleText);
    window.draw(artistText);
    window.draw(difficultyText);
    window.draw(gradeText);
   //      std::cout << "Drawing panel" << std::endl;
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
    //std::cout << "PercentX : " << PercentX << " PercentY : " << PercentY << std::endl;
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
    titleText.setCharacterSize(textSize * scale);
    artistText.setCharacterSize(textSize * scale);
    difficultyText.setCharacterSize(textSize * scale);
    titleText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, coverSprite.getPosition().y);
    artistText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, titleText.getPosition().y + PercentY * 3);
    difficultyText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, artistText.getPosition().y + PercentY * 3);
    gradeText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, difficultyText.getPosition().y + PercentY * 3);
    //difficultyText.setPosition(artistText.getPosition().x, artistText.getPosition().y + artistText.getGlobalBounds().height + 5);
    //gradeText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + 10, coverSprite.getPosition().y + coverSprite.getGlobalBounds().height - gradeText.getGlobalBounds().height);
}

void BeatmapPanel::draw(sf::RenderWindow& window) {
    // Draw sprites
    for (auto& [key, sprite] : sprites) {
        window.draw(sprite);
    }

    // Draw texts
    for (auto& [key, text] : texts) {
        window.draw(text);
    }
}

void BeatmapPanel::setText(const std::string& text, const sf::Font& font, unsigned int characterSize) {
    texts["title"].setString(text);
    texts["title"].setFont(font);
    texts["title"].setCharacterSize(characterSize);
}