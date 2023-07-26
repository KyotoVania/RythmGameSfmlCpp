/*
** EPITECH PROJECT, 2023
** newtry
** File description:
** Player.cpp
*/

#include "Player/Player.hpp"

/*
Player::Player()
{
    //initialization of player
    player_texture.loadFromFile("Resources/player2.png");
    laser_texture.loadFromFile("Resources/laser.png");
    player_texture.setSmooth(true);
    player.setRadius(base_player_radius);
    player.setPointCount(40);
    //player.setFillColor(Color(255, 255, 255, 128));
    player.setTexture(&player_texture);
    player.setOrigin(base_player_radius, base_player_radius);
    //use pair position to set position of player base_player_position
    player.setPosition(Vector2f((base_player_position.first), (base_player_position.second)));

    player_background.setRadius(base_player_radius * 0.75f);  // make it smaller than the player
    player_background.setPointCount(40);
    player_background.setFillColor(sf::Color::White);  // make it white
    player_background.setOrigin(base_player_radius * 0.75f, base_player_radius * 0.75f + 0.24f * base_player_radius);  // position it right below the player
    player_background.setPosition(Vector2f((base_player_position.first), (base_player_position.second)));
    laser.setSize(sf::Vector2f(2.0f, HEIGHT));  // HEIGHT should be the height of your window.
    laser.setTexture(&laser_texture);
    laser.setOrigin(1.0f, 0.0f);  // Set origin to the bottom center, so it will rotate around this point.
    laser.setPosition(base_player_position.first, base_player_position.second);  // Position at player's position
    laser.setRotation(180);  // Rotate the laser to point upwards.
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(player_background);
	window.draw(player);
    window.draw(laser);
}

void Player::moveLeft()
{
		//check if the player does not touch the screen limit
		if (base_player_position.first > 0) {
            base_player_position.first -= 8;
        }
}

void Player::moveRight()
{
       if (base_player_position.first < WIDTH) {
            base_player_position.first += 8;
        }
}

void Player::moveUp()
{
        if (base_player_position.second > 0) {
            base_player_position.second -= 8;
        }
}

void Player::moveDown()
{
        if (base_player_position.second < HEIGHT) {
            base_player_position.second += 8;
        }
}

void Player::update()
{
    player.setPosition(Vector2f((base_player_position.first), (base_player_position.second)));
    player_background.setPosition(Vector2f((base_player_position.first), (base_player_position.second + base_player_radius * 0.2))); // Position just below player
    laser.setPosition(base_player_position.first, base_player_position.second);
}

bool Player::getColor()
{
    return _color;
}

void Player::setBackgroundColor(bool color)
{
    _color = color;
}
*/