/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** PlayerGraphic.hpp
*/

#ifndef PLAYER_GRAPHIC_HPP_
	#define PLAYER_GRAPHIC_HPP_

class PlayerGraphic {
	public:
    
	protected:
    float invincibilityTime = 1.5f; // The length of the invincibility period in seconds
    float invincibilityTimer = 0.0f; // The current state of the timer
    sf::CircleShape player;
    sf::CircleShape playerBackground;
    sf::Texture playerTexture;
    sf::Texture laserTexture;
    const float basePlayerRadius = 20;
    std::pair<float, float> basePlayerPosition = { 400,300 };
	private:
};

#endif /*PLAYER_GRAPHIC_HPP_*/