#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Brick : public GameObject
{
public:
    Brick(float x, float y, float width, float height, int maxHealth = 1);

    int getHealth() const { return m_health; }
    int getMaxHealth() const { return m_maxHealth; }
    bool isDestroyed() const { return m_health <= 0; }

    void takeDamage(int damage = 1);
    void destroy();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

private:
    int m_health;
    int m_maxHealth;
    sf::RectangleShape m_shape;

    sf::Color getColorForHealth() const;
};

