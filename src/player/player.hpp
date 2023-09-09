#ifndef INDIE_GAME_PLAYER_HPP
#define INDIE_GAME_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../animation/animator.hpp"
#include "../util/keys.hpp"
#include "../game/state.hpp"
#include "../util/constants.hpp"

const static sf::Vector2f PlayerStartingPos(0, 0);
const static sf::Vector2f PlayerOffset((WIDTH / 2) - 90, (HEIGHT / 2) - 90);
const static sf::Vector2f HitBoxOffset(25, 30);

const static float playerSpeed = 6;

class Player{
public:
    Player() = default;
    inline explicit Player(int hp, std::string name){
        m_hp = hp;
        m_name = name;
        m_pos = PlayerStartingPos;
        m_animator = CAnimator("./textures/test/characters/player/");
    }
    ~Player(){}

    void load_texture();
    void update(Keys *keys, float deltaTime);
    void draw(sf::RenderWindow *win, State *state, bool DEBUG = false);

    inline sf::Vector2f* get_pos(){
        return &m_pos;
    }
    inline sf::Vector2f *get_last_pos(){
        return &m_last_pos;
    }
    inline sf::FloatRect* get_hitbox(){
        return &m_hitbox;
    }

    inline void set_sprite(sf::Sprite sprite){
        m_sprite = sprite;
    }
    inline void set_pos(sf::Vector2f pos){
        m_pos = pos;
    }

private:

    void move(Keys *keys);

    void update_animation(float deltaTime);
    void set_animation_data();


    int m_hp;
    std::string m_name;
    sf::Vector2f m_pos;
    sf::Vector2f m_last_pos;
   
    // Sprite and texture variables
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::FloatRect m_hitbox;
    
    struct AnimationData{
        int anim_frames;
        int curr_anim_frame = 0;
        float time_between_frames;
        float time_last_frame = 0;
    };

    PlayerState m_state = PlayerState::idle;
    PlayerState m_prev_state;
    EntityDir m_dir = EntityDir::right;

    CAnimator m_animator;
    AnimationData m_idle_data = { .anim_frames = 10, .time_between_frames = 0.125 };
    AnimationData m_walk_data = { .anim_frames = 8, .time_between_frames = 0.075 };
    AnimationData *m_current_animation;
};

#endif