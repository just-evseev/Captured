//
// Created by Святослав Кряжев on 25.11.2018.
//

#ifndef GRAPHICS_PLAYER_H
#define GRAPHICS_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Player {
private:
    sf::Vector2f position;
    sf::Vector2f size;

public:
    Player(sf::Vector2f pos);
    ~Player();

    sf::Vector2f get_pos();
    sf::Vector2f get_size();
};


#endif //GRAPHICS_PLAYER_H
