#include "animator.hpp"

void CAnimator::load_sprites(){
    // Load the sprite sheet from file
    m_sheet.loadFromFile(m_path);
    
    // Create the sprite and put it in the sprite vector
    sf::Sprite sprite;
    sprite.setTexture(m_sheet);
    sprite.setTextureRect(sf::IntRect(12, 0, 32, 56));
    m_sprites.push_back(sprite);
}

sf::Sprite CAnimator::get_sprite(PlayerState state){
    return m_sprites[0];
}