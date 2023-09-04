/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** Projectile.hpp
*/
#ifndef PROJECTILE_HPP_
	#define PROJECTILE_HPP_

#include <SFML/Graphics.hpp>

class Projectile {
public:
    // Constructor to initialize the projectile
    Projectile(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &size, float speed, int id) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        this->position = position;
        sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
        this->id = id;
        this->speed = speed;
    }

    // Update the projectile's position based on its speed
    void update(float deltaTime) {
        //sprite.move(0, speed * deltaTime);
        if (isAnimated) {
            frame++;
            if (frame > frameMax)
                frame = 0;
            sprite.setTextureRect(sf::IntRect(frame * spriteSize, 0, spriteSize, spriteSize));
            spriteSize += spriteSizeMax / frameMax;
            if (spriteSize > spriteSizeMax)
                spriteSize = spriteSizeMax;
        }
    }

    // Draw the projectile
    void draw(sf::RenderWindow &window) {
        window.draw(sprite);
    }

    // Getter for the sprite (if needed)
    const sf::Sprite& getSprite() const {
        return sprite;
    }

    void enableAnimation(int frameMax, int spriteSizeMax) {
        isAnimated = true;
        this->frameMax = frameMax;
        this->spriteSizeMax = spriteSizeMax;
    }

    // Add other functionalities like collision detection, etc.

private:
    sf::Sprite sprite;
    float speed;
    int id;
    sf::Vector2f position;
    float radius;
    float angle;
    int frame;
    int frameMax;
    int spriteSize;
    int spriteSizeMax;
    bool isAnimated = false;
};

#endif /*PROJECTILE_HPP_*/