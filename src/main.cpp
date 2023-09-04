#include <SFML/Graphics.hpp>
#include <iostream>
#include "game/game.hpp"
#include "util/constants.hpp"

int main()
{
    sf::RenderWindow win(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE);

    Game game(&win);


    while (win.isOpen()){
        game.on_update();
    }

    return 0;
}