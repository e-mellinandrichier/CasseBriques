#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Menu.hpp" 


class Paddle; 
class Ball;
class Brick;

class Game {
public:
    enum GameState { MENU, PLAYING, GAME_OVER }; 

    Game();
    ~Game(); 

    int start();

private:
    const int windowWidth = 1024;
    const int windowHeight = 768;

    sf::RenderWindow window;
    sf::Clock clock;
    sf::Font font;
    sf::Texture paddleTexture;
    sf::Texture ballTexture;
    sf::Texture brickTexture;

    Paddle* paddle;
    Ball* ball;
    std::vector<Brick*> bricks;
    Menu* menu;

    GameState state;
    int lives;
    int score;
    
    sf::Text livesText;
    sf::Text scoreText;
    sf::Text gameOverText;

    void events();
    void handleMenuEvents(sf::Event& event);
    void handleGameEvents(sf::Event& event);
    void handleGameOverEvents(sf::Event& event);
    void update(float time);
    void updateMenu(float time);
    void draw();
    void drawMenu();
    void drawGame();
    void drawGameOver();
    void createBricks();
    void resetBall();
    void checkGameOver();
    void startGame();
    void resetGame();
    void createParticles();

};