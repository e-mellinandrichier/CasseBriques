#include "InputManager.h"

InputManager& InputManager::getInstance()
{
    static InputManager instance;
    return instance;
}

void InputManager::processEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto it = m_keyBindings.find(event.key.code);
        if (it != m_keyBindings.end())
        {
            for (const auto& callback : it->second)
            {
                callback();
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        auto it = m_mouseBindings.find(event.mouseButton.button);
        if (it != m_mouseBindings.end())
        {
            m_mousePosition.x = event.mouseButton.x;
            m_mousePosition.y = event.mouseButton.y;
            for (const auto& callback : it->second)
            {
                callback(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        m_mousePosition.x = event.mouseMove.x;
        m_mousePosition.y = event.mouseMove.y;
    }
}

void InputManager::bindKey(sf::Keyboard::Key key, KeyCallback callback)
{
    m_keyBindings[key].push_back(callback);
}

void InputManager::unbindKey(sf::Keyboard::Key key)
{
    m_keyBindings.erase(key);
}

void InputManager::bindMouseButton(sf::Mouse::Button button, MouseCallback callback)
{
    m_mouseBindings[button].push_back(callback);
}

void InputManager::unbindMouseButton(sf::Mouse::Button button)
{
    m_mouseBindings.erase(button);
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key) const
{
    return sf::Keyboard::isKeyPressed(key);
}

