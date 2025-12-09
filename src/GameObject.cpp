#include "../include/GameObject.hpp"

GameObject::GameObject(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void GameObject::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect GameObject::getHitbox() const {
    return sprite.getGlobalBounds();
}
