#ifndef INDIE_GAME_GAME_HPP
#define INDIE_GAME_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include "../player/player.hpp"
#include "../objects/game_object.hpp"
#include "../util/keys.hpp"
#include "../level_data/level.hpp"

class Game{
public:

    inline explicit Game(){
        m_win.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE);
        m_win.setFramerateLimit(60);
        if(!m_win.isOpen()){
            std::cerr << "\033[31mError Initializing Window. Closing program\033[0m\n";
            exit(EXIT_FAILURE);
        }
        m_font.loadFromFile("./fonts/monospace.ttf");
        m_player = Player(100, "Grace");
        m_player.load_texture();
        m_state = State(CameraState::lock);
        load_map();
        for(GameObject &obj : m_objs){
            obj.load_texture();
        }
        std::cout << "Number of GameObjects -> " << m_objs.size() << std::endl;
    }
    inline ~Game(){}

    void on_update();
    void on_render();
    void draw_debug();
    void load_map();

    void main_loop(){
        while(m_win.isOpen()){
            on_update();
            on_render();
        }
    }

    inline void add_object(GameObject obj){
        m_objs.push_back(obj);
    }

private:

    inline void poll_events(){
        sf::Event event;
        while (m_win.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                m_win.close();
        }
    }

    void check_all_collisions();
    void draw_all_objs();

    void check_keypresses();
    
    // General stuff
    sf::RenderWindow m_win;
    Player m_player;
    State m_state;
    Keys m_keys;
    CameraState m_cam_state = CameraState::follow;

    // TIMEKEEPING
    sf::Clock m_clock;
    float m_deltaTime = 0;
    float m_lastFrameTime = 0;
    float m_timeSinceLastKeyPress = 0;

    // Keeping track of the game objects
    std::vector<GameObject> m_objs;

    // Font stuff
    sf::Font m_font;

    // DEBUG toggle
    bool DEBUG = false;

};

#endif