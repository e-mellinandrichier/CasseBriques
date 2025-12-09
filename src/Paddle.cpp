#include "../include/Paddle.hpp"
#include <SFML/Window/Keyboard.hpp>

Paddle::Paddle(const sf::Texture& texture, float X, float Y)
    : GameObject(texture), speed(300.f)
{
    sprite.setPosition(X, Y);
    sprite.setScale(0.15f,0.15f);
}

void Paddle::update(float time)
{
    float move = 0.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move -= speed * time;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move += speed * time;
    }

    sf::Vector2f pos = sprite.getPosition();
    pos.x += move;

    if (pos.x < 0) pos.x = 0;
    if (pos.x + sprite.getGlobalBounds().width > 1024)
        pos.x = 1024 - sprite.getGlobalBounds().width;

    sprite.setPosition(pos);
}

void Paddle::setSpeed(float s)
{
    speed = s;
}

float Paddle::getSpeed() const
{
    return speed;
}