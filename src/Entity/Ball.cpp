/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** beatmappanell.cpp
*/

#include "Entity/Ball.hpp"
#include <cmath>
#pragma region Projectile
/**
 *  Initializes drawables.
 */

Projectile::Projectile(const float x, const float y, const float radius, const float speed,  float angle, bool yingOrYang)
{
    circle.setRadius(radius);
    if (yingOrYang)
        circle.setFillColor(sf::Color::White);
    else
        circle.setFillColor(sf::Color::Black);
    yingYang = yingOrYang;
    circle.setOrigin(radius, radius);
    circle.setPosition(x, y);
    this->speed = speed;
    this->angle = angle;
    this->radius = radius;
    this->position = { x, y };
}

Projectile::~Projectile()
{
}
