#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <SFML/Graphics.hpp>
#include "Types.h"

class GameObject;

// utility class for collision detection
// all methods are static (no instance needed)
class CollisionDetector
{
public:
    // deleted constructor (pure utility class)
    CollisionDetector() = delete;

    // check AABB-to-AABB collision
    // PRE: both AABB objects valid
    // RETURN: true if boxes overlap, false otherwise
    // NOTES: uses separating axis theorem for axis-aligned boxes
    static bool checkAABB(const AABB& box1, const AABB& box2);

    // check AABB-to-AABB collision with GameObjects
    // PRE: both GameObjects valid
    // RETURN: true if collision boxes overlap
    static bool checkAABB(const GameObject& obj1, const GameObject& obj2);

    // check circle-to-AABB collision
    // PRE: circlePos valid, radius > 0, box valid
    // RETURN: true if circle overlaps with box
    // NOTES: finds closest point on box to circle center,
    //        returns true if distance <= radius
    static bool checkCircleAABB(const sf::Vector2f& circleCenter,
                                float radius,
                                const AABB& box);

    // check circle-to-AABB collision (object-based)
    // PRE: circle object is CIRCLE type, box object is RECTANGLE type
    // RETURN: true if collision detected
    static bool checkCircleAABB(const GameObject& circle, const GameObject& box);

    // get collision normal (direction of impact)
    // PRE: boxes are currently colliding
    // RETURN: normalized vector pointing from box1 toward box2
    // NOTES: used for bounce calculations in physics
    static sf::Vector2f getCollisionNormal(const AABB& box1, const AABB& box2);

    // find closest point on box to external point
    // PRE: point is external point, box is AABB
    // RETURN: closest point on box boundary to the given point
    // NOTES: useful for circle-box collision, may be inside or on boundary
    static sf::Vector2f getClosestPointOnAABB(const sf::Vector2f& point,
                                               const AABB& box);

private:
    // helper: calculate overlap on single axis
    // returns: amount of overlap (positive = overlapping, zero = touching, negative = separated)
    static float getAxisOverlap(float min1, float max1, float min2, float max2);
};

#endif // COLLISION_DETECTOR_H
