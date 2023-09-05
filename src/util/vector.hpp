#ifndef INDIE_GAME_VECTOR_HPP
#define INDIE_GAME_VECTOR_HPP

#include <SFML/Graphics.hpp>
#include <math.h>

inline float vec2_len(sf::Vector2f *v){
    return sqrt(v->x*v->x + v->y*v->y);
}


inline sf::Vector2f vec2_normalize(sf::Vector2f *v){
    float l = vec2_len(v);
    if(l == 0){
        return {};
    }
    return sf::Vector2f(v->x / l, v->y / l);
}


#endif