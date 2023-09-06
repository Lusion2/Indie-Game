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
    sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE);
    win.setFramerateLimit(60);

    Player player(100, "Grace");
    State state(CameraState::lock);
    Game game(&win, &state, &player);

    GameObject obj;
    game.add_object(&obj);

    std::cout << "\033[32mSuccessfully Began running!\033[0m\n";
    while (win.isOpen()){
        game.on_update();
        game.on_render();
    }

    return 0;
}