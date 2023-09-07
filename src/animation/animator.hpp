#ifndef INDIE_GAME_ANIMATOR_HPP
#define INDIE_GAME_ANIMATOR_HPP

#include <SFML/Graphics.hpp>
#include <string>

enum class PlayerState;

// This class will be added to an object that requires animation
class Animator{
public:
    Animator() = default;
    inline explicit Animator(const std::string &path){
        m_path = path;
    }
    inline ~Animator(){}

    inline void load_sprites(){
        m_sheet.loadFromFile(m_path);
        sf::Sprite sprite;
        sprite.setTexture(m_sheet);
        sprite.setTextureRect(static_cast<sf::IntRect>(sf::FloatRect(12, 0, 32, 56)));
        m_sprites.push_back(sprite);
    }

    inline sf::Sprite get_sprite(PlayerState state){
        return m_sprites[0];
    }

private:

    std::string m_path;

    sf::Texture m_sheet;
    std::vector<sf::Sprite> m_sprites;

    PlayerState m_player_state;
};

#endif