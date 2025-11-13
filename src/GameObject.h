#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <Types.h>

// base class for all game objects
// handles positioning, velocity, rendering, and collision
class GameObject
{
public:
    // constructor with position, size, and shape type
    GameObject(float x, float y, float width, float height, ShapeType shape);

    // virtual destructor for proper cleanup in inheritance
    virtual ~GameObject();

    // update position based on velocity and delta time
    virtual void update(float deltaTime);

    // render the object to the given window
    virtual void render(sf::RenderWindow& window);

    // getters
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    float getRotation() const;
    sf::Vector2f getSize() const;
    sf::Color getColor() const;
    AABB getCollisionBox() const;
    ShapeType getShapeType() const;

    // setters
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);
    void setVelocity(float vx, float vy);
    void setVelocity(const sf::Vector2f& vel);
    void setRotation(float angleDegrees);
    void setColor(const sf::Color& color);
    void setSize(float width, float height);

    // add velocity (for acceleration)
    // velocity += (vx, vy)
    void addVelocity(float vx, float vy);

    // rotate by angle (cumulative)
    // rotation += angleDegrees
    void rotate(float angleDegrees);

protected:
    // update the collision box based on current position and size
    void updateCollisionBox();

    // protected members for subclasses to use
    sf::Vector2f position;      // center of object (x, y)
    sf::Vector2f velocity;      // velocity vector (vx, vy) in pixels/second
    float rotation;             // rotation in degrees
    sf::Vector2f size;          // width and height
    sf::Color color;            // draw color
    ShapeType shapeType;        // CIRCLE or RECTANGLE
    AABB collisionBox;          // bounding box for collision detection

private:
    // SFML shape objects (only created once, reused each render)
    // mutable means they can be modified in const methods
    mutable sf::CircleShape circleShape;
    mutable sf::RectangleShape rectangleShape;
    mutable bool shapesInitialized;

    // initialize shape objects (called once on first render)
    void initializeShapes();
};

#endif // GAME_OBJECT_H
