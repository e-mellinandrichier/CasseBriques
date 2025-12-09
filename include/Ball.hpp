#pragma once

#include "GameObject.hpp"
#include "Paddle.hpp"
#include "Brick.hpp"
#include <SFML/Graphics.hpp>

class Ball : public GameObject {

public:
    Ball(const sf::Texture& texture, float X, float Y);

    void update(float time) override;

    void setSpeed(float speed);
    float getSpeed() const;

    void checkCollisionPaddle(const Paddle& paddle);
    sf::FloatRect getHitbox() const;

    bool checkCollisionBrick(Brick& brick);

private:
    float speed;
    sf::Vector2f direction;
    void reverseY();
};
