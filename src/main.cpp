#include "Game.h"
#include <iostream>

int main()
{
    // try-catch for safety
    try
    {
        // create game instance
        Game game;
        
        // initialize game
        game.init();
        
        // run main loop
        game.run();
        
        std::cout << "Game shut down successfully" << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}