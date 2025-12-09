#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    // MISE À JOUR : Ajout des actions Options et Credits (inchangé)
    enum class Action { None, Start, Options, Credits, Quit };

    Menu(sf::Font& font, int width, int height);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    Action handleEvent(const sf::Event& event);

private:
    // Structure pour les étoiles en arrière-plan (inchangée)
    struct Star {
        sf::Vector2f position;
        float size;
        float speed;
        sf::Uint8 alpha;
    };

    // Shared font (must outlive texts)
    sf::Font& font;

    // Layout
    int width;
    int height;

    // UI elements
    sf::Text titleText;
    sf::Text subtitleText;
    
    // Les 4 options du menu (Textes uniquement, pour un design plus épuré)
    sf::Text playText;
    // Suppression de scoresText
    sf::Text optionsText; 
    sf::Text creditsText; 
    sf::Text quitText;
    
    sf::Text instructionsText;
    sf::Text bestScoreLabel;
    sf::Text bestScoreValue;

    // Suppression des sf::RectangleShape (playButton, optionsButton, etc.)

    // selectedMenuItem va de 0 à 3 (Play, Options, Credits, Quit)
    int selectedMenuItem; 
    
    // Animation
    float animationTime;
    std::vector<Star> stars;
};