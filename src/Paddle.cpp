#include "Paddle.h"

Paddle::Paddle(float x, float y, float width, float height)
    : GameObject(x, y, width, height)
{
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setPosition(x, y);
    m_shape.setFillColor(sf::Color::White);
    m_shape.setOutlineColor(sf::Color::Cyan);
    m_shape.setOutlineThickness(2.f);
}

void Paddle::update(float deltaTime)
{
    // Apply movement
    m_velocity.x = m_moveSpeed;
    GameObject::update(deltaTime);
    
    // Update shape position
    m_shape.setPosition(m_position.x, m_position.y);
}

void Paddle::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

void Paddle::moveLeft(float speed)
{
    m_moveSpeed = -speed;
    if (m_moveSpeed < -m_maxSpeed)
    {
        m_moveSpeed = -m_maxSpeed;
    }
}

void Paddle::moveRight(float speed)
{
    m_moveSpeed = speed;
    if (m_moveSpeed > m_maxSpeed)
    {
        m_moveSpeed = m_maxSpeed;
    }
}

void Paddle::stop()
{
    m_moveSpeed = 0.f;
}

