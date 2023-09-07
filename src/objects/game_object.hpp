#ifndef INDIE_GAME_GAME_OBJECT_HPP
#define INDIE_GAME_GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../game/state.hpp"

// Base GameObject class...
// Other GameObjets will inherit from this class
class GameObject{
public:

    inline explicit GameObject(float x, float y){
        m_pos = {x, y};
        m_hitbox.left = x;
        m_hitbox.top = y;
    }
    inline ~GameObject(){}

    inline void draw(sf::RenderWindow *win, State *state, bool DEBUG){
        // t_pos is the screenspace position
        sf::Vector2f cam_pos = state->get_camera_pos();
        sf::Vector2f m_offset_pos = m_pos - cam_pos;
        m_hitbox.left = m_offset_pos.x; m_hitbox.top = m_offset_pos.y;

        if(m_sprite.getTexture() == NULL){
            load_texture();
        }


        m_sprite.setPosition(m_offset_pos);
        if (m_offset_pos.x > WIDTH || m_offset_pos.x + m_hitbox.width < 0 ||
            m_offset_pos.y > HEIGHT || m_offset_pos.y + m_hitbox.height < 0){
                onscreen = false;
                return;
            }
        else{
            if(DEBUG){
                sf::RectangleShape hitbox;
                hitbox.setFillColor(sf::Color(0, 0, 0, 0));
                hitbox.setSize(sf::Vector2f(m_hitbox.width, m_hitbox.height));
                hitbox.setOutlineColor(sf::Color(255, 255, 255));
                hitbox.setOutlineThickness(HITBOX_DRAW_SIZE);
                hitbox.setPosition(sf::Vector2f(m_hitbox.left, m_hitbox.top));
                win->draw(hitbox);
            }
            onscreen = true;
            win->draw(m_sprite);
        }
    }

    inline bool check_collision(sf::FloatRect *hit){
        return m_hitbox.intersects(*hit);
    }

    inline void load_texture(){
        if(!m_texture.loadFromFile("./textures/test/objs/rock.png")){
            std::cerr << "Failed to load texture\n";
            exit(EXIT_FAILURE);
        }
        m_sprite.setTexture(m_texture);
        sf::Vector2f sprite_pos = m_sprite.getPosition();
        sf::FloatRect sprite_size = m_sprite.getLocalBounds();
        m_hitbox.left = sprite_pos.x;
        m_hitbox.top = sprite_pos.y;
        m_hitbox.width = sprite_size.width;
        m_hitbox.height = sprite_size.height;
    }

    bool onscreen;

private:
    sf::Vector2f m_pos;
    sf::Vector2f m_offset_pos;
    sf::FloatRect m_hitbox;
    sf::Texture m_texture;
    sf::Sprite m_sprite;


};

#endif