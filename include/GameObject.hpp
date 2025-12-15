#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class GameObject
{
public:
    GameObject(float x, float y, float width, float height);
    virtual ~GameObject() = default;

    // Position
    sf::Vector2f getPosition() const { return m_position; }
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);

    // Velocity
    sf::Vector2f getVelocity() const { return m_velocity; }
    void setVelocity(float x, float y);
    void setVelocity(const sf::Vector2f& vel);

    // Rotation
    float getRotation() const { return m_rotation; }
    void setRotation(float angle);
    void rotate(float angle);

    // Size
    sf::Vector2f getSize() const { return m_size; }
    void setSize(float width, float height);

    // AABB Collision Box
    sf::FloatRect getAABB() const;

    // Update (called each frame)
    virtual void update(float deltaTime);

    // Render
    virtual void draw(sf::RenderWindow& window) const = 0;

    // Collision detection
    bool checkCollision(const GameObject& other) const;

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_rotation;
    sf::Vector2f m_size;
};

