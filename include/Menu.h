#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Menu
{
public:
    enum class MenuResult
    {
        Play,
        Exit,
        Nothing
    };

    Menu(sf::RenderWindow& window);
    
    MenuResult show();

private:
    struct MenuItem
    {
        sf::RectangleShape shape;
        sf::Text label;
        MenuResult action;
        bool isSelected;
    };

    sf::RenderWindow& m_window;
    std::vector<MenuItem> m_menuItems;
    int m_selectedItemIndex{0};
    
    void setupMenuItems();
    void draw();
    void moveUp();
    void moveDown();
    MenuResult getCurrentAction() const;
    void updateSelection();
};
