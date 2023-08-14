// beatmappannel.hpp
#ifndef BEATMAPPANNEL_HPP_
#define BEATMAPPANNEL_HPP_

#include <functional>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <utility>
#include "Beatmap/Beatmap.hpp"
#include "Database/Database.hpp"
class BeatmapPanel {
public:
    BeatmapPanel();
    BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, const BeatmapConfig& beatmapConfig, const sf::Font& fonts);
    ~BeatmapPanel();
    void draw(sf::RenderWindow& window);
    void setText(const std::string& text, const sf::Font& font, unsigned int characterSize);
    void adjust(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
    void adjustPanel(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
    void adjustCover(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
    void adjustGrade(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture textureCover;
    sf::Sprite coverSprite;
    sf::Text gradeText;
    sf::Text titleText;
    sf::Text artistText;
    sf::Text difficultyText;
    sf::Vector2f position;
    sf::Vector2f size;
    int textSize;
    sf::Font _font;
    Button leftArrowButton;
    Button rightArrowButton;
    int currentDifficulty;  // Represents the current difficulty level
    void handleButtonClick(const sf::Vector2f& mousePosition);
};

#endif /*BEATMAPPANNEL_HPP_*/
#endif /*BEATMAPPANNEL_HPP_*/
