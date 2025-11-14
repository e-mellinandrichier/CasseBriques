#include "GameObject.h"
#include <cmath>
#include <iostream>

// constructor - initialize all members and create SFML shapes
GameObject::GameObject(float x, float y, float width, float height, ShapeType shape)
    : position(x, y),
      velocity(0.0f, 0.0f),
      rotation(0.0f),
      size(width, height),
      color(sf::Color::White),
      shapeType(shape),
      shapesInitialized(false)
{
    // initialize collision box based on size and position
    std::cout << "GameObject created at (" << x << ", " << y << ") with size (" << width << ", " << height << ")" << std::endl;
    updateCollisionBox();
}

// destructor
GameObject::~GameObject()
{
    std::cout << "GameObject destroyed at (" << position.x << ", " << position.y << ")" << std::endl;
}

// update position based on velocity and delta time
void GameObject::update(float deltaTime)
{
    // check deltaTime is valid (>= 0)
    if (deltaTime < 0.0f) {
        std::cerr << "warning: negative deltaTime in GameObject::update" << std::endl;
        return;
    }

    // update position based on velocity and delta time
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    
    // update collision box to match new position
    updateCollisionBox();
}

// render the object
void GameObject::render(sf::RenderWindow& window)
{
    // initialize shapes on first render (lazy initialization)
    if (!shapesInitialized) initializeShapes();
    
    // draw appropriate shape based on shapeType
    // update shape position and rotation to match GameObject
    if (shapeType == ShapeType::CIRCLE) {
        circleShape.setPosition(position.x - size.x/2, position.y - size.y/2);
        circleShape.setRotation(rotation);
        circleShape.setFillColor(color);
        window.draw(circleShape);
    } else {
        rectangleShape.setPosition(position.x - size.x/2, position.y - size.y/2);
        rectangleShape.setRotation(rotation);
        rectangleShape.setFillColor(color); 
        window.draw(rectangleShape);
    }
}

// initialize SFML shapes 
void GameObject::initializeShapes()
{
    if (shapesInitialized) return;  // early exit if already initialized

    switch (shapeType) {
        case ShapeType::CIRCLE:
            circleShape.setRadius(size.x / 2);
            circleShape.setOrigin(size.x / 2, size.y / 2);  // center the origin
            break;
        case ShapeType::RECTANGLE:
            rectangleShape.setSize(sf::Vector2f(size.x, size.y));
            rectangleShape.setOrigin(size.x / 2, size.y / 2);  // center the origin
            break;
        default:
            throw std::runtime_error("invalid shape type");
    }
    
    shapesInitialized = true;
}

// update collision box based on current position and size
void GameObject::updateCollisionBox()
{
    // create AABB that represents the object's bounds
    if (shapeType == ShapeType::CIRCLE) {
        // for circles: box centered on position, size = diameter
        float radius = size.x / 2;
        collisionBox.x = position.x - radius;
        collisionBox.y = position.y - radius;
        collisionBox.width = size.x;
        collisionBox.height = size.y;
    } else {
        // for rectangle: box positioned at position, size = size
        collisionBox.x = position.x - size.x / 2;
        collisionBox.y = position.y - size.y / 2;
        collisionBox.width = size.x;
        collisionBox.height = size.y;
    }
}

// getters
sf::Vector2f GameObject::getPosition() const
{
    return position;
}

sf::Vector2f GameObject::getVelocity() const
{
    return velocity;
}

float GameObject::getRotation() const
{
    return rotation;
}

sf::Vector2f GameObject::getSize() const
{
    return size;
}

sf::Color GameObject::getColor() const
{
    return color;
}

AABB GameObject::getCollisionBox() const
{
    return collisionBox;
}

ShapeType GameObject::getShapeType() const
{
    return shapeType;
}

// setters
void GameObject::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
    updateCollisionBox();
}

void GameObject::setPosition(const sf::Vector2f& pos)
{
    position = pos;
    updateCollisionBox();
}

void GameObject::setVelocity(float vx, float vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

void GameObject::setVelocity(const sf::Vector2f& vel)
{
    velocity = vel;
}

void GameObject::setRotation(float angleDegrees)
{
    rotation = angleDegrees;
    // normalize angle to 0-360 range (optional)
    // while (rotation < 0) rotation += 360
    // while (rotation >= 360) rotation -= 360
}

void GameObject::setColor(const sf::Color& newColor)
{
    color = newColor;
}

void GameObject::setSize(float width, float height)
{
    size.x = width;
    size.y = height;
    updateCollisionBox();
}

// add velocity (for acceleration)
void GameObject::addVelocity(float vx, float vy)
{
    velocity.x += vx;
    velocity.y += vy;
}

// rotate by angle (cumulative)
void GameObject::rotate(float angleDegrees)
{
    rotation += angleDegrees;
    // normalize to 0-360 range if desired
}
