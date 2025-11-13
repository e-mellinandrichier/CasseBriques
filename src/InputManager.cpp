#include "InputManager.h"
#include <iostream>

// static instance getter (singleton pattern)
InputManager& InputManager::getInstance()
{
    // create static instance on first call
    // static InputManager instance;
    // return instance;
    
    // this creates a single global InputManager that persists
    // first call: constructor runs
    // subsequent calls: returns existing instance
}

// private constructor
InputManager::InputManager()
    : mousePosition(0.0f, 0.0f),
      windowShouldClose(false)
{
    // initialize all containers (maps, vectors)
    // log "InputManager initialized"
}

// update input state from SFML window
void InputManager::update(const sf::RenderWindow& window)
{
    // save previous frame key states
    // previousKeyPressed = currentKeyPressed
    
    // clear current frame pressed keys
    // for (auto& pair : currentKeyPressed)
    //     pair.second = false
    
    // poll all pending events from window
    // sf::Event event;
    // while (window.pollEvent(event))
    //     processEvent(event)
    
    // update mouse position from current window
    // mousePosition = sf::Mouse::getPosition(window)  // Screen coords
    // or
    // mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window))  // World coords
}

// process a single SFML event
void InputManager::processEvent(const sf::Event& event)
{
    // handle different event types
    
    // if (event.type == sf::Event::Closed)
    //     windowShouldClose = true
    
    // if (event.type == sf::Event::KeyPressed)
    //     currentKeyPressed[event.key.code] = true
    //     Execute all callbacks for this key:
    //     for (auto& callback : keyCallbacks[event.key.code])
    //         callback()
    
    // if (event.type == sf::Event::MouseButtonPressed)
    //     currentMousePressed[event.mouseButton.button] = true
    //     Execute all callbacks for this button:
    //     for (auto& callback : mouseCallbacks[event.mouseButton.button])
    //         callback()
    
    // if (event.type == sf::Event::MouseButtonReleased)
    //     currentMousePressed[event.mouseButton.button] = false
}

// register callback for key press
void InputManager::registerKeyCallback(sf::Keyboard::Key key, InputCallback callback)
{
    // add callback to keyCallbacks[key] vector
    // keyCallbacks[key].push_back(callback)
    // log "Callback registered for key"
}

// register callback for mouse button
void InputManager::registerMouseCallback(sf::Mouse::Button button, InputCallback callback)
{
    // add callback to mouseCallbacks[button] vector
    // mouseCallbacks[button].push_back(callback)
    // log "Callback registered for mouse button"
}

// check if key is pressed this frame
bool InputManager::isKeyPressed(sf::Keyboard::Key key) const
{
    // return true if key in currentKeyPressed and value is true
    // if (currentKeyPressed.count(key))
    //     return currentKeyPressed.at(key)
    // return false
}

// check if key was pressed last frame
bool InputManager::wasKeyPressed(sf::Keyboard::Key key) const
{
    // return true if key in previousKeyPressed and value is true
    // if (previousKeyPressed.count(key))
    //     return previousKeyPressed.at(key)
    // return false
}

// check if mouse button is pressed
bool InputManager::isMouseButtonPressed(sf::Mouse::Button button) const
{
    // return true if button in currentMousePressed and value is true
    // if (currentMousePressed.count(button))
    //     return currentMousePressed.at(button)
    // return false
}

// get mouse position
sf::Vector2f InputManager::getMousePosition() const
{
    return mousePosition;
}

// check if window should close
bool InputManager::shouldWindowClose() const
{
    return windowShouldClose;
}
