#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "CollisionDetector.h"
#include <Constants.h>
#include <iostream>
#include <chrono>

// constructor
Game::Game()
    : window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT),
             Constants::WINDOW_TITLE),
      isRunning(false),
      deltaTime(0.0f),
      frameCount(0)
{
    // set window settings
    // window.setFramerateLimit(60)  // cap FPS
    // log "game constructed"
}

// destructor
Game::~Game()
{
    // gameObjects will auto-delete via unique_ptr
    // log "game destroyed"
}

// initialize the game
void Game::init()
{
    // log "initializing game..."
    
    // initialize InputManager
    // InputManager& input = InputManager::getInstance()
    // input.registerKeyCallback(sf::Keyboard::Right, [this]() { /* ... */ })
    // input.registerKeyCallback(sf::Keyboard::Left, [this]() { /* ... */ })
    
    // create test objects
    initializeTestObjects();
    
    // reset game state
    isRunning = true;
    deltaTime = 0.0f;
    frameCount = 0;
    
    // log "game initialized successfully"
}

// initialize test objects for demo
void Game::initializeTestObjects()
{
    // create several test GameObjects with different shapes/colors
    
    // create a red circle in the center
    // auto circle = std::make_unique<GameObject>(
    //     Constants::WINDOW_WIDTH / 2.0f,
    //     Constants::WINDOW_HEIGHT / 2.0f,
    //     50.0f, 50.0f,
    //     ShapeType::CIRCLE
    // );
    // circle->setColor(sf::Color::Red);
    // circle->setVelocity(100.0f, 50.0f);  // move right and down
    // addGameObject(circle.release());
    
    // create a blue rectangle on the left
    // auto rect = std::make_unique<GameObject>(
    //     200.0f, 300.0f,
    //     60.0f, 60.0f,
    //     ShapeType::RECTANGLE
    // );
    // rect->setColor(sf::Color::Blue);
    // rect->setVelocity(75.0f, -50.0f);  // move right and up
    // addGameObject(rect.release());
    
    // create a green rectangle on the right
    // auto rect2 = std::make_unique<GameObject>(
    //     600.0f, 150.0f,
    //     80.0f, 40.0f,
    //     ShapeType::RECTANGLE
    // );
    // rect2->setColor(sf::Color::Green);
    // rect2->setVelocity(-100.0f, 0.0f);  // move left
    // addGameObject(rect2.release());
    
    // log "test objects created"
}

// main game loop
void Game::run()
{
    // log "starting game loop..."
    
    // while (window.isOpen() && isRunning)
    
    //     // Calculate delta time
    //     deltaTime = frameClock.restart().asSeconds();
    //     // Clamp to prevent huge jumps (e.g., if window was dragged)
    //     if (deltaTime > 0.05f) deltaTime = 0.05f;
    
    //     // update input
    //     InputManager& input = InputManager::getInstance();
    //     input.update(window);
    
    //     if (input.shouldWindowClose())
    //         break;
    
    //     // update game state
    //     update(deltaTime);
    
    //     // check collisions (optional debug)
    //     checkCollisions();
    
    //     // render
    //     render();
    
    //     // FPS counter
    //     frameCount++;
    //     if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
    //         // log FPS
    //         frameCount = 0;
    //         fpsClock.restart();
    
    // log "game loop ended"
}

// update all game objects
void Game::update(float deltaTime)
{
    // for (auto& obj : gameObjects)
    //     obj->update(deltaTime);
}

// render all game objects
void Game::render()
{
    // window.clear(sf::Color::Black);
    
    // for (auto& obj : gameObjects)
    //     obj->render(window);
    
    // optional: draw debug information
    // if (Constants::DEBUG_COLLISION)
    //     draw collision boxes for each object in different color
    
    // window.display();
}

// check collisions between all objects
void Game::checkCollisions()
{
    // if (!Constants::DEBUG_COLLISION)
    //     return;
    
    // for (size_t i = 0; i < gameObjects.size(); i++)
    //     for (size_t j = i + 1; j < gameObjects.size(); j++)
    //         if (CollisionDetector::checkAABB(*gameObjects[i], *gameObjects[j]))
    //             std::cout << "Collision between object " << i << " and " << j << std::endl;
}

// add game object to scene
void Game::addGameObject(GameObject* obj)
{
    // if (obj == nullptr)
    //     log warning and return
    
    // gameObjects.push_back(std::unique_ptr<GameObject>(obj));
    // log "object added to scene"
}

// remove game object from scene
void Game::removeGameObject(GameObject* obj)
{
    // find and remove object from gameObjects vector
    // auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
    //     [obj](const auto& ptr) { return ptr.get() == obj; });
    
    // if (it != gameObjects.end())
    //     gameObjects.erase(it);
    //     log "object removed from scene"
}

// quit the game
void Game::quit()
{
    isRunning = false;
}
