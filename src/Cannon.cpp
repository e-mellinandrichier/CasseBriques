#include "Cannon.h"
#include <cmath>

Cannon::Cannon(float x, float y, float width, float height)
    : GameObject(x, y, width, height)
{
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setOrigin(width / 2.f, height);
    m_shape.setPosition(x + width / 2.f, y + height);
    m_shape.setFillColor(sf::Color::White);

    m_base.setRadius(width / 2.f);
    m_base.setOrigin(width / 2.f, width / 2.f);
    m_base.setPosition(x + width / 2.f, y + height);
    m_base.setFillColor(sf::Color(128, 128, 128));
}

void Cannon::update(float deltaTime)
{
    GameObject::update(deltaTime);
    m_shape.setPosition(m_position.x + m_size.x / 2.f, m_position.y + m_size.y);
    m_base.setPosition(m_position.x + m_size.x / 2.f, m_position.y + m_size.y);
}

void Cannon::aimAt(float targetX, float targetY)
{
    float centerX = m_position.x + m_size.x / 2.f;
    float centerY = m_position.y + m_size.y;

    float dx = targetX - centerX;
    float dy = targetY - centerY;

    m_rotation = std::atan2(dy, dx) * 180.f / 3.14159265f;
    m_shape.setRotation(m_rotation);
}

void Cannon::aimAt(const sf::Vector2f& target)
{
    aimAt(target.x, target.y);
}

sf::Vector2f Cannon::getDirection() const
{
    float angleRad = m_rotation * 3.14159265f / 180.f;
    return sf::Vector2f(std::cos(angleRad), std::sin(angleRad));
}

void Cannon::draw(sf::RenderWindow& window) const
{
    window.draw(m_base);
    window.draw(m_shape);
}

