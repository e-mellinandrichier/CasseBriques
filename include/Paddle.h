#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Paddle : public GameObject
{
public:
    Paddle(float x, float y, float width, float height);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    // Move paddle left or right
    void moveLeft(float speed);
    void moveRight(float speed);
    void stop();

    // Get paddle bounds for collision
    sf::FloatRect getBounds() const { return getAABB(); }

private:
    sf::RectangleShape m_shape;
    float m_moveSpeed{0.f};
    static constexpr float m_maxSpeed{400.f};
};

