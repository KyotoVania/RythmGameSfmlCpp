/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Menu.cpp
*/

#include "Menu/Menu.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{
}

// Menu.cpp
void Menu::load(const std::pair<int, int>& res)
{
    // Load the background image
    sf::Texture& backgroundTexture = textures["background"];
    if (!backgroundTexture.loadFromFile("Resources/UI/Background.jpg")) {
        // Handle error...
    }
    sf::Sprite background(backgroundTexture);
    sprites["background"] = background;

    // Load the font
    sf::Font& font = fonts["sansation"];
    if (!font.loadFromFile("Resources/Fonts/sansation.ttf")) {
        // Handle error...
    }

    // Load the bottom buttons
    for (int i = 1; i <= 6; ++i) {
        std::string texturePath = "Resources/UI/Btn0" + std::to_string(i) + ".png";
        sf::Texture& buttonTexture = textures["button" + std::to_string(i)];
        if (!buttonTexture.loadFromFile(texturePath)) {
            // Handle error...
        }
        std::string buttonName = "button" + std::to_string(i);
        buttons.emplace(buttonName, Button(buttonTexture, sf::Vector2f(10 + i * 10, 80), [buttonName](){
            std::cout << "Button " << buttonName << " clicked!" << std::endl;
        }, res));
        buttons[buttonName].setText(std::to_string(i), font, 30); // You need to load the font somewhere before this
    }

    this->_res = res;

}


void Menu::loadBeatmaps(Database& database) {
    for (int i = 0; i < database.getNbBeatmaps(); ++i) {
        BeatmapConfig beatmap = database.getBeatmap(i);
        if (beatmap.getFolderPath() == "") {
            continue;
        }

        // Load the cover texture
        std::string coverTexturePath = "Resources/Beatmaps/"
                                       + beatmap.getFolderPath() + "/Cover.png"; // Assuming the cover image is named "cover.png"
        sf::Texture& coverTexture = textures[coverTexturePath];
        if (!coverTexture.loadFromFile(coverTexturePath)) {
            cout << "Error loading texture " << coverTexturePath << endl;
            // Handle error...
        }

        // Load the panel texture
        std::string panelTexturePath = "Resources/UI/MainPanel01.png"; // Assuming the panel image is named "MainPanel01.png"
        sf::Texture& panelTexture = textures[panelTexturePath];
        if (!panelTexture.loadFromFile(panelTexturePath)) {
            cout << "Error loading texture " << panelTexturePath << endl;
            // Handle error...
        }

        // Create a BeatmapPanel object and add it to the beatmapPanel vector
        BeatmapPanel panel(panelTexture, coverTexture, sf::Vector2f(5, 5), _res , "S"); // You may need to adjust the parameters here
        beatmapPanel.push_back(panel);
    }
}


void Menu::update(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& button : buttons) {
        button.second.handleEvent(event, window);
    }

    // Determine the selected panel
    int selectedPanel = 0; // This should be updated based on user input

    // Adjust the panels
    for (int i = 0; i < beatmapPanel.size(); ++i) {
        if (i < selectedPanel) {
            beatmapPanel[i].adjust(0.8f, 128, sf::Vector2f(-2, -1), res);
        } else if (i > selectedPanel) {
            beatmapPanel[i].adjust(0.8f, 128, sf::Vector2f(2, -1), res);
        } else {
            beatmapPanel[i].adjust(1.0f, 255, sf::Vector2f(0, 0), res);
        }
    }
}


void Menu::draw(sf::RenderWindow& window)
{
    window.draw(sprites["background"]);
    for (auto& button : buttons) {
        button.second.draw(window);
    }

    // Draw the panels in reverse order
    std::cout << beatmapPanel.size() << std::endl;
    for (int i = beatmapPanel.size() - 1; i >= 0; --i) {
        beatmapPanel[i].draw(window);
    }
}

