#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    sf::RenderWindow window{
        sf::VideoMode{sf::Vector2u{800u, 600u}},
        "Casse Briques"
    };
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    std::cout << "Goodbye from CasseBriques!" << std::endl;
    return 0;
}

