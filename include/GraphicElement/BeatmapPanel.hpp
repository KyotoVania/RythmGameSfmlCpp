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
#include "GraphicElement/Button.hpp"
class BeatmapPanel {
public:
    BeatmapPanel();
    BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureArrowLeft, const sf::Texture& textureArrowRight,
                 const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, const BeatmapConfig& beatmapConfig, const sf::Font& fonts);
    ~BeatmapPanel();
    void draw(sf::RenderWindow& window);
    void setText(const std::string& text, const sf::Font& font, unsigned int characterSize);
    void adjust(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
    void adjustPanel(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
    void adjustCover(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
    void adjustGrade(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res);
    void adjustDifficulty(int difficulty);
    int getDifficultyUser() {
        return difficultyUser;
    }
    std::string getBeatmapName() {
        std::string name = texts["title"].getString();
        name.erase(0, 8);
        return name;
    }
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    //void adjustDifficultyUserPlus();
private:
    sf::Texture texture;
    std::map<std::string, sf::Sprite> sprites; // Replace individual sprites with a map
    std::map<string, Button> buttons;
    map<string, ButtonConfig> buttonConfigs;
    //sf::Texture textureCover;
    std::map<std::string, sf::Text> texts; // Map for text elements
    int difficultyUser;
    sf::Vector2f position;
    sf::Vector2f size;
    int textSize;
    sf::Font _font;
};
#endif /*BEATMAPPANNEL_HPP_*/
