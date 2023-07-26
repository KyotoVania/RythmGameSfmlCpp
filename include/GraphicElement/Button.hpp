/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Button.hpp
*/
#ifndef BUTTON_HPP_
	#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <string>

enum ButtonType {
    RECTANGLE,
    TRIANGLE,
    CIRCLE,
    TEXT
};

enum ButtonState {
    NORMAL,
    HOVER,
    PRESSED,
    DISABLED
};

class Button {
protected:
    sf::Vector2f position;
    sf::Shape* shape;
    sf::Text text;

public:
    Button(sf::Vector2f position, sf::Shape* shape,
    const std::string& buttonText, sf::Font& font, sf::Color color, int size);
    virtual ~Button();
    bool isMouseOver(sf::Vector2f mousePosition) const;
    virtual void draw(sf::RenderWindow& window);
};

#endif /*BUTTON_HPP_*/
