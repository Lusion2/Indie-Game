#include <iostream>
#include "game/game.hpp"

int main()
{
    std::cout << "\033[33mInitializing\033[0m\n";
    // Default constructor handles everything
    Game game;

    std::cout << "\033[32mSuccessfully Initialized!\033[0m\n";
    // Begin the main game loop
    game.main_loop();

    return 0;
}