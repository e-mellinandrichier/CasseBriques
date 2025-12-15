#include "GameObject.hpp"
#include <cmath>

GameObject::GameObject(float x, float y, float width, float height)
    : m_position(x, y)
    , m_velocity(0.f, 0.f)
    , m_rotation(0.f)
    , m_size(width, height)
{
}

void GameObject::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void GameObject::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;
}

void GameObject::setVelocity(float x, float y)
{
    m_velocity.x = x;
    m_velocity.y = y;
}

void GameObject::setVelocity(const sf::Vector2f& vel)
{
    m_velocity = vel;
}

void GameObject::setRotation(float angle)
{
    m_rotation = angle;
}

void GameObject::rotate(float angle)
{
    m_rotation += angle;
}

void GameObject::setSize(float width, float height)
{
    m_size.x = width;
    m_size.y = height;
}

sf::FloatRect GameObject::getAABB() const
{
    return sf::FloatRect(m_position.x, m_position.y, m_size.x, m_size.y);
}

void GameObject::update(float deltaTime)
{
    m_position += m_velocity * deltaTime;
}

bool GameObject::checkCollision(const GameObject& other) const
{
    return getAABB().intersects(other.getAABB());
}

