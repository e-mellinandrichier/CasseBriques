#include "Brick.hpp"
#include <algorithm>

Brick::Brick(float x, float y, float width, float height, int maxHealth)
    : GameObject(x, y, width, height)
    , m_health(maxHealth)
    , m_maxHealth(maxHealth)
{
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setPosition(x, y);
    m_shape.setFillColor(getColorForHealth());
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setOutlineThickness(1.f);
}

void Brick::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health < 0)
    {
        m_health = 0;
    }
    m_shape.setFillColor(getColorForHealth());
}

void Brick::destroy()
{
    m_health = 0;
}

void Brick::update(float deltaTime)
{
    GameObject::update(deltaTime);
    m_shape.setPosition(m_position.x, m_position.y);
}

void Brick::draw(sf::RenderWindow& window) const
{
    if (!isDestroyed())
    {
        window.draw(m_shape);
    }
}

sf::Color Brick::getColorForHealth() const
{
    if (m_health <= 0)
    {
        return sf::Color::Transparent;
    }

    float healthRatio = static_cast<float>(m_health) / static_cast<float>(m_maxHealth);
    
    // Color gradient: Red (low health) -> Yellow -> Green (high health)
    if (healthRatio > 0.66f)
    {
        // Green
        return sf::Color(0, 255, 0);
    }
    else if (healthRatio > 0.33f)
    {
        // Yellow
        return sf::Color(255, 255, 0);
    }
    else
    {
        // Red
        return sf::Color(255, 0, 0);
    }
}

