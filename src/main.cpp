#include <SFML/Graphics.hpp>
#include <iostream>
#include "game/game.hpp"
#include "game/state.hpp"
#include "objects/game_object.hpp"
#include "player/player.hpp"
#include "util/constants.hpp"

int main()
{
    std::cout << "\033[33mInitializing\033[0m\n";
    Game game;

    GameObject obj;
    game.add_object(&obj);

    std::cout << "\033[32mSuccessfully Initialized!\033[0m\n";
    game.main_loop();

    return 0;
}