/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** RectangleButton.cpp
*/

#include "GraphicElement/RectangleButton.hpp"

RectangleButton::
RectangleButton(sf::Vector2f position, sf::Vector2f size, const std::string& buttonText, sf::Font& font, sf::Color color, int sizeText)
: Button(position, new sf::RectangleShape(size), buttonText, font, color, sizeText) {
}

void RectangleButton::setSize(sf::Vector2f size) {
    static_cast<sf::RectangleShape*>(shape)->setSize(size);
}