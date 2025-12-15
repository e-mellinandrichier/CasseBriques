#pragma once

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Cannon : public GameObject
{
public:
    Cannon(float x, float y, float width, float height);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    // Point cannon towards a position
    void aimAt(float targetX, float targetY);
    void aimAt(const sf::Vector2f& target);

    // Get direction the cannon is aiming
    sf::Vector2f getDirection() const;

    float getAngle() const { return m_rotation; }

private:
    sf::RectangleShape m_shape;
    sf::CircleShape m_base;
};

