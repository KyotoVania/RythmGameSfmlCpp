#include <SFML/Graphics.hpp>
#include <string>


/*class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, const std::string& textString, sf::Font& font)
            : position(position), size(size) {

        // Définir la forme du bouton
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(sf::Color::Blue); // Couleur du bouton

        // Définir le texte du bouton
        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(24); // Taille du texte
        text.setFillColor(sf::Color::White); // Couleur du texte

        // Centrer le texte dans le bouton
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        text.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    }

    // Dessine le bouton sur la fenêtre spécifiée
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    // Vérifie si les coordonnées du clic de souris sont à l'intérieur du bouton
    bool isMouseOver(sf::Vector2f mousePosition) {
        return mousePosition.x >= position.x && mousePosition.x <= position.x + size.x &&
               mousePosition.y >= position.y && mousePosition.y <= position.y + size.y;
    }

protected:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Vector2f position;
    sf::Vector2f size;
};

class TriangleButton : public Button {
public:
    TriangleButton(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Font& font)
            : Button(position, size, text, font) {

        // Création de la forme triangulaire du bouton
        shape.setPointCount(3);
        shape.setPoint(0, sf::Vector2f(0.0f, 0.0f));
        shape.setPoint(1, sf::Vector2f(base, 0.0f));
        shape.setPoint(2, sf::Vector2f(base / 2.0f, size.x));
    }
}; */

/*
class Button {
public:
    Button(sf::Vector2f position, sf::Shape* shape, const std::string& buttonText) {
        this->position = position;
        this->shape = shape;
        this->text.setString(buttonText);
    }

    virtual ~Button() {
        delete shape;
    }

    virtual void draw(sf::RenderWindow& window) {
        shape->setPosition(position);
        window.draw(*shape);
        window.draw(text);
    }
protected:
    sf::Vector2f position;
    sf::Shape* shape;
    sf::Text text;
}; */

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
