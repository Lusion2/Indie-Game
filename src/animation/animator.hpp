#ifndef INDIE_GAME_ANIMATOR_HPP
#define INDIE_GAME_ANIMATOR_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

enum class PlayerState{
    idle, walk, run, hit,
};

enum class EntityState;

enum class EntityDir{
    left, right,
};

// This class will be added to an object that requires animation
class CAnimator{
public:
    CAnimator() = default;
    inline explicit CAnimator(const std::string &path){
        m_dir = path;
    }
    inline ~CAnimator() {}

    void load_sprites();


    // get_sprite returns the sprite at the player state and animation frame
    // The animation frame variable starts from 0
    // This function is overloaded for the player and entities (not implemented yet)
    sf::Sprite get_sprite(PlayerState state, int animation_frame);
    sf::Sprite get_sprite(EntityState state, int animation_frame);

private:

    void load_animation(std::stringstream &path, const std::string& type, int frames);

    std::string m_dir;

    std::unordered_map<std::string, sf::Texture> m_sheet_map;
    std::unordered_map<std::string, sf::Sprite> m_sprite_map;

    PlayerState m_player_state;
};

#endif