#include <SFML/Graphics.hpp>
#include "../util/keys.hpp"
#include "../util/vector.hpp"
#include "../game/state.hpp"
#include "player.hpp"

void Player::update(Keys *keys){
    move(keys);
}

void Player::draw(sf::RenderWindow *win, State *state, bool DEBUG){
    // t_pos is the screenspace position
    sf::Vector2f t_pos;
    CameraState cam_state = state->get_camera_state();
    sf::Vector2f cam_pos = state->get_camera_pos();
    
    // Setting the screenspace pos of the player depending
    // on the camera state
    if(cam_state == CameraState::follow){
        t_pos = PlayerOffset;
    }
    else if (cam_state == CameraState::lock){
        t_pos = m_pos + PlayerOffset - cam_pos;
    }
    m_hitbox.left = t_pos.x + HitBoxOffset.x;
    m_hitbox.top = t_pos.y + HitBoxOffset.y;

    // Draw the hitbox if DEBUG is true
    if(DEBUG){
        sf::RectangleShape hitbox;
        hitbox.setSize(sf::Vector2f(m_hitbox.width, m_hitbox.height));
        hitbox.setPosition(sf::Vector2f(m_hitbox.left, m_hitbox.top));
        hitbox.setFillColor(sf::Color(255, 255, 255));
        win->draw(hitbox);
    }

    m_sprite.setPosition(t_pos);
    win->draw(m_sprite);
}

void Player::move(Keys *keys){
    // The direction will only be 8 directions 45 degrees apart
    // When the player moves, the state changes to walk, else it's idle
    sf::Vector2f dir(0, 0);
    m_state = PlayerState::idle;
    if(keys->w){
        dir.y -= 1;
        m_state = PlayerState::walk;
    }
    if(keys->s){
        dir.y += 1;
        m_state = PlayerState::walk;
    }
    if(keys->a){
        dir.x -= 1;
        m_state = PlayerState::walk;
    }
    if(keys->d){
        dir.x += 1;
        m_state = PlayerState::walk;
    }
    
    // Normalize the direction to fix faster speeds when going diagonal
    dir = vec2_normalize(&dir);
    m_pos += dir * playerSpeed;
}