#include <SFML/Graphics.hpp>
#include "../util/keys.hpp"
#include "../util/vector.hpp"
#include "../game/state.hpp"
#include "../animation/animator.hpp"
#include "player.hpp"

void Player::load_texture(){
    m_animator.load_sprites();
    m_sprite = m_animator.get_sprite(m_state, 0);

    sf::FloatRect sprite_rect = m_sprite.getGlobalBounds();
    m_hitbox.left = sprite_rect.left;
    m_hitbox.top = sprite_rect.top;
    m_hitbox.width = sprite_rect.width;
    m_hitbox.height = sprite_rect.height;
    m_sprite.setScale(2, 2);
}

void Player::update(Keys *keys, float deltaTime){
    m_last_pos = m_pos;
    move(keys);
    update_animation(deltaTime);
}

void Player::update_animation(float deltaTime){
    set_animation_data();
    
    // This whole thing is a bit confusing to read because of the m_current_animation pointer, so I'll explain it
    //
    // First we check if it's time to update the animation frame or check if there's been a state change, if so, update the frame
    // After, we check if we've reached the end of the animation, then we reset the animation to zero
    // Then we set the sprite to the current animation frame using the animator component, flip it if it needs to be flipped,
    // and update the hitbox 
    //
    if(deltaTime - m_current_animation->time_last_frame >= m_current_animation->time_between_frames || m_state != m_prev_state){
        if(m_state != m_prev_state){
            m_current_animation->curr_anim_frame = 0;
        }
        m_current_animation->time_last_frame = deltaTime;
        if(m_current_animation->curr_anim_frame < m_current_animation->anim_frames){
            m_current_animation->curr_anim_frame++;
        }
        if(m_current_animation->curr_anim_frame == m_current_animation->anim_frames){
            m_current_animation->curr_anim_frame = 0;
        }
        m_sprite = m_animator.get_sprite(m_state, m_current_animation->curr_anim_frame);
        sf::FloatRect sprite_rect = m_sprite.getGlobalBounds();
        
        // Flip the sprite if we face left
        if(m_dir == EntityDir::left){
            sf::IntRect texture_rect = m_sprite.getTextureRect();
            m_sprite.setTextureRect(sf::IntRect(texture_rect.left + texture_rect.width, texture_rect.top, -texture_rect.width, texture_rect.height));
        }
        m_hitbox = sprite_rect;
        m_sprite.setScale(2, 2);
        m_prev_state = m_state;
    }
}

void Player::set_animation_data(){
    switch(m_state){
        case PlayerState::idle:
            m_current_animation = &m_idle_data;
            break;
        case PlayerState::walk:
            m_current_animation = &m_walk_data;
            break;
        default:
            break;
    }
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
        hitbox.setOutlineThickness(HITBOX_DRAW_OUTLINE_SIZE);
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
        m_dir = EntityDir::left;
    }
    if(keys->d){
        dir.x += 1;
        m_state = PlayerState::walk;
        m_dir = EntityDir::right;
    }
    
    // Normalize the direction to fix faster speeds when going diagonal
    dir = vec2_normalize(&dir);
    m_pos += dir * playerSpeed;
}