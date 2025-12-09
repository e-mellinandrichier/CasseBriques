#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "../include/Game.hpp"
#include "../include/Paddle.hpp"
#include "../include/Ball.hpp"
#include "../include/Brick.hpp"
#include "../include/Menu.hpp"


const int windowWidth = 1024;
const int windowHeight = 768;



Game::~Game() 
{
    delete paddle;
    delete ball;
    if(menu) delete menu;
    for(auto brick : bricks)
    {
        delete brick;
    }
}
// **********************************************


Game::Game()
// CORRECTION : Suppression de menuAnimationTime(0.f) qui n'est pas un membre de Game.
: window(sf::VideoMode(windowWidth,windowHeight), "Casse-Briques"), lives(3), score(0), state(MENU) 
{
    window.setFramerateLimit(60);

    if(!paddleTexture.loadFromFile("assets/images/paddle.Png"))
    {
        std::cout << "Erreur de texture du Paddle" << std::endl;
    }

    if(!ballTexture.loadFromFile("assets/images/ball.png"))
    {
        std::cout << "Texture de la Balle pas trouver" << std::endl;
    }

    if(!brickTexture.loadFromFile("assets/images/brick.png"))
    {
        std::cout << "Texture de brick introuvable" << std::endl;
    }

    if(!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        std::cout << "Police Arial introuvable, utilisation police par défaut" << std::endl;
    }

    paddle = new Paddle(paddleTexture, 400, 700);
    ball = new Ball(ballTexture, 512, 384);
    
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 10);
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowWidth - 150, 10);
    
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
    gameOverText.setPosition(windowWidth / 2, windowHeight / 2);
    
    menu = new Menu(font, windowWidth, windowHeight);
}

int Game::start()
{
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds(); 
        events();
        
        if(state == PLAYING)
        {
            update(deltaTime);
        }
        else if(state == MENU)
        {
            updateMenu(deltaTime);
        }
        
        draw();
    }
    
    // Le code de nettoyage a été déplacé dans Game::~Game()
    
    return 0;
}

void Game::events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        
        switch(state)
        {
            case MENU:
                handleMenuEvents(event);
                break;
            case PLAYING:
                handleGameEvents(event);
                break;
            case GAME_OVER:
                handleGameOverEvents(event);
                break;
        }
    }
}

void Game::handleMenuEvents(sf::Event& event)
{
    if(!menu) return;
    auto action = menu->handleEvent(event);
    
    if(action == Menu::Action::Start) {
        startGame();
    } 
    else if(action == Menu::Action::Options) {
        // TODO: Implémentez ici la logique pour basculer vers l'écran Options
        std::cout << "DEBUG: Options sélectionné. Nécessite l'état 'OPTIONS'." << std::endl;
    } 
    else if(action == Menu::Action::Credits) {
        // TODO: Implémentez ici la logique pour basculer vers l'écran Crédits
        std::cout << "DEBUG: Crédits sélectionné. Nécessite l'état 'CREDITS'." << std::endl;
    }
    else if(action == Menu::Action::Quit) {
        window.close();
    }
}

void Game::handleGameEvents(sf::Event& event)
{
    
}

void Game::handleGameOverEvents(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        resetGame();
        state = MENU;
    }
}

void Game::update(float time)
{
    paddle->update(time);
    ball->update(time);
    ball->checkCollisionPaddle(*paddle);
    
    for(auto brick : bricks)
    {
        if(ball->checkCollisionBrick(*brick))
        {
            if(brick->isDestroyed())
            {
                score += brick->getScoreValue();
            }
        }
    }
    
    bricks.erase(
        std::remove_if(bricks.begin(), bricks.end(), 
            [](Brick* brick) { 
                if(brick->isDestroyed()) {
                    delete brick;
                    return true;
                }
                return false;
            }),
        bricks.end()
    );
    
    checkGameOver();
    
    livesText.setString("Vies: " + std::to_string(lives));
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::updateMenu(float time)
{
    if(menu) menu->update(time);
}


void Game::draw()
{
    window.clear(sf::Color::Black);
    
    switch(state)
    {
        case MENU:
            drawMenu();
            break;
        case PLAYING:
            drawGame();
            break;
        case GAME_OVER:
            drawGameOver();
            break;
    }
    
    window.display();
}

void Game::drawMenu()
{
    if(menu) menu->draw(window);
}

void Game::drawGame()
{
    paddle->draw(window);
    ball->draw(window);
    for(auto brick : bricks)
    {
        brick->draw(window);
    }
    
    window.draw(livesText);
    window.draw(scoreText);
}

void Game::drawGameOver()
{
    drawGame();
    
    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
    window.draw(overlay);
    
    bool isVictory = (gameOverText.getString() == "VICTOIRE!");
    
    sf::RectangleShape gameOverShadow(sf::Vector2f(740, 340));
    gameOverShadow.setOrigin(370, 170);
    gameOverShadow.setPosition(windowWidth / 2 + 10, windowHeight / 2 + 10);
    gameOverShadow.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(gameOverShadow);
    
    sf::RectangleShape gameOverBox(sf::Vector2f(740, 340));
    gameOverBox.setOrigin(370, 170);
    gameOverBox.setPosition(windowWidth / 2, windowHeight / 2);
    gameOverBox.setFillColor(sf::Color(20, 20, 40, 240));
    gameOverBox.setOutlineThickness(6);
    
    sf::Color boxOutline = isVictory ? sf::Color(50, 255, 100) : sf::Color(255, 50, 80);
    gameOverBox.setOutlineColor(boxOutline);
    window.draw(gameOverBox);
    
    for(int i = 0; i < 2; i++)
    {
        sf::RectangleShape glowBox = gameOverBox;
        glowBox.setScale(1.02f + i * 0.03f, 1.02f + i * 0.03f);
        sf::Color glowColor = boxOutline;
        glowColor.a = static_cast<sf::Uint8>(30 - i * 10);
        glowBox.setFillColor(sf::Color::Transparent);
        glowBox.setOutlineColor(glowColor);
        glowBox.setOutlineThickness(4);
        window.draw(glowBox);
    }
    
    sf::Text shadowText = gameOverText;
    shadowText.setPosition(windowWidth / 2 + 5, windowHeight / 2 - 50 + 5);
    shadowText.setFillColor(sf::Color(0, 0, 0, 200));
    shadowText.setOutlineThickness(0);
    window.draw(shadowText);
    
    gameOverText.setPosition(windowWidth / 2, windowHeight / 2 - 50);
    if(isVictory)
    {
        gameOverText.setFillColor(sf::Color(100, 255, 150));
        gameOverText.setOutlineThickness(3);
        gameOverText.setOutlineColor(sf::Color(50, 200, 100));
    }
    else
    {
        gameOverText.setFillColor(sf::Color(255, 100, 120));
        gameOverText.setOutlineThickness(3);
        gameOverText.setOutlineColor(sf::Color(200, 50, 80));
    }
    window.draw(gameOverText);
    
    sf::RectangleShape scoreLine(sf::Vector2f(500, 3));
    scoreLine.setOrigin(250, 1.5f);
    scoreLine.setPosition(windowWidth / 2, windowHeight / 2 + 20);
    scoreLine.setFillColor(boxOutline);
    window.draw(scoreLine);
    
    sf::Text scoreDisplayText;
    scoreDisplayText.setFont(font);
    scoreDisplayText.setCharacterSize(38);
    scoreDisplayText.setFillColor(sf::Color(255, 220, 100));
    scoreDisplayText.setStyle(sf::Text::Bold);
    scoreDisplayText.setString("SCORE: " + std::to_string(score));
    scoreDisplayText.setOutlineThickness(2);
    scoreDisplayText.setOutlineColor(sf::Color(150, 120, 50));
    sf::FloatRect bounds = scoreDisplayText.getLocalBounds();
    scoreDisplayText.setOrigin(bounds.width / 2, bounds.height / 2);
    scoreDisplayText.setPosition(windowWidth / 2, windowHeight / 2 + 60);
    
    sf::Text scoreShadow = scoreDisplayText;
    scoreShadow.setPosition(windowWidth / 2 + 3, windowHeight / 2 + 63);
    scoreShadow.setFillColor(sf::Color(0, 0, 0, 150));
    scoreShadow.setOutlineThickness(0);
    window.draw(scoreShadow);
    window.draw(scoreDisplayText);
    
    sf::Text returnText;
    returnText.setFont(font);
    returnText.setCharacterSize(20);
    returnText.setFillColor(sf::Color(150, 180, 220));
    returnText.setString("Appuyez sur ESPACE pour retourner au menu");
    bounds = returnText.getLocalBounds();
    returnText.setOrigin(bounds.width / 2, bounds.height / 2);
    returnText.setPosition(windowWidth / 2, windowHeight / 2 + 125);
    window.draw(returnText);
}

void Game::createBricks()
{
    int rows = 5;
    int cols = 7;  
    float brickWidth = 100;   
    float brickHeight = 40; 
    float startX = 40;     
    float startY = 50;  
    float spacingX = 35;   
    float spacingY = 30; 

    for(int row = 0; row < rows; row++)
    {
        Brick::BrickType type;
        
        if(row == 0)
            type = Brick::SOLID;
        else if(row == 1 || row == 2)
            type = Brick::REINFORCED;
        else
            type = Brick::NORMAL;
        
        for(int col = 0; col < cols; col++)
        {
            float x = startX + col * (brickWidth + spacingX);
            float y = startY + row * (brickHeight + spacingY);
            
            bricks.push_back(new Brick(brickTexture, x, y, type));
        }
    }
}

void Game::resetBall()
{
    delete ball;
    ball = new Ball(ballTexture, 512, 384);
}

void Game::checkGameOver()
{
    if(ball->getHitbox().top > windowHeight)
    {
        lives--;
        if(lives <= 0)
        {
            state = GAME_OVER;
            gameOverText.setString("GAME OVER");
            gameOverText.setFillColor(sf::Color::Red);
            sf::FloatRect bounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
            gameOverText.setPosition(windowWidth / 2, windowHeight / 2);
        }
        else
        {
            resetBall();
        }
    }
    
    if(bricks.empty() && state == PLAYING)
    {
        gameOverText.setString("VICTOIRE!");
        gameOverText.setFillColor(sf::Color::Green);
        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
        gameOverText.setPosition(windowWidth / 2, windowHeight / 2);
        state = GAME_OVER;
    }
}

void Game::startGame()
{
    state = PLAYING;
    lives = 3;
    score = 0;
    
    for(auto brick : bricks)
    {
        delete brick;
    }
    bricks.clear();
    createBricks();
    resetBall();
}

void Game::resetGame()
{
    lives = 3;
    score = 0;
    
    for(auto brick : bricks)
    {
        delete brick;
    }
    bricks.clear();
    resetBall();
}

void Game::createParticles()
{

}