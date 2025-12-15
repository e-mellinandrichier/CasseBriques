#include "Menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow& window)
    : m_window(window)
{
    setupMenuItems();
}

void Menu::setupMenuItems()
{
    sf::Vector2u windowSize = m_window.getSize();
    float centerX = windowSize.x / 2.f;
    float startY = windowSize.y / 2.f;
    
    // Play item - Green rectangle with play symbol (triangle)
    MenuItem playItem;
    playItem.shape.setSize(sf::Vector2f(250.f, 70.f));
    playItem.shape.setFillColor(sf::Color(50, 200, 50));
    playItem.shape.setOutlineColor(sf::Color::White);
    playItem.shape.setOutlineThickness(3.f);
    playItem.shape.setPosition(centerX - 125.f, startY - 50.f);
    playItem.action = MenuResult::Play;
    playItem.isSelected = true;
    
    // Empty label (won't display without font, but structure is there)
    playItem.label.setString("");
    playItem.label.setCharacterSize(40);
    
    m_menuItems.push_back(playItem);
    
    // Exit item - Red rectangle with X symbol
    MenuItem exitItem;
    exitItem.shape.setSize(sf::Vector2f(250.f, 70.f));
    exitItem.shape.setFillColor(sf::Color(200, 50, 50));
    exitItem.shape.setOutlineColor(sf::Color::White);
    exitItem.shape.setOutlineThickness(2.f);
    exitItem.shape.setPosition(centerX - 125.f, startY + 50.f);
    exitItem.action = MenuResult::Exit;
    exitItem.isSelected = false;
    
    exitItem.label.setString("");
    exitItem.label.setCharacterSize(40);
    
    m_menuItems.push_back(exitItem);
    
    updateSelection();
}

Menu::MenuResult Menu::show()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return MenuResult::Exit;
            }
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    moveDown();
                }
                else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
                {
                    return getCurrentAction();
                }
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    return MenuResult::Exit;
                }
            }
        }
        
        draw();
        m_window.display();
    }
    
    return MenuResult::Exit;
}

void Menu::draw()
{
    m_window.clear(sf::Color::Black);
    
    sf::Vector2u windowSize = m_window.getSize();
    
    // Draw title background
    sf::RectangleShape titleBg(sf::Vector2f(windowSize.x, 140.f));
    titleBg.setFillColor(sf::Color(20, 20, 40));
    titleBg.setPosition(0.f, 0.f);
    m_window.draw(titleBg);
    
    // Draw title using visual blocks (representing "CASSE-BRIQUES")
    float titleX = windowSize.x / 2.f - 200.f;
    float titleY = 40.f;
    
    // Draw decorative title blocks
    for (int i = 0; i < 12; ++i)
    {
        sf::RectangleShape block(sf::Vector2f(25.f, 60.f));
        block.setFillColor(sf::Color::Cyan);
        block.setPosition(titleX + i * 35.f, titleY);
        if (i % 2 == 0) // Alternate pattern
        {
            block.setSize(sf::Vector2f(25.f, 60.f));
        }
        else
        {
            block.setSize(sf::Vector2f(25.f, 50.f));
        }
        m_window.draw(block);
    }
    
    // Draw title line
    sf::RectangleShape titleLine(sf::Vector2f(450.f, 4.f));
    titleLine.setFillColor(sf::Color::Cyan);
    titleLine.setPosition(windowSize.x / 2.f - 225.f, 110.f);
    m_window.draw(titleLine);
    
    // Draw menu items
    for (size_t i = 0; i < m_menuItems.size(); ++i)
    {
        auto& item = m_menuItems[i];
        
        // Draw selection indicator (triangle on left)
        if (item.isSelected)
        {
            // Draw yellow triangle pointing right
            sf::CircleShape indicator(15.f, 3);
            indicator.setFillColor(sf::Color::Yellow);
            indicator.setRotation(90.f);
            indicator.setPosition(item.shape.getPosition().x - 30.f, item.shape.getPosition().y + 20.f);
            m_window.draw(indicator);
            
            // Make selected item brighter and thicker outline
            item.shape.setOutlineThickness(5.f);
            item.shape.setOutlineColor(sf::Color::Yellow);
        }
        else
        {
            item.shape.setOutlineThickness(2.f);
            item.shape.setOutlineColor(sf::Color::White);
        }
        
        m_window.draw(item.shape);
        
        // Draw visual symbols inside buttons
        if (i == 0) // Play button
        {
            // Draw play triangle (pointing right) - centered
            float centerX = item.shape.getPosition().x + item.shape.getSize().x / 2.f;
            float centerY = item.shape.getPosition().y + item.shape.getSize().y / 2.f;
            sf::CircleShape playTriangle(20.f, 3);
            playTriangle.setFillColor(sf::Color::White);
            playTriangle.setRotation(90.f);
            playTriangle.setOrigin(20.f, 20.f); // Set origin to center
            playTriangle.setPosition(centerX, centerY);
            m_window.draw(playTriangle);
        }
        else // Exit button
        {
            // Draw X symbol using lines
            float centerX = item.shape.getPosition().x + item.shape.getSize().x / 2.f;
            float centerY = item.shape.getPosition().y + item.shape.getSize().y / 2.f;
            
            // Draw X with rectangles
            sf::RectangleShape line1(sf::Vector2f(40.f, 4.f));
            line1.setFillColor(sf::Color::White);
            line1.setRotation(45.f);
            line1.setPosition(centerX - 20.f, centerY - 2.f);
            m_window.draw(line1);
            
            sf::RectangleShape line2(sf::Vector2f(40.f, 4.f));
            line2.setFillColor(sf::Color::White);
            line2.setRotation(-45.f);
            line2.setPosition(centerX - 20.f, centerY - 2.f);
            m_window.draw(line2);
        }
    }
    
    // Draw instructions area
    sf::RectangleShape instBg(sf::Vector2f(windowSize.x, 80.f));
    instBg.setFillColor(sf::Color(30, 30, 30));
    instBg.setPosition(0.f, windowSize.y - 80.f);
    m_window.draw(instBg);
    
    // Draw instruction arrows visually
    float instX = windowSize.x / 2.f - 200.f;
    float instY = windowSize.y - 50.f;
    
    // Up arrow
    sf::CircleShape upArrow(12.f, 3);
    upArrow.setFillColor(sf::Color(150, 150, 150));
    upArrow.setRotation(0.f);
    upArrow.setPosition(instX, instY);
    m_window.draw(upArrow);
    
    // Down arrow
    sf::CircleShape downArrow(12.f, 3);
    downArrow.setFillColor(sf::Color(150, 150, 150));
    downArrow.setRotation(180.f);
    downArrow.setPosition(instX + 40.f, instY);
    m_window.draw(downArrow);
    
    // Draw instruction boxes
    sf::RectangleShape enterBox(sf::Vector2f(60.f, 25.f));
    enterBox.setFillColor(sf::Color(100, 100, 100));
    enterBox.setOutlineColor(sf::Color::White);
    enterBox.setOutlineThickness(1.f);
    enterBox.setPosition(instX + 100.f, instY - 5.f);
    m_window.draw(enterBox);
}

void Menu::moveUp()
{
    m_selectedItemIndex = (m_selectedItemIndex - 1 + m_menuItems.size()) % m_menuItems.size();
    updateSelection();
}

void Menu::moveDown()
{
    m_selectedItemIndex = (m_selectedItemIndex + 1) % m_menuItems.size();
    updateSelection();
}

void Menu::updateSelection()
{
    for (size_t i = 0; i < m_menuItems.size(); ++i)
    {
        m_menuItems[i].isSelected = (i == m_selectedItemIndex);
    }
}

Menu::MenuResult Menu::getCurrentAction() const
{
    return m_menuItems[m_selectedItemIndex].action;
}
