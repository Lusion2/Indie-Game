#ifndef INDIE_GAME_GAME_HPP
#define INDIE_GAME_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Game{
public:

    inline explicit Game(sf::RenderWindow *win){
        m_win = win;
    }
    inline ~Game(){}

    inline void on_update(){
        
    }

private:

    sf::RenderWindow *m_win;

};

#endif