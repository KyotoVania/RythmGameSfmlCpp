#include <SFML/Graphics.hpp>
#include <string>

class Button {
protected:
    sf::Vector2f position;
    sf::Shape* shape;
    sf::Text text;

public:
    Button(sf::Vector2f position, sf::Shape* shape, const std::string& buttonText, sf::Font& font, sf::Color color) {
        this->position = position;
        this->shape = shape;
        this->shape->setFillColor(color);
        this->text.setString(buttonText);
        this->text.setFont(font);
        this->text.setPosition(position.x + shape->getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2, position.y + shape->getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
    }

    virtual ~Button() {
        delete shape;
    }

    bool isMouseOver(sf::Vector2f mousePosition) const {
        return shape->getGlobalBounds().contains(mousePosition);
    }

    virtual void draw(sf::RenderWindow& window) {
        shape->setPosition(position);
        window.draw(*shape);
        window.draw(text);
    }
};

class RectangleButton : public Button {
public:
    //RectangleButton(sf::Vector2f position, sf::Vector2f size, const std::string& buttonText, sf::Font font) : Button(position, new sf::RectangleShape(size), buttonText, font) {}
    RectangleButton(sf::Vector2f position, sf::Vector2f size, const std::string& buttonText, sf::Font& font, sf::Color color)
            : Button(position, new sf::RectangleShape(size), buttonText, font, color) {}

    void setSize(sf::Vector2f size) {
        static_cast<sf::RectangleShape*>(shape)->setSize(size);
    }
};

class TriangleButton : public Button {
public:
    TriangleButton(sf::Vector2f sommet_one, sf::Vector2f sommet_two, sf::Vector2f sommet_three, const std::string& buttonText, sf::Font& font, sf::Color color) : Button(new sf::ConvexShape(sommet_one, sommet_two, sommet_three), buttonText, font, color) {
        float centerX = (sommet_one.x + sommet_two.x + sommet_three.x) / 3.0f;
        float centerY = (sommet_one.y + sommet_two.y + sommet_three.y) / 3.0f;
        text.setPosition(centerX, centerY);
    }

    void setRadius(float radius) {
        static_cast<sf::CircleShape*>(shape)->setRadius(radius);
    }
};
