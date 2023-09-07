#include <SFML/Graphics.hpp>
#include "../util/keys.hpp"
#include "../util/vector.hpp"
#include "../game/state.hpp"
#include "../animation/animator.hpp"
#include "player.hpp"

void Player::load_texture(){
    // Handle the texture and sprite initialization
    // if (!m_texture.loadFromFile("./textures/characters/Protag(V1).png")){
    //     std::cerr << "\033[31mError Loading Player Sprite. Closing program\033[0m\n";
    //     exit(EXIT_FAILURE);
    // }
    // sf::Vector2f textureSize = static_cast<sf::Vector2f>(m_texture.getSize());

    m_animator.load_sprites();
    m_sprite = m_animator.get_sprite(m_state);

    // m_sprite.setTexture(m_texture);
    // m_hitbox = static_cast<sf::FloatRect>(m_sprite.getTextureRect());
    sf::FloatRect sprite_rect = m_sprite.getGlobalBounds();
    m_hitbox.left = sprite_rect.left;
    m_hitbox.top = sprite_rect.top;
    m_hitbox.width = sprite_rect.width;
    m_hitbox.height = sprite_rect.height;
    m_sprite.setScale(2, 2);

    // m_hitbox.width += 12;
    // m_hitbox.height += 60; // Yeah I pulled these numbers out of my ass
}

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
        hitbox.setFillColor(sf::Color(0, 0, 0, 0));
        hitbox.setOutlineColor(sf::Color(255, 255, 255));
        hitbox.setOutlineThickness(HITBOX_DRAW_SIZE);
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