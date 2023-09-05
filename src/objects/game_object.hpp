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
        
        if(!m_texture.loadFromFile("./textures/test/rock.png")){
            std::cerr << "Failed to load texture\n";
        }
        m_sprite.setTexture(m_texture);
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
        sf::Vector2f cam_pos = state->get_camera_pos();
        sf::Vector2f t_pos = m_pos - cam_pos;

        m_sprite.setPosition(t_pos);
        win->draw(m_sprite);
    }

private:
    sf::Vector2f m_pos;
    sf::FloatRect m_hitbox;
    sf::RectangleShape m_rect_shape;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

};

#endif