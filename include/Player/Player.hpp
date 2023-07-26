/*
** EPITECH PROJECT, 2023
** newtry
** File description:
** Player.hpp
*/
#ifndef PLAYER_HPP_
	#define PLAYER_HPP_
#include "Visualizer/FFT.hpp"

class Player {
	public:
		Player();
		~Player();
		void draw(sf::RenderWindow& window);
		void update();
		sf::Clock colorChangeClock;
		bool gotHit = false;
		float invincibilityTime = 1.5f; // The length of the invincibility period in seconds
		float invincibilityTimer = 0.0f; // The current state of the timer
		sf::CircleShape player;
		/**
		* Planet background shape.
		*/
		sf::CircleShape player_background;
		/**
		* Planet texture.
		*/
		sf::Texture player_texture;
		sf::Texture laser_texture;
		const float base_player_radius = 20;
		std::pair<float, float> base_player_position = { 400,300 };
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		bool _color = false;
		bool getColor();
		void setBackgroundColor(bool color);
		sf::RectangleShape laser;
		
	protected:
	
	private:
};

#endif /*PLAYER_HPP_*/