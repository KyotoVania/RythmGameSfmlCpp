/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** Planet.cpp
*/


#include "Entity/Planet.hpp"
/*
PlanetProjectile::PlanetProjectile()
{
    this->circle = sf::CircleShape(50);
    this->circle.setFillColor(sf::Color::Red);
    this->circle.setOutlineThickness(10);
    this->circle.setOutlineColor(sf::Color::Black);
    this->circle.setPosition(100, 100);
}
*/
PlanetProjectile::PlanetProjectile( const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &size, float speed, int id,PlanetColor color)
        : Projectile(texture, position, size, speed, id), color(color)
{
    this->circle = sf::CircleShape(50);
//    this->planet.setFillColor(sf::Color::Red);
    this->circle.setOutlineThickness(10);
    this->circle.setOutlineColor(sf::Color::Black);
    this->circle.setPosition(100, 100);
}

PlanetProjectile::~PlanetProjectile()
{
}