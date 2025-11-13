#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Constants.h"

class GameObject;

// main game class
// manages the game window, game loop, and all game objects
class Game
{
public:
    // constructor
    // game object created but not initialized
    Game();

    // destructor
    // all resources cleaned up
    ~Game();

    // initialize the game
    void init();

    // run the main game loop
    void run();

    // stop the game loop
    // isRunning set to false, loop will exit
    void quit();

    // add a game object to the scene
    void addGameObject(GameObject* obj);

    // remove a game object from the scene
    void removeGameObject(GameObject* obj);

private:
    // initialize test objects for a demo
    void initializeTestObjects();

    // update all game objects
    void update(float deltaTime);

    // render all game objects
    void render();

    // check collisions between all objects (for debugging)
    void checkCollisions();

    // data members
    sf::RenderWindow window;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    bool isRunning;
    float deltaTime;

    // frame timing
    sf::Clock frameClock;  // tracks time between frames
    int frameCount;        // for FPS counter
    sf::Clock fpsClock;    // for measuring FPS
};

#endif // GAME_H
