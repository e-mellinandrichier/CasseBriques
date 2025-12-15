#pragma once

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Paddle : public GameObject {

public:
    Paddle(const sf::Texture& texture, float X, float Y);

    void update(float time) override;

    void setSpeed(float speed);
    float getSpeed() const;

private:
    float speed;

};