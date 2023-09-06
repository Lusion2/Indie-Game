#ifndef INDIE_GAME_PLAYER_HPP
#define INDIE_GAME_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../util/keys.hpp"
#include "../game/state.hpp"
#include "../util/constants.hpp"

enum class PlayerState{
    idle, walk, run, hit,
};

const static sf::Vector2f PlayerStartingPos(0, 0);
const static sf::Vector2f PlayerOffset((WIDTH / 2) - 90, (HEIGHT / 2) - 90);
const static sf::Vector2f HitBoxOffset(25, 30);

const static float playerSpeed = 10;

class Player{
public:
    Player() = default;
    inline explicit Player(int hp, std::string name){
        m_hp = hp;
        m_name = name;
        m_pos = PlayerStartingPos;
    }
    inline ~Player(){}

    bool load_texture();
    void update(Keys *keys);
    void draw(sf::RenderWindow *win, State *state, bool DEBUG = false);

    inline sf::Vector2f* get_pos(){
        return &m_pos;
    }
    inline sf::FloatRect* get_hitbox(){
        return &m_hitbox;
    }

private:

    void move(Keys *keys);

    int m_hp;
    std::string m_name;
    sf::Vector2f m_pos;
   
    // Sprite and texture variables
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::FloatRect m_hitbox;
    
    PlayerState m_state;

};

#endif