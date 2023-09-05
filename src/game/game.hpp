#ifndef INDIE_GAME_GAME_HPP
#define INDIE_GAME_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../player/player.hpp"
#include "../objects/game_object.hpp"
#include "../util/keys.hpp"

class Game{
public:

    inline explicit Game(sf::RenderWindow *win, State *state, Player *p){
        m_win = win;
        m_state = state;
        m_player = p;
    }
    inline ~Game(){}

    void on_update();
    void on_render();

    inline void add_object(GameObject *obj){
        m_objs.push_back(obj);
    }

private:

    inline void poll_events(){
        sf::Event event;
        while (m_win->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                m_win->close();
        }
    }

    void check_keypresses();
    
    // General stuff
    sf::RenderWindow *m_win;
    Player *m_player;
    State *m_state;
    Keys m_keys;
    CameraState m_cam_state = CameraState::follow;

    // TIMEKEEPING
    sf::Clock m_clock;
    float m_deltaTime;
    float m_timeSinceLastKeyPress;

    // Keeping track of the game objects
    std::vector<GameObject*> m_objs;

    // DEBUG toggle
    bool DEBUG;
};

#endif