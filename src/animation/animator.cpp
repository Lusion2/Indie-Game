#include <iostream>
#include <sstream>
#include <string>
#include "animator.hpp"

void CAnimator::load_sprites(){
    // Load each animation 
    std::stringstream path;
    path << m_dir;
    load_animation(path, "idle", 10);
    load_animation(path, "walk", 8);
}

void CAnimator::load_animation(std::stringstream &path_stream, const std::string& type, int frames){
    path_stream << type << ".png";
    sf::Texture sheet;
    if(!sheet.loadFromFile(path_stream.str())){
        std::cerr << "Failed to load sprite sheet" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_sheet_map.insert({ type, sheet });

    // Create the sprite and put it in the sprite map
    for(int i = 0; i < frames; i++){
        sf::Sprite sprite(m_sheet_map.at(type), sf::IntRect(i * 48, 0, 48, 48));
        std::stringstream name;
        name << type << "_" << i;
        m_sprite_map.insert({name.str(), sprite});
    }
    path_stream.str("");
    path_stream << m_dir;
}

sf::Sprite CAnimator::get_sprite(PlayerState state, int animation_frame){
    std::stringstream sprite_name;
    switch(state){
        case PlayerState::idle:
            sprite_name << "idle_" << animation_frame;
            return m_sprite_map.at(sprite_name.str());
            break;

        case PlayerState::walk:
            sprite_name << "walk_" << animation_frame;
            return m_sprite_map.at(sprite_name.str());

        default:
            return {};
    }

}