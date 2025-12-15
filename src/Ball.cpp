#include "Ball.h"
#include <cmath>
#include <algorithm>

Ball::Ball(float x, float y, float radius, const sf::Vector2f& velocity)
    : GameObject(x, y, radius * 2.f, radius * 2.f)
    , m_radius(radius)
    , m_speed(std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y))
{
    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition(x + radius, y + radius);
    
    // Normalize velocity and scale by speed
    float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (length > 0.f)
    {
        m_velocity = sf::Vector2f(velocity.x / length * m_speed, velocity.y / length * m_speed);
    }
}

void Ball::update(float deltaTime)
{
    // Apply gravity only if enabled
    if (m_gravityEnabled)
    {
        m_velocity.y += m_gravity * deltaTime;
    }
    
    GameObject::update(deltaTime);
    m_shape.setPosition(m_position.x + m_radius, m_position.y + m_radius);
}

void Ball::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

void Ball::bounceOffWalls(float windowWidth, float windowHeight)
{
    float centerX = m_position.x + m_radius;
    float centerY = m_position.y + m_radius;

    // Left wall
    if (centerX - m_radius <= 0.f && m_velocity.x < 0.f)
    {
        m_velocity.x = -m_velocity.x;
        m_position.x = m_radius;
    }
    // Right wall
    else if (centerX + m_radius >= windowWidth && m_velocity.x > 0.f)
    {
        m_velocity.x = -m_velocity.x;
        m_position.x = windowWidth - m_radius * 2.f;
    }
    // Top wall
    if (centerY - m_radius <= 0.f && m_velocity.y < 0.f)
    {
        m_velocity.y = -m_velocity.y;
        m_position.y = m_radius;
    }
}

bool Ball::isOutOfBounds(float windowHeight) const
{
    return m_position.y + m_radius * 2.f > windowHeight;
}

sf::Vector2f Ball::getCenter() const
{
    return sf::Vector2f(m_position.x + m_radius, m_position.y + m_radius);
}

bool Ball::checkCollisionWithAABB(const sf::FloatRect& aabb)
{
    sf::Vector2f center = getCenter();
    
    // Find closest point on AABB to circle center
    float closestX = std::max(aabb.left, std::min(center.x, aabb.left + aabb.width));
    float closestY = std::max(aabb.top, std::min(center.y, aabb.top + aabb.height));
    
    // Calculate distance from circle center to closest point
    float dx = center.x - closestX;
    float dy = center.y - closestY;
    float distanceSquared = dx * dx + dy * dy;
    
    return distanceSquared < (m_radius * m_radius);
}

void Ball::handleCollisionWithAABB(const sf::FloatRect& aabb)
{
    sf::Vector2f center = getCenter();
    sf::Vector2f aabbCenter(aabb.left + aabb.width / 2.f, aabb.top + aabb.height / 2.f);
    
    // Determine collision side
    float dx = center.x - aabbCenter.x;
    float dy = center.y - aabbCenter.y;
    
    float overlapX = m_radius + aabb.width / 2.f - std::abs(dx);
    float overlapY = m_radius + aabb.height / 2.f - std::abs(dy);
    
    if (overlapX < overlapY)
    {
        // Horizontal collision
        m_velocity.x = -m_velocity.x;
        if (dx > 0)
        {
            m_position.x = aabb.left + aabb.width + m_radius;
        }
        else
        {
            m_position.x = aabb.left - m_radius * 2.f;
        }
    }
    else
    {
        // Vertical collision
        m_velocity.y = -m_velocity.y;
        if (dy > 0)
        {
            m_position.y = aabb.top + aabb.height + m_radius;
        }
        else
        {
            m_position.y = aabb.top - m_radius * 2.f;
        }
    }
}

