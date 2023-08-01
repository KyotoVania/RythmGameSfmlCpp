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

}


void Menu::loadBeatmaps(Database& database) {
    for (int i = 0; i < database.getNbBeatmaps(); ++i) {
        BeatmapConfig beatmap = database.getBeatmap(i);
        if (beatmap.getFolderPath() == "") {
            continue;
        }
        sf::Texture texture;
        std::string texturePath = "Resources/Beatmaps/"
                                  + beatmap.getFolderPath() + "/Cover.png"; // Assuming the cover image is named "cover.png"
        if (!texture.loadFromFile(texturePath)) {
            cout << "Error loading texture " << texturePath << endl;
            // Handle error...
        }
        textures[texturePath] = texture;
        sf::Sprite sprite(texture);
        sprites[texturePath] = sprite;

        // Load the panel texture
        sf::Texture panelTexture;
        std::string panelTexturePath = "Resources/UI/MainPanel01.png"; // Assuming the panel image is named "MainPanel01.png"
        if (!panelTexture.loadFromFile(panelTexturePath)) {
            cout << "Error loading texture " << panelTexturePath << endl;
            // Handle error...
        }
        textures[panelTexturePath] = panelTexture;

        // Create a BeatmapPanel object and add it to the beatmapPanel vector
        BeatmapPanel panel(panelTexture, texture, sf::Vector2f(0, 0), std::pair<int, int>(0, 0), "S"); // You may need to adjust the parameters here
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
            beatmapPanel[i].adjust(0.8f, 128, sf::Vector2f(-200, -100));
        } else if (i > selectedPanel) {
            beatmapPanel[i].adjust(0.8f, 128, sf::Vector2f(200, -100));
        } else {
            beatmapPanel[i].adjust(1.0f, 255, sf::Vector2f(0, 0));
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

