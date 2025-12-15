#pragma once

#include <SFML/Window.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

class InputManager
{
public:
    using KeyCallback = std::function<void()>;
    using MouseCallback = std::function<void(int x, int y)>;

    static InputManager& getInstance();

    // Process events (call this in your game loop)
    void processEvent(const sf::Event& event);

    // Keyboard bindings
    void bindKey(sf::Keyboard::Key key, KeyCallback callback);
    void unbindKey(sf::Keyboard::Key key);

    // Mouse bindings
    void bindMouseButton(sf::Mouse::Button button, MouseCallback callback);
    void unbindMouseButton(sf::Mouse::Button button);

    // Check if key is currently pressed
    bool isKeyPressed(sf::Keyboard::Key key) const;

    // Get mouse position
    sf::Vector2i getMousePosition() const { return m_mousePosition; }

private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    std::unordered_map<sf::Keyboard::Key, std::vector<KeyCallback>> m_keyBindings;
    std::unordered_map<sf::Mouse::Button, std::vector<MouseCallback>> m_mouseBindings;
    sf::Vector2i m_mousePosition;
};

