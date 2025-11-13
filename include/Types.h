#ifndef TYPES_H
#define TYPES_H

#include <SFML/Graphics.hpp>

// shape type for GameObject rendering
enum class ShapeType
{
    CIRCLE,
    RECTANGLE
};

// axis-aligned bounding box for collision detection
struct AABB
{
    float x, y;           // Top-left corner
    float width, height;  // Dimensions

    // get bounding box edges
    float left() const { return x; }
    float right() const { return x + width; }
    float top() const { return y; }
    float bottom() const { return y + height; }

    // get center point
    sf::Vector2f center() const { return sf::Vector2f(x + width / 2.0f, y + height / 2.0f); }

    // check if point is inside
    bool contains(const sf::Vector2f& point) const
    {
        return point.x >= left() && point.x <= right() &&
               point.y >= top() && point.y <= bottom();
    }
};

#endif // TYPES_H
