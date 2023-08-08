// Button.hpp
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <functional>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
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
public:
    Button();
    Button(const sf::Texture& texture, const sf::Vector2f& position, std::function<void()> onClick, std::pair<int, int> res);
    ~Button();

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setText(const std::string& text, const sf::Font& font, unsigned int characterSize);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text text;
    std::function<void()> onClick;
    ButtonState state;
    sf::Vector2f position;
    sf::Vector2f size;
    ButtonType type;
};
#endif /*BUTTON_HPP_*/
