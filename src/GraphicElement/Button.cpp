/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Button.cpp
*/

#include "GraphicElement/Button.hpp"

Button::Button() {
}

Button::Button(const sf::Texture& texture, const sf::Vector2f& position, std::function<void()> onClick, std::pair<int, int> res)
        : onClick(onClick)
{
    sprite.setTexture(texture);
    // Convert position from normalized coordinates to pixel coordinates
    sf::Vector2f pixelPosition;
    pixelPosition.x = position.x / 100.0f * res.first;
    pixelPosition.y = position.y / 100.0f * res.second;
    sprite.setPosition(pixelPosition);
}


Button::~Button() {
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            onClick();
        }

    }
}


void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}


// Button.cpp
void Button::setText(const std::string& text, const sf::Font& font, unsigned int characterSize) {
    this->text.setString(text);
    this->text.setFont(font);
    this->text.setCharacterSize(characterSize);
    // Center the text in the button
    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    this->text.setPosition(sf::Vector2f(position.x + size.x/2.0f, position.y + size.y/2.0f));
}
