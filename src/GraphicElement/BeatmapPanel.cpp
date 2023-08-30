/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** beatmappanell.cpp
*/

#include "GraphicElement/BeatmapPanel.hpp"
#include "global.hpp"
#include <cmath>

void adjustDifficultyUserMinus(int * difficultyUser, sf::Text * textDifficultyUser);
void adjustDifficultyUserPlus(int * difficultyUser, sf::Text * textDifficultyUser);
BeatmapPanel::BeatmapPanel(){

}

BeatmapPanel::BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureArrowLeft, const sf::Texture& textureArrowRight, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, const BeatmapConfig& beatmapConfig, const sf::Font& fonts) {
    // Normalize the position
    float normalizedX = std::fmod(position.x, 10.0f) / 10.0f;
    float normalizedY = std::fmod(position.y, 10.0f) / 10.0f;
    this->difficultyUser = 0;

    // Calculate the screen position
    float screenX = normalizedX * res.first - texturePanel.getSize().x / 2;
    float screenY = normalizedY * res.second - texturePanel.getSize().y / 2;

    // Assuming grade is a text displayed on the panel
    //load font "Resources/Fonts/sansation.ttf"
    textSize = 35;
    // Calculate the starting position for the text based on the cover's right edge
    float textStartX = sprites["cover"].getPosition().x + sprites["cover"].getGlobalBounds().width + 10; // 10 is a margin, adjust as needed
    float textStartY = sprites["cover"].getPosition().y;
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

    texts["difficulty_user"].setFont(fonts);
    texts["difficulty_user"].setCharacterSize(20); // Adjust as needed
    std::string stringDifficultyUser = std::to_string(this->difficultyUser);
    std::cout << "DifficultyUser init : " << difficultyUser << std::endl;
    std::cout << "adress of difficultyUser : " << &difficultyUser << std::endl;
    texts["difficulty_user"].setString("Difficulty selected : " + stringDifficultyUser);
    texts["difficulty_user"].setPosition(textStartX, texts["difficulty"].getPosition().y + texts["artist"].getGlobalBounds().height + 5);


    texts["grade"].setFont(fonts);
    texts["grade"].setCharacterSize(20); // Adjust as needed
    texts["grade"].setString("Grade : S");
    texts["grade"].setPosition(textStartX, texts["difficulty_user"].getPosition().y + texts["difficulty"].getGlobalBounds().height + 5);
    sprites["panel"].setTexture(texturePanel);
    sprites["panel"].setPosition(screenX, screenY);

    buttonConfigs["ArrowLeft"] = {"ArrowLeft", [this](){ adjustDifficultyUserMinus(&this->difficultyUser, &this->texts["difficulty_user"]);}};
    buttonConfigs["ArrowRight"] ={"ArrowRight", [this](){ adjustDifficultyUserPlus(&this->difficultyUser, &this->texts["difficulty_user"]);}};

    std::cout << "Creating panel position : " << screenX << " " << screenY << std::endl;
    std::cout << "position are set to : " << position.x << " " << position.y << std::endl;
    this->position = sf::Vector2f(screenX, screenY);
    // Assuming the cover is a smaller sprite displayed on the panel
    //check if the cover is not empty
    if (textureCover.getSize().x == 0 || textureCover.getSize().y == 0)
        std::cout << "Cover is empty" << std::endl;
    sprites["cover"].setTexture(textureCover);
    sprites["cover"].setPosition(position); // Adjust this as needed
    //button
    float arrowLeftX = 50;
    float arrowLeftY = 50;
    //std::pair<int, int> fakeRes = std::make_pair(sprites["panel"].getGlobalBounds().width, sprites["panel"].getGlobalBounds().height);
    buttons.emplace("ArrowLeft", Button(textureArrowLeft, sf::Vector2f(arrowLeftX, arrowLeftY), buttonConfigs["ArrowLeft"].onClick, HARDRES));
    buttons["ArrowLeft"].setText("", fonts, 20);
    buttons.emplace("ArrowRight", Button(textureArrowRight, sf::Vector2f(arrowLeftX + sprites["arrowLeft"].getGlobalBounds().width + 10, arrowLeftY), buttonConfigs["ArrowRight"].onClick, HARDRES));
    buttons["ArrowRight"].setText("", fonts, 20);
}

BeatmapPanel::~BeatmapPanel(){

}

void BeatmapPanel::draw(sf::RenderWindow& window) {
    window.draw(sprites["panel"]);
    window.draw(sprites["cover"]);
    for (auto& button : buttons)
        button.second.draw(window);
    window.draw(texts["title"]);

    window.draw(texts["artist"]);
    window.draw(texts["difficulty"]);
    window.draw(texts["difficulty_user"]);
    window.draw(texts["grade"]);

     //    std::cout << "Drawing panel" << std::endl;
}

void BeatmapPanel::setText(const std::string& text, const sf::Font& font, unsigned int characterSize) {

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
    // Adjust the panel
    sprites["panel"].setScale(scale, scale);
    sprites["panel"].setColor(sf::Color(255, 255, 255, opacity));
    screenOffsetX = screenOffsetX - (sprites["panel"].getTexture()->getSize().x * scale) / 2;
    screenOffsetY = screenOffsetY - (sprites["panel"].getTexture()->getSize().y * scale) / 2;
    sprites["panel"].setPosition(screenOffsetX, screenOffsetY); // Also set the position to the screen offset
    // Adjust the cover and text as well
    sprites["cover"].setScale(scale, scale);
    sprites["cover"].setColor(sf::Color(255, 255, 255, opacity));
    sprites["cover"].setPosition(screenOffsetX + PercentX * 5, screenOffsetY + PercentY * 5); // Also set the position to the screen offset


    for (auto& text : texts) {
        text.second.setCharacterSize(textSize * scale);
        //text.second.setColor(sf::Color(255, 255, 255, opacity));
    }
    //std::cout << "sprite[cover] position : " << sprites["cover"].getPosition().x << " " << sprites["cover"].getPosition().y << std::endl;
    texts["title"].setPosition(sprites["cover"].getPosition().x + sprites["cover"].getGlobalBounds().width + PercentX, sprites["cover"].getPosition().y);
    texts["artist"].setPosition(sprites["cover"].getPosition().x + sprites["cover"].getGlobalBounds().width + PercentX, texts["title"].getPosition().y + PercentY * 3);
    texts["difficulty"].setPosition(sprites["cover"].getPosition().x + sprites["cover"].getGlobalBounds().width + PercentX, texts["artist"].getPosition().y + PercentY * 3);
    texts["difficulty_user"].setPosition(sprites["cover"].getPosition().x + sprites["cover"].getGlobalBounds().width + PercentX, texts["difficulty"].getPosition().y + PercentY * 3);
    texts["grade"].setPosition(sprites["cover"].getPosition().x + sprites["cover"].getGlobalBounds().width + PercentX, texts["difficulty_user"].getPosition().y + PercentY * 3);
}

void BeatmapPanel::adjustDifficulty(int difficulty) {
    // Update the difficultyText or any other required elements
    texts["difficulty"].setString("Difficulty : " + std::to_string(difficulty));
}

void adjustDifficultyUserPlus(int * difficultyUser, sf::Text * difficultyUserText) {
    // Update the difficultyText or any other required elements
    *difficultyUser += 1;
    if (*difficultyUser > 10)
          *difficultyUser = 10;
    std::string stringDifficultyUser = std::to_string(*difficultyUser);
    difficultyUserText->setString("Difficulty selected : " + stringDifficultyUser);
    std::cout << "Difficulty selected : " << stringDifficultyUser << std::endl;
    //texts["difficulty_user"].setString("Difficulty selected : " + stringDifficultyUser);
}

void adjustDifficultyUserMinus(int * difficultyUser, sf::Text * difficultyUserText) {
    // Update the difficultyText or any other required elements
    //std::cout << "Size of texts map: " << texts.size() << std::endl;
    std::cout << "this->difficultyUser minus b: " << *difficultyUser << std::endl;
    std::cout << "this->difficultyUser minus adress: " << difficultyUser << std::endl;

    *difficultyUser -= 1;
    if (*difficultyUser < 0)
        *difficultyUser = 0;
    std::string stringDifficultyUser = std::to_string(*difficultyUser);
    difficultyUserText->setString("Difficulty selected : " + stringDifficultyUser);
    std::cout << "Difficulty selected : " << stringDifficultyUser << std::endl;
}

void BeatmapPanel::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& button : buttons)
        button.second.handleEvent(event, window);
}

/*
void BeatmapPanel::handleButtonClick(const sf::Vector2f& mousePosition) {
    if (leftArrowButton.isClicked(mousePosition)) {
        if (currentDifficulty > 0) {
            currentDifficulty--;
            // Update the difficultyText or any other required elements
        }
    } else if (rightArrowButton.isClicked(mousePosition)) {
        if (currentDifficulty < MAX_DIFFICULTY) {  // Assuming MAX_DIFFICULTY is a defined constant or you can replace with the desired value
            currentDifficulty++;
            // Update the difficultyText or any other required elements
        }
    }
}
 */
