#include "../include/Brick.hpp"

Brick::Brick(const sf::Texture& texture, float X, float Y, BrickType brickType)
    : GameObject(texture), type(brickType), life(brickType), maxLife(brickType), destroyed(false)
{
    sprite.setPosition(X,Y);
    sprite.setScale(0.13f,0.13f);
    updateColor();
}

void Brick::update(float time)
{

}

void Brick::hit()
{
    life--;
    if(life <= 0)
    {
        destroyed = true;
    }
    else
    {
        updateColor();
    }
}

bool Brick::isDestroyed() const
{
    return destroyed;
}

int Brick::getLife() const
{
    return life;
}

int Brick::getMaxLife() const
{
    return maxLife;
}

int Brick::getScoreValue() const
{
    return type * 10;
}

void Brick::updateColor()
{
    sf::Color color;
    
    switch(type)
    {
        case NORMAL:
            color = sf::Color::White;
            break;
        case REINFORCED:
            color = (life == 2) ? sf::Color::Yellow : sf::Color(255, 165, 0);
            break;
        case SOLID:
            if(life == 3) color = sf::Color::Red;
            else if(life == 2) color = sf::Color(255, 100, 100);
            else color = sf::Color(255, 150, 150);
            break;
    }
    
    sprite.setColor(color);
}