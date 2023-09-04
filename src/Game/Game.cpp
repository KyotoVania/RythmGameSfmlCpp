/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** Game.cpp
*/

#include "Game/Game.hpp"

Game::Game()
{

}

Game::~Game()
{
}

void Game::loadTextures()
{
    //the game class will hold all the texture in a map, to be able to access them from anywhere
    //they will used when creating the entities and the background of the game
    if (!textures["background"].loadFromFile("Resources/Game/gameBackground.jpg")) {
        std::cout << "Error loading texture : " << "Resources/Game/gameBackground.jpg" << std::endl;
        // Handle error...
    }
    if (!textures["redPlanet"].loadFromFile("Resources/Game/Entity/redPlanet.png")) {
        std::cout << "Error loading texture : " << "Resources/Game/Entity/redPlanet.png" << std::endl;
        // Handle error...
    }
    if (!textures["bluePlanet"].loadFromFile("Resources/Game/Entity/bluePlanet.png")) {
        std::cout << "Error loading texture : " << "Resources/Game/Entity/bluePlanet.png" << std::endl;
        // Handle error...
    }
    if (!textures["greenPlanet"].loadFromFile("Resources/Game/Entity/greenPlanet.png")) {
        std::cout << "Error loading texture : " << "Resources/Game/Entity/greenPlanet.png" << std::endl;
        // Handle error...
    }
    if (!textures["blueLaser"].loadFromFile("Resources/Game/blueLaser.png")) {
        std::cout << "Error loading texture : " << "Resources/Game/blueLaser.png" << std::endl;
        // Handle error...
    }
    if (!fonts["sansation"].loadFromFile("Resources/Fonts/sansation.ttf")) {
        std::cout << "Error loading font : sansation" << std::endl;
        // Handle error...
    }
    _res = {1920, 1080};
}

void Game::loadEntities()
{
    // Load a pool of projectiles for each planet
    for (int i = 0; i < 10; ++i) {
        sf::Vector2f position = {rand() % _res.first, rand() % _res.second};
        sf::Vector2f size = {50, 50};
        float speed = 10;
        int id = i;
        PlanetProjectile * redProj = new PlanetProjectile(textures["redPlanet"], position, size, speed, id, RED);
        redProj->enableAnimation(100, 126);
        PlanetProjectile* blueProj = new PlanetProjectile(textures["bluePlanet"], position, size, speed, id, BLUE);
        blueProj->enableAnimation(100, 126);
        PlanetProjectile *greenProj=new PlanetProjectile(textures["greenPlanet"], position, size, speed, id, GREEN);
        greenProj->enableAnimation(100, 126);
        projectilePools["red"].push_back(redProj);
        projectilePools["blue"].push_back(blueProj);
        projectilePools["green"].push_back(greenProj);
    }
}

void Game::loadTexts()
{
    // Load the font
    if (!fonts["sansation"].loadFromFile("Resources/Fonts/sansation.ttf")) {
        std::cout << "Error loading font" << std::endl;
        // Handle error...
    }
    // Load the text
    texts["score"] = sf::Text("Score : 0", fonts["sansation"]);
    texts["score"].setCharacterSize(24);
    texts["score"].setFillColor(sf::Color::White);
    texts["score"].setPosition(10, 10);
}

void Game::loadSprites()
{
    // Load the background
    sprites["background"] = sf::Sprite(textures["background"]);
    sprites["background"].setScale(1.5, 1.5);
}

void Game::draw(sf::RenderWindow& window)
{
    window.draw(sprites["background"]);
    window.draw(texts["score"]);
    // Draw the projectiles
    for (auto& projectile : projectilePools["red"]) {
        window.draw(projectile->getSprite());
    }
    for (auto& projectile : projectilePools["blue"]) {
        window.draw(projectile->getSprite());
    }
    for (auto& projectile : projectilePools["green"]) {
        window.draw(projectile->getSprite());
    }
}

void Game::setDifficulty(int difficulty)
{
    this->difficulty = difficulty;
}

void Game::update()
{
    // Update the projectiles
    for (auto& projectile : projectilePools["red"]) {
        projectile->update(0.0);
    }
    for (auto& projectile : projectilePools["blue"]) {
        projectile->update(0.0);
    }
    for (auto& projectile : projectilePools["green"]) {
        projectile->update(0.0);
    }
}