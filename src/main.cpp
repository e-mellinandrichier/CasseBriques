#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    constexpr unsigned int windowWidth{800u};
    constexpr unsigned int windowHeight{600u};

    sf::RenderWindow window{
        sf::VideoMode{sf::Vector2u{windowWidth, windowHeight}},
        "Casse Briques"
    };
    window.setFramerateLimit(60);

    constexpr float ballRadius{10.f};
    sf::CircleShape ball{ballRadius};
    ball.setFillColor(sf::Color::White);

    sf::Vector2f ballPosition{
        static_cast<float>(windowWidth) * 0.5f - ballRadius,
        static_cast<float>(windowHeight) * 0.5f - ballRadius
    };
    sf::Vector2f ballVelocity{220.f, 180.f};

    sf::Clock clock;

    while (window.isOpen())
    {
        const float deltaSeconds{clock.restart().asSeconds()};

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        ballPosition += ballVelocity * deltaSeconds;

        const auto ballDiameter{ballRadius * 2.f};

        if ((ballPosition.x <= 0.f && ballVelocity.x < 0.f) ||
            (ballPosition.x + ballDiameter >= static_cast<float>(windowWidth) && ballVelocity.x > 0.f))
        {
            ballVelocity.x = -ballVelocity.x;
        }

        if ((ballPosition.y <= 0.f && ballVelocity.y < 0.f) ||
            (ballPosition.y + ballDiameter >= static_cast<float>(windowHeight) && ballVelocity.y > 0.f))
        {
            ballVelocity.y = -ballVelocity.y;
        }

        ball.setPosition(ballPosition);

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }

    std::cout << "Goodbye from CasseBriques!" << std::endl;
    return 0;
}

