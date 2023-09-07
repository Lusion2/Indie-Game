#include <SFML/Graphics.hpp>
#include <iostream>
#include "game/game.hpp"
#include "game/state.hpp"
#include "objects/game_object.hpp"
#include "player/player.hpp"
#include "util/constants.hpp"
#include "level_data/level.hpp"

int main()
{
    std::cout << "\033[33mInitializing\033[0m\n";
    Game game;

    std::cout << "\033[32mSuccessfully Initialized!\033[0m\n";
    game.main_loop();

    return 0;
}