#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject(const sf::Texture& texture);

    virtual ~GameObject() = default;

    virtual void update(float time) {}

    virtual void draw(sf::RenderWindow& window);

    sf::FloatRect getHitbox() const;

protected:
    sf::Sprite sprite;
};
