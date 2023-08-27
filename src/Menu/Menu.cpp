/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Menu.cpp
*/

#include "Menu/Menu.hpp"
#include "Core/Core.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{
}

void Menu::loadTextures(Database& database)
{
    // Load the background texture
    if (!textures["background"].loadFromFile("Resources/UI/Background.jpg")) {
        std::cout << "Error loading texture : " << "Resources/UI/Background.jpg" << std::endl;
        // Handle error...
    }
    // Load button textures
    for (int i = 1; i <= 6; ++i) {
        std::string texturePath = "Resources/UI/Btn0" + std::to_string(i) + ".png";
        if (!textures["Btn0" + std::to_string(i)].loadFromFile(texturePath)) {
            std::cout << "Error loading texture " << texturePath << std::endl;
            // Handle error...
        }
    }

    // Load the panel texture
    if (!textures["MainPanel01"].loadFromFile("Resources/UI/MainPanel01.png")) {
        std::cout << "Error loading texture : " << "Resources/UI/MainPanel01.png" << std::endl;
        // Handle error...
    }
    // Load arrow textures

    if (!textures["ArrowsRight"].loadFromFile("Resources/UI/ArrowsRight.png")) {
        std::cout << "Error loading texture : " << "Resources/UI/ArrowsRight.png" << std::endl;
        // Handle error...
    }
    std::cout << "Loading arrow textures" << std::endl;
    if (!textures["ArrowsLeft"].loadFromFile("Resources/UI/ArrowsLeft.png")) {
        std::cout << "Error loading texture : " << "Resources/UI/ArrowsLeft.png" << std::endl;
        // Handle error...
    }
    // Load the cover texture
    for (int i = 0; i < database.getNbBeatmaps(); ++i) {
        BeatmapConfig beatmap = database.getBeatmap(i);
        if (beatmap.getFolderPath() == "") {
            continue;
        }
        std::string coverPath = "Resources/Beatmaps/" + beatmap.getFolderPath() + "/Cover.png";
        if (!textures[beatmap.getFolderPath()].loadFromFile(coverPath)) {
            std::cout << "Error loading texture : " << coverPath << std::endl;
            // Handle error...
        }
    }
}



// Menu.cpp
void Menu::load(const std::pair<int, int>& res, Database& database)
{
    buttonConfigs = {
            {"Left", [this](){ this->slideLeft(); }},
            {"Right", [this](){ this->slideRight(); }},
            {"Exit", [](){ std::cout << "Exiting..." << std::endl; /* Add exit logic here */ }},
            {"Analyse", [this](){
                this->onAnalyzeButtonClicked(getActualSongName());
            }},
            {"Play", [](){std::cout<< "Playing..." << std::endl;}}
            // Add more configurations as needed
    };
    // Load the background image
    loadTextures(database);
    sf::Sprite background(textures["background"]);
    sprites["background"] = background;

    // Load the font
    if (!fonts["sansation"].loadFromFile("Resources/Fonts/sansation.ttf")) {
        std::cout << "Error loading font" << std::endl;
        // Handle error...
    }

    // Load the bottom buttons
    for (int i = 1; i <= 6; ++i) {
        std::string buttonName = "button" + std::to_string(i);

        if (i - 1 < buttonConfigs.size()) { // Ensure we don't go out of bounds
            buttons.emplace(buttonName, Button(textures["Btn0" + std::to_string(i)]
                    ,sf::Vector2f(10 + i * 10, 80), buttonConfigs[i-1].onClick, res));
            buttons[buttonName].setText(buttonConfigs[i-1].text, fonts["sansation"], 30);
        } else {
            buttons.emplace(buttonName, Button(textures["Btn0" + std::to_string(i)], sf::Vector2f(10 + i * 10, 80), [](){}, res)); // Default empty function
            buttons[buttonName].setText(std::to_string(i), fonts["sansation"], 30);
        }
    }
    this->_res = res;
    loadBeatmaps(database);
}

void Menu::loadBeatmaps(Database& database) {
    //std::cout << "Loading beatmaps in MENU" << std::endl;
    for (int i = 0; i < database.getNbBeatmaps(); ++i) {
        std::cout << "Loading beatmap " << i << std::endl;
        BeatmapConfig beatmap = database.getBeatmap(i);
        if (beatmap.getFolderPath() == "") {
            continue;
        }
        
        // Create a BeatmapPanel object and add it to the beatmapPanel vector
        BeatmapPanel panel(textures["MainPanel01"], textures["ArrowsLeft"], textures["ArrowsRight"],
                           textures[beatmap.getFolderPath()],
                           sf::Vector2f(5, 5), _res, beatmap, fonts["sansation"]);
        beatmapPanel.push_back(panel);
    }
}


void Menu::update(const sf::Event& event, const sf::RenderWindow& window)
{
    for (auto& button : buttons) {
        button.second.handleEvent(event, window);
    }

    // Determine the selected panel
    int selectedPanel = selectedPanelIndex;
    // Adjust the panels
    for (int i = 0; i < beatmapPanel.size(); ++i) {
        if (i < selectedPanel) {
            beatmapPanel[i].adjust(0.5f, 128, sf::Vector2f(2, 4), _res);
        } else if (i > selectedPanel) {
            beatmapPanel[i].adjust(0.5f, 128, sf::Vector2f(8, 4), _res);
        } else {
            beatmapPanel[i].adjust(0.8f, 255, sf::Vector2f(5, 5), _res);
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
   // std::cout << "there is x beatpmap : " + beatmapPanel.size() << std::endl;
    for (int i = beatmapPanel.size() - 1; i >= 0; --i) {
        beatmapPanel[i].draw(window);
    }
}

void Menu::slideLeft() {
    if (selectedPanelIndex > 0) {
        selectedPanelIndex--;
    }
    // You can add wrap-around logic here if you want the selection to loop back to the last panel when at the first panel.
}

void Menu::slideRight() {
    if (selectedPanelIndex < beatmapPanel.size() - 1) {
        selectedPanelIndex++;
    }
    // You can add wrap-around logic here if you want the selection to loop back to the first panel when at the last panel.
}


void Menu::onAnalyzeButtonClicked(const std::string& beatmapPath)
{
    std::cout << "Analyzing beatmap " << beatmapPath << std::endl;
    //fft.loadMusic(beatmapPath); // Assuming fftMenu is an instance of FFT_Menu in the Menu class
    fft.loadMusicMenu(beatmapPath);
    std::cout << "load music finished" << std::endl;
    int difficulty = fft.calculate_song_difficulty();
    std::cout << "Difficulty : " << difficulty << std::endl;
    //setDifficulty(difficulty);
}

std::string Menu::getActualSongName() {

    std::string beatmapPath = "Resources/Beatmaps/" +
     beatmapPanel[selectedPanelIndex].getBeatmapName();
    return beatmapPath;
}