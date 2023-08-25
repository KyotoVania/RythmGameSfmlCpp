#ifndef BALL_HPP
#define BALL_HPP
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Projectile
{
public:
    Projectile(const float x, const float y, const float radius, const float speed, float angle, bool yingOrYang);
    ~Projectile();
    sf::CircleShape circle;
    float speed;
    bool yingYang;
    float radius;
    float angle;
    std::pair<float, float> position;
    bool operator==(const Projectile& other) const {
        return position == other.position && speed == other.speed && angle == other.angle;
    }
};

#endif //BALL_HPP