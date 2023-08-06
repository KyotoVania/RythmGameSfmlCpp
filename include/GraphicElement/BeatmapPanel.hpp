// beatmappannel.hpp
#ifndef BEATMAPPANNEL_HPP_
#define BEATMAPPANNEL_HPP_

#include <functional>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <utility>
#include "Beatmap/Beatmap.hpp"

class BeatmapPanel {
public:
    BeatmapPanel();
    BeatmapPanel(const sf::Texture& texturePannel, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, std::string Grade, sf::Font fonts);
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
    sf::Vector2f position;
    sf::Vector2f size;
    int textSize;
    sf::Font _font;
};
#endif /*BEATMAPPANNEL_HPP_*/
