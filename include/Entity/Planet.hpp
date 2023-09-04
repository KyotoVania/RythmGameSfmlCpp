/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** PlanetProjectile.hpp
*/
#ifndef PLANET_PROJECTILE_HPP_
	#define PLANET_PROJECTILE_HPP_

#include "Entity/Projectile.hpp"

typedef enum {
    RED,
    BLUE,
    GREEN,
    YELLOW
} PlanetColor;

class PlanetProjectile : public Projectile {
	public:
		PlanetProjectile(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &size, float speed, int id, PlanetColor color);
		~PlanetProjectile();

	protected:
    PlanetColor color;
    sf::CircleShape circle;
private:
};

#endif /*PLANET_PROJECTILE_HPP_*/