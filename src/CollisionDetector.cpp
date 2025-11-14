#include "CollisionDetector.h"
#include "GameObject.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// AABB-to-AABB collision detection
bool CollisionDetector::checkAABB(const AABB& box1, const AABB& box2)
{
    // Check overlap on both X and Y axes (separating axis theorem)
    // Two boxes collide if they overlap on ALL axes
    
    // bool xOverlap = (box1.left < box2.right && box1.right > box2.left)
    // bool yOverlap = (box1.top < box2.bottom && box1.bottom > box2.top)
    
    // return (xOverlap && yOverlap)
    
    return false; // Placeholder
}

// AABB collision with GameObjects
bool CollisionDetector::checkAABB(const GameObject& obj1, const GameObject& obj2)
{
    // Get collision boxes from both objects
    // return checkAABB(obj1.getCollisionBox(), obj2.getCollisionBox())
    
    return false; // Placeholder
}

// Circle-to-AABB collision detection
bool CollisionDetector::checkCircleAABB(const sf::Vector2f& circleCenter,
                                        float radius,
                                        const AABB& box)
{
    // Find the closest point on the box to the circle center
    // sf::Vector2f closestPoint = getClosestPointOnAABB(circleCenter, box)
    
    // Calculate distance from circle center to closest point
    // float distance = length(circleCenter - closestPoint)
    // or:
    // float dx = circleCenter.x - closestPoint.x
    // float dy = circleCenter.y - closestPoint.y
    // float distance = sqrt(dx*dx + dy*dy)
    
    // Collision occurs if distance <= radius
    // return (distance <= radius)
    
    return false; // Placeholder
}

// Circle-to-AABB collision with GameObjects
bool CollisionDetector::checkCircleAABB(const GameObject& circle, const GameObject& box)
{
    // Assume circle is CIRCLE type, box is RECTANGLE type
    // Extract circle radius (half of width or height, both equal for circle)
    // float radius = circle.getSize().x / 2.0f
    
    // Call the point/radius version
    // return checkCircleAABB(circle.getPosition(), radius, box.getCollisionBox())
    
    return false; // Placeholder
}

// Get collision normal (direction of impact)
sf::Vector2f CollisionDetector::getCollisionNormal(const AABB& box1, const AABB& box2)
{
    // Find center of each box
    // sf::Vector2f center1(box1.x + box1.width/2, box1.y + box1.height/2)
    // sf::Vector2f center2(box2.x + box2.width/2, box2.y + box2.height/2)
    
    // calculate vector from box1 to box2
    // sf::Vector2f direction = center2 - center1
    
    // determine which axis has more overlap to know contact normal
    // calculate overlaps on X and Y axes
    // float xOverlap = ...
    // float yOverlap = ...
    
    // if X overlap is less, normal is horizontal
    // if Y overlap is less, normal is vertical
    
    // normalize the result to length 1.0
    // return normalized(direction)
    
    return sf::Vector2f(0.0f, 0.0f); // placeholder
}

// find closest point on AABB to external point
sf::Vector2f CollisionDetector::getClosestPointOnAABB(const sf::Vector2f& point,
                                                      const AABB& box)
{
    // clamp point X coordinate to box X range [box.left, box.right]
    // float closestX = std::clamp(point.x, box.left(), box.right())
    
    // clamp point Y coordinate to box Y range [box.top, box.bottom]
    // float closestY = std::clamp(point.y, box.top(), box.bottom())
    
    // return {closestX, closestY}
    // this gives the closest point on the box boundary to the external point
    
    return point; // placeholder
}

// helper: calculate overlap on single axis
float CollisionDetector::getAxisOverlap(float min1, float max1, float min2, float max2)
{
    // calculate overlap between two 1D ranges
    // If ranges don't overlap, return 0 (or negative to indicate separation)
    
    // float overlapStart = std::max(min1, min2)
    // float overlapEnd = std::min(max1, max2)
    
    // if (overlapEnd < overlapStart)
    //     return 0  // no overlap
    
    // return (overlapEnd - overlapStart)  // overlap amount
    
    return 0.0f; // placeholder
}
