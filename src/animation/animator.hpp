#ifndef INDIE_GAME_ANIMATOR_HPP
#define INDIE_GAME_ANIMATOR_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum class PlayerState;

// This class will be added to an object that requires animation
class CAnimator{
public:
    CAnimator() = default;
    inline explicit CAnimator(const std::string &path){
        m_path = path;
    }
    inline ~CAnimator() {}

    void load_sprites();

    sf::Sprite get_sprite(PlayerState state);

private:

    std::string m_path;

    sf::Texture m_sheet;
    std::vector<sf::Sprite> m_sprites;

    PlayerState m_player_state;
};

#endif