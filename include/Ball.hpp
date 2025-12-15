#pragma once

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Ball : public GameObject
{
public:
    Ball(float x, float y, float radius, const sf::Vector2f& velocity);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    float getRadius() const { return m_radius; }

    // Bounce off walls (left, right, top)
    void bounceOffWalls(float windowWidth, float windowHeight);

    // Check if ball is out of bounds (below window)
    bool isOutOfBounds(float windowHeight) const;

    // Collision with AABB (for bricks)
    bool checkCollisionWithAABB(const sf::FloatRect& aabb);
    void handleCollisionWithAABB(const sf::FloatRect& aabb);

    // Enable/disable gravity
    void setGravityEnabled(bool enabled) { m_gravityEnabled = enabled; }

private:
    float m_radius;
    sf::CircleShape m_shape;
    float m_speed;
    bool m_gravityEnabled{true};
    static constexpr float m_gravity{50.f}; // Gravity acceleration in pixels per second squared (reduced)

    sf::Vector2f getCenter() const;
};

