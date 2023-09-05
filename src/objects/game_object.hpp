#ifndef INDIE_GAME_GAME_OBJECT_HPP
#define INDIE_GAME_GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../game/state.hpp"

// Base GameObject class...
// Other GameObjets will inherit from this class
class GameObject{
public:

    inline explicit GameObject(){
        m_pos = {0.0f, 0.0f};
        m_hitbox.left = 0.0;
        m_hitbox.top = 0.0f;
        m_rect_shape.setFillColor(sf::Color(255, 255, 255));
        m_rect_shape.setSize(sf::Vector2f(100, 100));
    }
    // inline explicit GameObject(sf::Vector2f pos, sf::Color col){
    //     m_pos = pos;
    //     m_hitbox.left = m_pos.x;
    //     m_hitbox.top = m_pos.y;
    //     m_rect_shape.setFillColor(col);
    // }
    inline ~GameObject(){}

    inline void update(){

    }

    inline void draw(sf::RenderWindow *win, State *state){
        // t_pos is the screenspace position
        sf::Vector2f t_pos;
        CameraState cam_state = state->get_camera_state();
        sf::Vector2f cam_pos = state->get_camera_pos();

        // Setting the screenspace pos of the player depending
        // on the camera state
        if (cam_state == CameraState::follow){
            t_pos = m_pos - cam_pos;
        }
        else if (cam_state == CameraState::lock){
            t_pos = m_pos - cam_pos;
        }
        m_rect_shape.setPosition(t_pos);
        win->draw(m_rect_shape);
    }

private:
    sf::Vector2f m_pos;
    sf::FloatRect m_hitbox;
    sf::RectangleShape m_rect_shape;
    sf::Sprite m_sprite;

};

#endif