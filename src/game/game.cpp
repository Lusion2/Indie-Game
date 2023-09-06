#include "game.hpp"

//*******************
//*PUBLIC FUNCTIONS
//*******************
void Game::on_update(){
    // Update deltaTime
    m_deltaTime = m_clock.getElapsedTime().asSeconds();

    // Poll events and keypresses
    poll_events();
    check_keypresses();

    // Update the player and the camera position
    m_player->update(&m_keys);
    if(m_state->get_camera_state() == CameraState::follow){
        m_state->set_camera_pos(*m_player->get_pos());
    }

    for (GameObject *obj : m_objs){
        if(obj->check_collision(m_player->get_hitbox())){
            // TODO: Handle collision
        }
        // obj->update();
    }
}

void Game::on_render(){
    // Clear the screen
    m_win->clear();
    
    // Draw the player
    m_player->draw(m_win, m_state, DEBUG);

    // Draw each game object
    for(GameObject *obj : m_objs){
        obj->draw(m_win, m_state, DEBUG);
    }

    // Display the frame
    m_win->display();
}

//*******************
//*PRIVATE FUNCTIONS
//*******************
void Game::check_keypresses(){
    sf::Keyboard k;
    m_keys.w = false;
    m_keys.s = false;
    m_keys.a = false;
    m_keys.d = false;
    m_keys.space = false;
    m_keys.enter = false;
    if (k.isKeyPressed(k.Escape)){
        m_win->close();
    }
    if (k.isKeyPressed(k.W) || k.isKeyPressed(k.Up)){
        m_keys.w = true;
    }
    if (k.isKeyPressed(k.S) || k.isKeyPressed(k.Down)){
        m_keys.s = true;
    }
    if (k.isKeyPressed(k.A) || k.isKeyPressed(k.Left)){
        m_keys.a = true;
    }
    if (k.isKeyPressed(k.D) || k.isKeyPressed(k.Right)){
        m_keys.d = true;
    }
    if (k.isKeyPressed(k.Space)){
        m_keys.space = true;
    }
    if (k.isKeyPressed(k.Enter)){
        m_keys.enter = true;
    }
    if (k.isKeyPressed(k.F1)){
        if (m_deltaTime - m_timeSinceLastKeyPress >= 0.25){
            DEBUG = !DEBUG;
            m_timeSinceLastKeyPress = m_deltaTime;
        }
    }
    if (k.isKeyPressed(k.F2)){
        if (m_deltaTime - m_timeSinceLastKeyPress >= 0.25){
            m_state->set_camera_state(CameraState::lock);
            m_timeSinceLastKeyPress = m_deltaTime;
        }
    }
    if (k.isKeyPressed(k.F3)){
        if (m_deltaTime - m_timeSinceLastKeyPress >= 0.25){
            m_state->set_camera_state(CameraState::follow);
            m_timeSinceLastKeyPress = m_deltaTime;
        }
    }
}
