#include <iostream>
#include "game/game.hpp"

int main()
{
    std::cout << "\033[33mInitializing\033[0m\n";
    Game game;

    std::cout << "\033[32mSuccessfully Initialized!\033[0m\n";
    game.main_loop();

    return 0;
}