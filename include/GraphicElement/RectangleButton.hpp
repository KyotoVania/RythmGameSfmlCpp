/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** RectangleButton.hpp
*/
#ifndef RECTANGLEBUTTON_HPP_
	#define RECTANGLEBUTTON_HPP_

#include "Button.hpp"

class RectangleButton : public Button {
public:
    RectangleButton(sf::Vector2f position, sf::Vector2f size,
    const std::string& buttonText, sf::Font& font, sf::Color color, int sizeText);

    void setSize(sf::Vector2f size);
};


#endif /*RECTANGLEBUTTON_HPP_*/