/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** PlayerConfig.cpp
*/

#include "Player/PlayerConfig.hpp"

sf::Keyboard::Key PlayerConfig::stringToKey(const std::string& key) {
    if (key.length() != 1) {
        throw std::runtime_error("Invalid key: " + key);
    }

    char c = key[0];
    if (c >= 'a' && c <= 'z') {
        return static_cast<sf::Keyboard::Key>(c - 'a' + sf::Keyboard::A);
    } else if (c == ' ') {
        return sf::Keyboard::Space;
    } else {
        throw std::runtime_error("Invalid key: " + key);
    }
}


PlayerConfig::PlayerConfig()
{
    keyBindings["MoveUp"] = sf::Keyboard::W;
    keyBindings["MoveDown"] = sf::Keyboard::S;
    keyBindings["MoveLeft"] = sf::Keyboard::A;
    keyBindings["MoveRight"] = sf::Keyboard::D;
    keyBindings["SwitchColor"] = sf::Keyboard::Space;
}

PlayerConfig::~PlayerConfig()
{
}

void PlayerConfig::load(const libconfig::Setting& playerSetting) {
    playerSetting.lookupValue("name", Name);
    playerSetting.lookupValue("id", Id);
    playerSetting.lookupValue("accuracy", Accuracy);
    const libconfig::Setting& input = playerSetting["Input"];
    std::string key;
    input.lookupValue("up", key);
    keyBindings["up"] = stringToKey(key);
    input.lookupValue("down", key);
    keyBindings["down"] = stringToKey(key);
    input.lookupValue("left", key);
    keyBindings["left"] = stringToKey(key);
    input.lookupValue("right", key);
    keyBindings["right"] = stringToKey(key);
    input.lookupValue("action", key);
    keyBindings["action"] = stringToKey(key);
}

void PlayerConfig::print() {
    std::cout << "Name: " << Name << std::endl;
    std::cout << "Id: " << Id << std::endl;
    std::cout << "Accuracy: " << Accuracy << std::endl;
    std::cout << "Key bindings:" << std::endl;
    for (auto& binding : keyBindings) {
        std::cout << binding.first << ": " << binding.second << std::endl;
    }
}