/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Button.cpp
*/

#include "GraphicElement/Button.hpp"

Button::Button(sf::Vector2f position, sf::Shape* shape,
    const std::string& buttonText, sf::Font& font, sf::Color color, int size) {
    this->position = position;
    this->shape = shape;
    this->shape->setFillColor(color);

    this->text.setString(buttonText);
    this->text.setFont(font);
    this->text.setCharacterSize(size);
    this->text.setPosition(position.x + shape->getGlobalBounds().width / 2 -
    this->text.getGlobalBounds().width / 2, position.y +
    shape->getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
}

Button::~Button() {
    delete shape;
    delete &text;
}

bool Button::isMouseOver(sf::Vector2f mousePosition) const {
    return shape->getGlobalBounds().contains(mousePosition);
}

void Button::draw(sf::RenderWindow& window) {
    shape->setPosition(position);
    window.draw(*shape);
    window.draw(text);
}