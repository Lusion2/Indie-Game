#include <iomanip>
#include <sstream>
#include <thread>
#include <string>
#include "game.hpp"
#include "../level_data/level.hpp"

//*******************
//*PUBLIC FUNCTIONS
//*******************
void Game::on_update(){
    // Update time stuff
    float currentTime = m_clock.getElapsedTime().asSeconds();
    m_deltaTime = currentTime - m_lastFrameTime;

    // Poll events and keypresses
    poll_events();
    check_keypresses();
    
    // Update the player and the camera position
    m_player.update(&m_keys);
    if(m_state.get_camera_state() == CameraState::follow){
        m_state.set_camera_pos(*m_player.get_pos());
    }

    // Update the last frame time
    m_lastFrameTime = currentTime;
}

void Game::on_render(){
    // Clear the screen
    m_win.clear();

    // Draw the player
    m_player.draw(&m_win, &m_state, DEBUG);

    // Check obj collisions and drawing
    // TODO: I do not want to loop through all the objs twice... need to find a better solution than doing it in the render function
    check_all_collisions();

    // Draw the debug info
    draw_debug();

    // Display the frame
    m_win.display();
}

//*********************
//* Drawing debug info
//*********************
void Game::draw_debug()
{
    // Begin with displaying the FPS
    std::stringstream buffer;
    buffer << "FPS: " << (int)(1.0f / m_deltaTime);
    sf::Text out(buffer.str(), m_font, 20);
    out.setFillColor(sf::Color(150, 150, 150));
    out.setOutlineColor(sf::Color(0, 0, 0));
    out.setOutlineThickness(5);
    out.setPosition(0, 0);
    m_win.draw(out);

    // Display the Debug mode
    buffer.str("");
    buffer << "Debug Mode: ";
    switch((int)DEBUG){
        case 1:
            buffer << "On";
            break;
        case 0:
            buffer << "Off";
            break;
        default:
            break;
    }

    // Display the current camera mode
    out.setString(buffer.str());
    out.setPosition(0, 30);
    m_win.draw(out);
    buffer.str("");
    buffer << "Camera Mode: ";
    switch(m_state.get_camera_state()){
        case CameraState::follow:
            buffer << "Follow";
            break;
        case CameraState::lock:
            buffer << "Lock";
            break;
        default:
            break;
    }
    out.setString(buffer.str());
    out.setPosition(0, 60);
    m_win.draw(out);
}

void Game::load_map(){
    for(int y = 0; y < LEVEL.size(); y++){
        for(int x = 0; x < LEVEL.at(y).size(); x++){
            if(LEVEL.at(y).at(x) == 1){
                GameObject obj(x * BLOCKSIZE, y * BLOCKSIZE);
                add_object(obj);
            }
        }
    }
}

//*******************
//*PRIVATE FUNCTIONS
//*******************
void Game::check_all_collisions(){
    // Handle GameObject logic and drawing
    // This is done in the render loop so we don't need to loop through all the objects twice per frame
    for(GameObject obj : m_objs){
        if(obj.onscreen && obj.check_collision(m_player.get_hitbox())){
            // TODO: Handle Collisions
        }
        obj.draw(&m_win, &m_state, DEBUG);
    }
}

void Game::draw_all_objs(){
    for(GameObject obj : m_objs){
        obj.draw(&m_win, &m_state, DEBUG);
    }
}

void Game::check_keypresses(){
    sf::Keyboard k;
    m_keys.w = false;
    m_keys.s = false;
    m_keys.a = false;
    m_keys.d = false;
    m_keys.space = false;
    m_keys.enter = false;
    if (k.isKeyPressed(k.Escape)){
        m_win.close();
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
        // Swap debug modes
        if (m_lastFrameTime - m_timeSinceLastKeyPress >= 0.25){
            DEBUG = !DEBUG;
            if(DEBUG){
                std::cout << "\33[34mDEBUG: \33[1mTrue\033[0m\n";
            }
            else{
                std::cout << "\033[33mDEBUG: \033[1mFalse\033[0m\n";
            }
            m_timeSinceLastKeyPress = m_lastFrameTime;
        }
    }
    if (k.isKeyPressed(k.F2)){
        // Switch the camera state to lock
        if (m_lastFrameTime - m_timeSinceLastKeyPress >= 0.25){
            m_state.set_camera_state(CameraState::lock);
            m_timeSinceLastKeyPress = m_lastFrameTime;
        }
    }
    if (k.isKeyPressed(k.F3)){
        // Switch the camera state to follow
        if (m_lastFrameTime - m_timeSinceLastKeyPress >= 0.25){
            m_state.set_camera_state(CameraState::follow);
            m_timeSinceLastKeyPress = m_lastFrameTime;
        }
    }
}
