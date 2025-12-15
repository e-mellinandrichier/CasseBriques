#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>

#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

class Game {
public:
    enum GameState { MENU, PLAYING, GAME_OVER, VICTORY };

    Game();
    int run();

private:
    static constexpr unsigned int WINDOW_WIDTH{800u};
    static constexpr unsigned int WINDOW_HEIGHT{600u};
    static constexpr float BALL_RADIUS{8.f};
    static constexpr float BALL_SPEED{400.f};
    static constexpr float PADDLE_WIDTH{100.f};
    static constexpr float PADDLE_HEIGHT{15.f};
    static constexpr float BRICK_WIDTH{70.f};
    static constexpr float BRICK_HEIGHT{30.f};
    static constexpr float BRICK_SPACING{5.f};
    static constexpr int BRICK_ROWS{5};
    static constexpr int BRICK_COLS{10};
    static constexpr int INITIAL_LIVES{3};

    sf::RenderWindow window;
    sf::Clock clock;
    sf::Font font;
    GameState state;
    int lives;
    int score;

    std::unique_ptr<Paddle> paddle;
    std::unique_ptr<Ball> ball;
    std::vector<std::unique_ptr<Brick>> bricks;
    bool ballLaunched;

    void initializeGame();
    void createBricks();
    void resetBall();
    void handleEvents();
    void update(float deltaTime);
    void draw();
    void checkGameOver();
    void resetGameState();
};

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Casse Briques"),
      state(MENU), lives(INITIAL_LIVES), score(0), ballLaunched(false)
{
    window.setFramerateLimit(60);
    
    // Try to load a system font, but continue without it if unavailable
    const std::string fontPaths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/System/Library/Fonts/Arial.ttf"
    };
    
    bool fontLoaded = false;
    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            fontLoaded = true;
            break;
        }
    }
    
    if (!fontLoaded) {
        std::cout << "Warning: Could not load system font. Text may not display correctly." << std::endl;
    }
    
    // Initialize paddle
    float paddleX = WINDOW_WIDTH / 2.f - PADDLE_WIDTH / 2.f;
    float paddleY = WINDOW_HEIGHT - PADDLE_HEIGHT - 20.f;
    paddle = std::make_unique<Paddle>(paddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT);
}

int Game::run()
{
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleEvents();

        if (state == PLAYING) {
            update(deltaTime);
        }

        draw();
    }

    std::cout << "Goodbye from CasseBriques!" << std::endl;
    return 0;
}

void Game::initializeGame()
{
    state = PLAYING;
    lives = INITIAL_LIVES;
    score = 0;
    ballLaunched = false;
    bricks.clear();
    createBricks();
    resetBall();
}

void Game::createBricks()
{
    float brickStartX = (WINDOW_WIDTH - (BRICK_COLS * (BRICK_WIDTH + BRICK_SPACING) - BRICK_SPACING)) / 2.f;
    float brickStartY = 50.f;

    for (int row = 0; row < BRICK_ROWS; ++row) {
        for (int col = 0; col < BRICK_COLS; ++col) {
            float x = brickStartX + col * (BRICK_WIDTH + BRICK_SPACING);
            float y = brickStartY + row * (BRICK_HEIGHT + BRICK_SPACING);
            int health = BRICK_ROWS - row;
            bricks.push_back(std::make_unique<Brick>(x, y, BRICK_WIDTH, BRICK_HEIGHT, health));
        }
    }
}

void Game::resetBall()
{
    float paddleX = paddle->getPosition().x;
    float paddleY = paddle->getPosition().y;
    float ballX = paddleX + PADDLE_WIDTH / 2.f - BALL_RADIUS;
    float ballY = paddleY - BALL_RADIUS * 2.f;

    ball = std::make_unique<Ball>(ballX, ballY, BALL_RADIUS, sf::Vector2f(0.f, 0.f));
    ball->setGravityEnabled(false);
    ballLaunched = false;
}

void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (state == MENU && event.key.code == sf::Keyboard::Return) {
                initializeGame();
            } else if (state == PLAYING && event.key.code == sf::Keyboard::Space) {
                if (!ballLaunched && ball) {
                    float ballX = paddle->getPosition().x + PADDLE_WIDTH / 2.f - BALL_RADIUS;
                    float ballY = paddle->getPosition().y - BALL_RADIUS * 2.f;
                    ball->setPosition(ballX, ballY);
                    ball->setVelocity(0.f, -BALL_SPEED);
                    ball->setGravityEnabled(true);
                    ballLaunched = true;
                }
            } else if ((state == GAME_OVER || state == VICTORY) && event.key.code == sf::Keyboard::Return) {
                state = MENU;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        InputManager::getInstance().processEvent(event);
    }
}

void Game::update(float deltaTime)
{
    // Update paddle position with mouse
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float targetX = static_cast<float>(mousePos.x) - PADDLE_WIDTH / 2.f;
    targetX = std::max(0.f, std::min(targetX, static_cast<float>(WINDOW_WIDTH) - PADDLE_WIDTH));
    paddle->setPosition(targetX, WINDOW_HEIGHT - PADDLE_HEIGHT - 20.f);
    paddle->update(deltaTime);

    // Update bricks
    for (auto& brick : bricks) {
        brick->update(deltaTime);
    }

    // Update ball
    if (!ballLaunched && ball) {
        float ballX = paddle->getPosition().x + PADDLE_WIDTH / 2.f - BALL_RADIUS;
        float ballY = paddle->getPosition().y - BALL_RADIUS * 2.f;
        ball->setPosition(ballX, ballY);
        ball->setVelocity(0.f, 0.f);
        ball->setGravityEnabled(false);
        ball->update(0.f);
    } else if (ball && ballLaunched) {
        ball->update(deltaTime);
        ball->bounceOffWalls(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));

        // Collision with paddle
        if (ball->checkCollisionWithAABB(paddle->getBounds())) {
            sf::Vector2f ballCenter = ball->getPosition() + sf::Vector2f(BALL_RADIUS, BALL_RADIUS);
            float paddleCenterX = paddle->getPosition().x + PADDLE_WIDTH / 2.f;
            float hitPosition = (ballCenter.x - paddleCenterX) / (PADDLE_WIDTH / 2.f);
            hitPosition = std::max(-1.f, std::min(1.f, hitPosition));

            float angle = hitPosition * 60.f * 3.14159265f / 180.f;
            float speed = std::sqrt(ball->getVelocity().x * ball->getVelocity().x +
                                   ball->getVelocity().y * ball->getVelocity().y);
            if (speed < BALL_SPEED * 0.5f) speed = BALL_SPEED;

            sf::Vector2f newVelocity(std::sin(angle) * speed, -std::abs(std::cos(angle) * speed));
            ball->setVelocity(newVelocity);
            ball->setPosition(ball->getPosition().x, paddle->getPosition().y - BALL_RADIUS * 2.f);
        }

        // Collision with bricks
        for (auto& brick : bricks) {
            if (!brick->isDestroyed() && ball->checkCollisionWithAABB(brick->getAABB())) {
                ball->handleCollisionWithAABB(brick->getAABB());
                brick->takeDamage(1);
                if (brick->isDestroyed()) {
                    score += 10;
                }
            }
        }

        // Check if ball is out of bounds
        if (ball->isOutOfBounds(static_cast<float>(WINDOW_HEIGHT))) {
            lives--;
            if (lives <= 0) {
                state = GAME_OVER;
            } else {
                resetBall();
            }
        }
    }

    // Check for victory
    bool allDestroyed = std::all_of(bricks.begin(), bricks.end(),
                                     [](const auto& brick) { return brick->isDestroyed(); });
    if (allDestroyed && !bricks.empty()) {
        state = VICTORY;
    }

    // Clean up destroyed bricks
    bricks.erase(
        std::remove_if(bricks.begin(), bricks.end(),
                      [](const auto& brick) { return brick->isDestroyed(); }),
        bricks.end());
}

void Game::draw()
{
    window.clear(sf::Color::Black);

    if (state == MENU) {
        sf::Text title;
        title.setFont(font);
        title.setString("CASSE BRIQUES");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::White);
        title.setPosition(WINDOW_WIDTH / 2.f - 150.f, WINDOW_HEIGHT / 2.f - 100.f);
        window.draw(title);

        sf::Text startText;
        startText.setFont(font);
        startText.setString("Appuyez sur ENTREE pour commencer");
        startText.setCharacterSize(24);
        startText.setFillColor(sf::Color::Yellow);
        startText.setPosition(WINDOW_WIDTH / 2.f - 180.f, WINDOW_HEIGHT / 2.f + 50.f);
        window.draw(startText);
    } else if (state == PLAYING) {
        for (const auto& brick : bricks) {
            brick->draw(window);
        }
        paddle->draw(window);
        if (ball) {
            ball->draw(window);
        }

        sf::Text livesText;
        livesText.setFont(font);
        livesText.setString("Vies: " + std::to_string(lives));
        livesText.setCharacterSize(20);
        livesText.setFillColor(sf::Color::White);
        livesText.setPosition(10.f, 10.f);
        window.draw(livesText);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(WINDOW_WIDTH - 200.f, 10.f);
        window.draw(scoreText);
    } else if (state == GAME_OVER) {
        for (const auto& brick : bricks) {
            brick->draw(window);
        }
        paddle->draw(window);
        if (ball) {
            ball->draw(window);
        }

        sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        overlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(overlay);

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(64);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(WINDOW_WIDTH / 2.f - 180.f, WINDOW_HEIGHT / 2.f - 100.f);
        window.draw(gameOverText);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score final: " + std::to_string(score));
        scoreText.setCharacterSize(32);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(WINDOW_WIDTH / 2.f - 150.f, WINDOW_HEIGHT / 2.f);
        window.draw(scoreText);

        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Appuyez sur ENTREE pour revenir au menu");
        restartText.setCharacterSize(20);
        restartText.setFillColor(sf::Color::Yellow);
        restartText.setPosition(WINDOW_WIDTH / 2.f - 200.f, WINDOW_HEIGHT / 2.f + 100.f);
        window.draw(restartText);
    } else if (state == VICTORY) {
        for (const auto& brick : bricks) {
            brick->draw(window);
        }
        paddle->draw(window);
        if (ball) {
            ball->draw(window);
        }

        sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        overlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(overlay);

        sf::Text victoryText;
        victoryText.setFont(font);
        victoryText.setString("VICTOIRE!");
        victoryText.setCharacterSize(64);
        victoryText.setFillColor(sf::Color::Green);
        victoryText.setPosition(WINDOW_WIDTH / 2.f - 160.f, WINDOW_HEIGHT / 2.f - 100.f);
        window.draw(victoryText);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score final: " + std::to_string(score));
        scoreText.setCharacterSize(32);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(WINDOW_WIDTH / 2.f - 150.f, WINDOW_HEIGHT / 2.f);
        window.draw(scoreText);

        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Appuyez sur ENTREE pour revenir au menu");
        restartText.setCharacterSize(20);
        restartText.setFillColor(sf::Color::Yellow);
        restartText.setPosition(WINDOW_WIDTH / 2.f - 200.f, WINDOW_HEIGHT / 2.f + 100.f);
        window.draw(restartText);
    }

    window.display();
}

void Game::checkGameOver()
{
    if (ball->isOutOfBounds(static_cast<float>(WINDOW_HEIGHT))) {
        lives--;
        if (lives <= 0) {
            state = GAME_OVER;
        } else {
            resetBall();
        }
    }
}

int main()
{
    Game game;
    return game.run();
}
