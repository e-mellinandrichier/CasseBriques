#pragma once 

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Brick : public GameObject {

public:
    enum BrickType {
        NORMAL = 1,
        REINFORCED = 2,
        SOLID = 3
    };

    Brick(const sf::Texture& texture, float X, float Y, BrickType type = NORMAL);

    void update(float time) override;

    void hit();
    bool isDestroyed() const;
    int getLife() const;
    int getMaxLife() const;
    int getScoreValue() const;

private:
    int life;
    int maxLife;
    bool destroyed;
    BrickType type;
    
    void updateColor();
};