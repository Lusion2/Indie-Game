#ifndef INDIE_GAME_STATE_HPP
#define INDIE_GAME_STATE_HPP

#include <SFML/Graphics.hpp>

struct Camera{
    sf::Vector2f pos;
};

enum class CameraState{
    follow,
    lock,
};

class State{
public:

    inline explicit State(CameraState state){
        m_camera_state = state;
    }
    inline explicit State(){
        m_camera_state = CameraState::follow;
    }
    inline ~State(){}

    inline CameraState get_camera_state(){
        return m_camera_state;
    }
    inline void set_camera_state(CameraState state){
        m_camera_state = state;
    }
    inline sf::Vector2f get_camera_pos(){
        return m_camera.pos;
    }
    inline void set_camera_pos(sf::Vector2f pos){
        if(m_camera_state == CameraState::follow){
            m_camera.pos = pos;
        }
    }


private:

    CameraState m_camera_state;
    Camera m_camera;

};

#endif