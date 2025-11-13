#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <functional>

// typedef for input callback functions
using InputCallback = std::function<void()>;

// singleton input manager
// handles keyboard and mouse input events
// allows registering callbacks for specific input actions
class InputManager
{
public:
    // get singleton instance
    // RETURN: reference to the global InputManager instance
    static InputManager& getInstance();

    // delete copy constructor and assignment (singleton)
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    // poll events from SFML window
    // PRE: window is valid and open
    // POST: internal state updated, callbacks executed for new events
    void update(const sf::RenderWindow& window);

    // register callback for key press event
    // PRE: callback is valid function
    // POST: callback will execute when key is pressed
    void registerKeyCallback(sf::Keyboard::Key key, InputCallback callback);

    // register callback for mouse button press
    // PRE: callback is valid function
    // POST: callback will execute when mouse button is pressed
    void registerMouseCallback(sf::Mouse::Button button, InputCallback callback);

    // check if a key is currently pressed
    // RETURN: true if key is pressed in this frame, false otherwise
    bool isKeyPressed(sf::Keyboard::Key key) const;

    // check if a key was held from previous frame
    // RETURN: true if key was pressed last frame
    bool wasKeyPressed(sf::Keyboard::Key key) const;

    // check if mouse button is pressed
    // RETURN: true if button pressed in this frame
    bool isMouseButtonPressed(sf::Mouse::Button button) const;

    // get current mouse position in window
    // RETURN: mouse position as Vector2f
    sf::Vector2f getMousePosition() const;

    // check if window should close
    // RETURN: true if close event received
    bool shouldWindowClose() const;

private:
    // private constructor (singleton)
    InputManager();

    // process a single SFML event
    // PRE: event is valid
    // POST: internal state updated, relevant callbacks executed
    void processEvent(const sf::Event& event);

    // data members
    std::map<sf::Keyboard::Key, bool> currentKeyPressed;   // keys pressed this frame
    std::map<sf::Keyboard::Key, bool> previousKeyPressed;  // keys pressed last frame
    std::map<sf::Keyboard::Key, std::vector<InputCallback>> keyCallbacks;
    std::map<sf::Mouse::Button, bool> currentMousePressed;
    std::map<sf::Mouse::Button, std::vector<InputCallback>> mouseCallbacks;
    sf::Vector2f mousePosition;
    bool windowShouldClose;
};

#endif // INPUT_MANAGER_H
