#include "../include/Menu.hpp"
#include <cmath>
#include <iostream>

// Constantes de layout ajustées pour un meilleur centrage
const float MENU_ITEM_START_Y = 380.f; // Point de départ plus haut et bien centré
const float MENU_ITEM_SPACING_Y = 70.f; // Espacement vertical optimisé pour 4 options

Menu::Menu(sf::Font& f, int w, int h)
    : font(f), width(w), height(h), selectedMenuItem(0), animationTime(0.f)
{
    // TITRE - Style grand et impactant, avec une touche holographique
    titleText.setFont(font);
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color(255, 255, 255)); 
    titleText.setOutlineColor(sf::Color(0, 180, 255, 150)); // Cyan clair
    titleText.setOutlineThickness(3.f);
    titleText.setString("CASSE-BRIQUE");
    titleText.setStyle(sf::Text::Bold);
    titleText.setLetterSpacing(1.f);
    auto bounds = titleText.getLocalBounds();
    titleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    titleText.setPosition(width / 2.f, 150.f); // Monté

    // SUBTITLE - Discret et technique
    subtitleText.setFont(font);
    subtitleText.setCharacterSize(18);
    subtitleText.setFillColor(sf::Color(100, 150, 200, 200));
    subtitleText.setString("// PROJET LAPLATEFORME EDITION //");
    subtitleText.setLetterSpacing(4.f);
    bounds = subtitleText.getLocalBounds();
    subtitleText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    subtitleText.setPosition(width / 2.f, 250.f);

    // INSTRUCTIONS
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(14);
    instructionsText.setFillColor(sf::Color(80, 120, 180, 180));
    instructionsText.setString("UTILISEZ LES FLECHES | ENTREE POUR ACTIVER");
    instructionsText.setLetterSpacing(1.5f);
    bounds = instructionsText.getLocalBounds();
    instructionsText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    instructionsText.setPosition(width / 2.f, height - 30.f);

    // MEILLEUR SCORE - Positionné en bas à droite pour équilibrer
    bestScoreLabel.setFont(font);
    bestScoreLabel.setCharacterSize(14);
    bestScoreLabel.setFillColor(sf::Color(150, 150, 200));
    bestScoreLabel.setString("RECORD ACTUEL");
    bestScoreLabel.setLetterSpacing(3.f);
    bounds = bestScoreLabel.getLocalBounds();
    bestScoreLabel.setOrigin(bounds.width, bounds.height); 
    bestScoreLabel.setPosition(width - 40.f, height - 90.f);

    bestScoreValue.setFont(font);
    bestScoreValue.setCharacterSize(40);
    bestScoreValue.setFillColor(sf::Color(0, 255, 255)); // Cyan brillant
    bestScoreValue.setString("25.600");
    bestScoreValue.setStyle(sf::Text::Bold);
    bestScoreValue.setLetterSpacing(2.f);
    bounds = bestScoreValue.getLocalBounds();
    bestScoreValue.setOrigin(bounds.width, bounds.height); 
    bestScoreValue.setPosition(width - 40.f, height - 40.f);
    
    // **********************************************
    // OPTIONS DU MENU
    // **********************************************
    
    // Initialisation des textes des options (taille et police communes)
    sf::Text* menuItems[] = {&playText, &optionsText, &creditsText, &quitText};
    std::string itemStrings[] = {"[ DEMARRER LA SIMULATION ]", "[ OUVRIR LES OPTIONS ]", "[ CREDITS ]", "[ SORTIR DU PROTOCOL ]"};

    for (int i = 0; i < 4; ++i) {
        menuItems[i]->setFont(font);
        menuItems[i]->setCharacterSize(36); // Taille lisible
        menuItems[i]->setString(itemStrings[i]);
        menuItems[i]->setLetterSpacing(1.5f);
        
        // Positionnement vertical
        float yPos = MENU_ITEM_START_Y + MENU_ITEM_SPACING_Y * i;
        
        bounds = menuItems[i]->getLocalBounds();
        menuItems[i]->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        menuItems[i]->setPosition(width / 2.f, yPos);
    }

    // PARTICULES - Ambiance subtile
    for (int i = 0; i < 180; ++i) {
        Star star;
        star.position = sf::Vector2f(
            static_cast<float>(rand() % width),
            static_cast<float>(rand() % height)
        );
        star.size = 0.5f + static_cast<float>(rand() % 3) * 0.5f;
        star.speed = 0.5f + static_cast<float>(rand() % 100) / 100.f;
        star.alpha = 50 + rand() % 80; 
        stars.push_back(star);
    }
}

void Menu::update(float dt)
{
    animationTime += dt;

    // Animation des étoiles (scintillement subtil)
    for (auto& star : stars) {
        star.alpha = static_cast<sf::Uint8>(
            80 + 40 * std::sin(animationTime * star.speed + star.position.x * 0.01f)
        );
    }

    // Animation du titre - Effet de pulsation très subtil sur le contour
    float pulse = 1.0f + 0.05f * std::sin(animationTime * 1.5f);
    titleText.setScale(pulse, pulse);

    // Mise à jour des styles des textes du menu
    sf::Text* menuItems[] = {&playText, &optionsText, &creditsText, &quitText};
    for(int i = 0; i < 4; ++i) {
        if (i == selectedMenuItem) {
            // Effet Holographique (texte vif et contour lumineux)
            menuItems[i]->setFillColor(sf::Color(0, 255, 255)); // Cyan vif
            menuItems[i]->setOutlineThickness(1.5f);
            menuItems[i]->setOutlineColor(sf::Color(255, 255, 255, 180));
        } else {
            // Texte inactif
            menuItems[i]->setFillColor(sf::Color(100, 150, 200)); // Bleu gris
            menuItems[i]->setOutlineThickness(0.f);
        }
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    // BACKGROUND - Noir profond (Espace)
    window.clear(sf::Color(5, 5, 20)); 

    // EFFET DE GLOW ARRIÈRE-PLAN CENTRÉ (Holographique)
    sf::CircleShape centralGlow(width / 3.f);
    centralGlow.setOrigin(centralGlow.getRadius(), centralGlow.getRadius());
    centralGlow.setPosition(width / 2.f, height / 2.f);
    centralGlow.setFillColor(sf::Color(0, 50, 80, 50)); // Bleu sombre très transparent
    window.draw(centralGlow);

    // ÉTOILES / PARTICULES
    for (const auto& star : stars) {
        sf::CircleShape starShape(star.size);
        starShape.setPosition(star.position);
        starShape.setFillColor(sf::Color(150, 200, 255, star.alpha));
        window.draw(starShape);
    }
    
    // CADRE DÉCORATIF HOLOGRAPHIQUE (Lignes)
    sf::RectangleShape lineVertical(sf::Vector2f(2.f, 400.f));
    lineVertical.setOrigin(1.f, 200.f);
    lineVertical.setPosition(width / 2.f, height / 2.f + 50.f);
    lineVertical.setFillColor(sf::Color(0, 180, 255, 100)); 
    window.draw(lineVertical);

    // TITRE et SUBTITLE
    window.draw(titleText);
    window.draw(subtitleText);

    // EFFET DE SÉLECTION (Hologramme)
    if (selectedMenuItem != -1) {
        sf::Text* menuItems[] = {&playText, &optionsText, &creditsText, &quitText};
        
        // Cadre autour de l'élément sélectionné
        sf::FloatRect textBounds = menuItems[selectedMenuItem]->getGlobalBounds();
        sf::Vector2f center = menuItems[selectedMenuItem]->getPosition();
        float textWidth = textBounds.width;
        float textHeight = textBounds.height;

        // Le contour holographique
        sf::RectangleShape highlight(sf::Vector2f(textWidth + 40.f, textHeight + 20.f));
        highlight.setOrigin((textWidth + 40.f) / 2.f, (textHeight + 20.f) / 2.f);
        highlight.setPosition(center.x, center.y);
        highlight.setFillColor(sf::Color(0, 255, 255, 20)); // Remplissage très transparent
        highlight.setOutlineThickness(2.f);
        
        // Pulsation du contour
        sf::Uint8 pulseAlpha = static_cast<sf::Uint8>(100 + 100 * (0.5f + 0.5f * std::sin(animationTime * 5.f)));
        highlight.setOutlineColor(sf::Color(0, 255, 255, pulseAlpha));
        window.draw(highlight);
    }
    
    // DESSINER LES TEXTES DES OPTIONS
    window.draw(playText);
    window.draw(optionsText);
    window.draw(creditsText);
    window.draw(quitText);

    // MEILLEUR SCORE (Encadré discret)
    sf::RectangleShape scorePanel(sf::Vector2f(200, 80));
    scorePanel.setOrigin(200, 80);
    scorePanel.setPosition(width - 20.f, height - 20.f);
    scorePanel.setFillColor(sf::Color(10, 10, 30, 180)); 
    scorePanel.setOutlineThickness(1.f);
    scorePanel.setOutlineColor(sf::Color(0, 150, 255, 100));
    window.draw(scorePanel);

    window.draw(bestScoreLabel);
    window.draw(bestScoreValue);

    // INSTRUCTIONS
    window.draw(instructionsText);
}

Menu::Action Menu::handleEvent(const sf::Event& event)
{
    const int numItems = 4; // 4 éléments: Play, Options, Credits, Quit
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedMenuItem = (selectedMenuItem - 1 + numItems) % numItems;
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedMenuItem = (selectedMenuItem + 1) % numItems;
        } else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
            if (selectedMenuItem == 0) return Action::Start;
            else if (selectedMenuItem == 1) return Action::Options;
            else if (selectedMenuItem == 2) return Action::Credits;
            else return Action::Quit;
        }
    }
    return Action::None;
}