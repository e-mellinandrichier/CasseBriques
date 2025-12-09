#include <iostream>
#include "../include/Ball.hpp"
#include "../include/Brick.hpp"
#include <cmath>


Ball::Ball(const sf::Texture& texture, float X, float Y)
    : GameObject(texture), speed (250.f), direction(0.7f,1.0f)
{
    sprite.setPosition(X,Y);
    sprite.setScale(0.08f,0.08f);
}


void Ball::update(float time)
{
    float move = speed * time; 

    sf::Vector2f pos = sprite.getPosition();
    pos.x += direction.x * move;
    pos.y += direction.y * move;

    if(pos.x <= 0 || pos.x + sprite.getGlobalBounds().width >= 1024)
    direction.x = -direction.x;

    if(pos.y <= 0 || pos.y + sprite.getGlobalBounds().height >= 768)
    direction.y = -direction.y;

    sprite.setPosition(pos);
}

void Ball::setSpeed(float s)
{
    speed = s;
}

float Ball::getSpeed() const
{
    return speed;
}

void Ball::checkCollisionPaddle(const Paddle& paddle) {
    if (sprite.getGlobalBounds().intersects(paddle.getHitbox())) {
        
        float paddleCenter = paddle.getHitbox().left + paddle.getHitbox().width / 2.f;

        float ballCenter = sprite.getPosition().x + sprite.getGlobalBounds().width / 2.f;
        
        float offset = (ballCenter - paddleCenter) / (paddle.getHitbox().width / 2.f);

        direction.x = offset;
        
        direction.y *= -1;
        
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;
        sf::Vector2f pos = sprite.getPosition();
        pos.y = paddle.getHitbox().top - sprite.getGlobalBounds().height;
        sprite.setPosition(pos);
    }
}

bool Ball::checkCollisionBrick(Brick& brick) {
    if(brick.isDestroyed()) return false;
    
    sf::FloatRect ballRect = sprite.getGlobalBounds();
    sf::FloatRect brickRect = brick.getHitbox();
    sf::FloatRect intersection;

    if (ballRect.intersects(brickRect, intersection)) {
        brick.hit();
        
        float brickCenter = brickRect.left + brickRect.width / 2.f;
        float ballCenter  = ballRect.left + ballRect.width / 2.f;
        float offset = 0.f;

        if (brickRect.width > 0.f)
            offset = (ballCenter - brickCenter) / (brickRect.width / 2.f);

        offset = std::clamp(offset, -1.f, 1.f);

        direction.x = offset;

        bool hitFromTop = (ballRect.top + ballRect.height) <= (brickRect.top + intersection.height / 2.f);
        bool hitFromBottom = (ballRect.top) >= (brickRect.top + brickRect.height - intersection.height / 2.f);

        if (hitFromTop) {
            direction.y = -std::abs(direction.y);

            sprite.setPosition(ballRect.left, brickRect.top - ballRect.height - 0.01f);
        }
        else if (hitFromBottom) {
            direction.y = std::abs(direction.y);

            sprite.setPosition(ballRect.left, brickRect.top + brickRect.height + 0.01f);
        }
        else {
            direction.y = -direction.y;
        }

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.f) {
            direction.x /= length;
            direction.y /= length;
        }
        
        return true;
    }
    
    return false;
}

void Ball::reverseY() {
    direction.y = -direction.y;
}

sf::FloatRect Ball::getHitbox() const {
    return sprite.getGlobalBounds();
}