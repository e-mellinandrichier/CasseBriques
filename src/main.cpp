#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

#include "GameObject.h"
#include "InputManager.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Menu.h"

void runGame(sf::RenderWindow& window)
{
    constexpr unsigned int windowWidth{800u};
    constexpr unsigned int windowHeight{600u};

    // Create paddle at the bottom
    constexpr float paddleWidth{100.f};
    constexpr float paddleHeight{15.f};
    constexpr float paddleY{static_cast<float>(windowHeight) - paddleHeight - 20.f};
    Paddle paddle{windowWidth / 2.f - paddleWidth / 2.f, paddleY, paddleWidth, paddleHeight};

    // Create brick grid
    std::vector<std::unique_ptr<Brick>> bricks;
    constexpr int brickRows{5};
    constexpr int brickCols{10};
    constexpr float brickWidth{70.f};
    constexpr float brickHeight{30.f};
    constexpr float brickSpacing{5.f};
    constexpr float brickStartX{(windowWidth - (brickCols * (brickWidth + brickSpacing) - brickSpacing)) / 2.f};
    constexpr float brickStartY{50.f};

    for (int row = 0; row < brickRows; ++row)
    {
        for (int col = 0; col < brickCols; ++col)
        {
            float x = brickStartX + col * (brickWidth + brickSpacing);
            float y = brickStartY + row * (brickHeight + brickSpacing);
            // Different health for different rows
            int health = brickRows - row;
            bricks.push_back(std::make_unique<Brick>(x, y, brickWidth, brickHeight, health));
        }
    }

    // Ball management
    constexpr float ballRadius{8.f};
    constexpr float ballSpeed{400.f};
    bool ballLaunched{false};
    
    // Create ball on paddle at start
    float initialBallX = paddle.getPosition().x + paddleWidth / 2.f - ballRadius;
    float initialBallY = paddle.getPosition().y - ballRadius * 2.f;
    std::unique_ptr<Ball> ball = std::make_unique<Ball>(initialBallX, initialBallY, ballRadius, sf::Vector2f(0.f, 0.f));
    ball->setGravityEnabled(false);

    // Input manager
    InputManager& inputManager = InputManager::getInstance();

    // Bind space to launch ball
    inputManager.bindKey(sf::Keyboard::Space, [&]() {
        if (!ballLaunched && ball)
        {
            // Launch ball from current paddle position
            float ballX = paddle.getPosition().x + paddleWidth / 2.f - ballRadius;
            float ballY = paddle.getPosition().y - ballRadius * 2.f;
            sf::Vector2f velocity(0.f, -ballSpeed);
            // Ensure ball is at paddle position before launching
            ball->setPosition(ballX, ballY);
            ball->setVelocity(velocity);
            ball->setGravityEnabled(true);
            ballLaunched = true;
        }
    });

    sf::Clock clock;

    while (window.isOpen())
    {
        const float deltaSeconds{clock.restart().asSeconds()};

        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            inputManager.processEvent(event);
        }

        // Paddle follows mouse
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float targetX = static_cast<float>(mousePos.x) - paddleWidth / 2.f;
        
        // Keep paddle in bounds
        if (targetX < 0.f)
        {
            targetX = 0.f;
        }
        else if (targetX + paddleWidth > static_cast<float>(windowWidth))
        {
            targetX = static_cast<float>(windowWidth) - paddleWidth;
        }
        
        paddle.setPosition(targetX, paddleY);

        // Update paddle
        paddle.update(deltaSeconds);

        // Update bricks
        for (auto& brick : bricks)
        {
            brick->update(deltaSeconds);
        }

        // Update ball
        if (!ballLaunched && ball)
        {
            // Ball follows paddle when not launched - update every frame
            // This ensures the ball moves with the paddle
            float ballX = paddle.getPosition().x + paddleWidth / 2.f - ballRadius;
            float ballY = paddle.getPosition().y - ballRadius * 2.f;
            ball->setPosition(ballX, ballY);
            ball->setVelocity(0.f, 0.f);
            ball->setGravityEnabled(false);
            // Update ball visual position (call update with 0 delta to sync shape position)
            ball->update(0.f);
        }
        else if (ball && ballLaunched)
        {
            ball->update(deltaSeconds);
            ball->bounceOffWalls(static_cast<float>(windowWidth), static_cast<float>(windowHeight));

            // Check collision with paddle
            if (ball->checkCollisionWithAABB(paddle.getBounds()))
            {
                // Calculate bounce angle based on where ball hits paddle
                sf::Vector2f ballCenter = sf::Vector2f(
                    ball->getPosition().x + ballRadius,
                    ball->getPosition().y + ballRadius
                );
                float paddleCenterX = paddle.getPosition().x + paddleWidth / 2.f;
                float hitPosition = (ballCenter.x - paddleCenterX) / (paddleWidth / 2.f);
                hitPosition = std::max(-1.f, std::min(1.f, hitPosition)); // Clamp to [-1, 1]
                
                // Bounce angle: -60 to +60 degrees based on hit position
                float angle = hitPosition * 60.f * 3.14159265f / 180.f;
                float speed = std::sqrt(ball->getVelocity().x * ball->getVelocity().x + 
                                       ball->getVelocity().y * ball->getVelocity().y);
                if (speed < ballSpeed * 0.5f) speed = ballSpeed; // Ensure minimum speed
                
                sf::Vector2f newVelocity(std::sin(angle) * speed, -std::abs(std::cos(angle) * speed));
                ball->setVelocity(newVelocity);
                
                // Position ball above paddle
                ball->setPosition(ball->getPosition().x, paddle.getPosition().y - ballRadius * 2.f);
            }

            // Check collision with bricks
            for (auto& brick : bricks)
            {
                if (!brick->isDestroyed() && ball->checkCollisionWithAABB(brick->getAABB()))
                {
                    ball->handleCollisionWithAABB(brick->getAABB());
                    brick->takeDamage(1);
                }
            }

            // Check if ball is out of bounds
            if (ball->isOutOfBounds(static_cast<float>(windowHeight)))
            {
                // Reset ball on paddle
                float ballX = paddle.getPosition().x + paddleWidth / 2.f - ballRadius;
                float ballY = paddle.getPosition().y - ballRadius * 2.f;
                ball->setPosition(ballX, ballY);
                ball->setVelocity(0.f, 0.f);
                ball->setGravityEnabled(false);
                ballLaunched = false;
            }
        }

        // Render
        window.clear(sf::Color::Black);

        // Draw bricks
        for (const auto& brick : bricks)
        {
            brick->draw(window);
        }

        // Draw paddle
        paddle.draw(window);

        // Draw ball
        if (ball)
        {
            ball->draw(window);
        }

        window.display();
    }
}

int main()
{
    constexpr unsigned int windowWidth{800u};
    constexpr unsigned int windowHeight{600u};

    sf::RenderWindow window{
        sf::VideoMode{windowWidth, windowHeight},
        "Casse Briques"
    };
    window.setFramerateLimit(60);

    // Show menu
    Menu menu(window);
    Menu::MenuResult result = menu.show();

    // Handle menu result
    if (result == Menu::MenuResult::Play)
    {
        runGame(window);
    }

    std::cout << "Goodbye from CasseBriques!" << std::endl;
    return 0;
}
