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
    BeatmapPanel(const sf::Texture& texturePannel, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, std::string Grade );
    ~BeatmapPanel();
    void draw(sf::RenderWindow& window);
    void setText(const std::string& text, const sf::Font& font, unsigned int characterSize);
    void adjust(float scale, float opacity, const sf::Vector2f& offset);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Texture textureCover;
    sf::Sprite coverSprite;
    sf::Text gradeText;
    sf::Vector2f position;
    sf::Vector2f size;
};
#endif /*BEATMAPPANNEL_HPP_*/
