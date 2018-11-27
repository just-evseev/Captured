//
// Created by Святослав Кряжев on 25.11.2018.
//

#include "Player.h"

Player::Player(sf::Vector2f pos)
        : position(pos), size(60.f, 60.f) {

    std::clog << "Player: created" << std::endl;
}

Player::~Player() {
    std::clog << "Player: destroyed" << std::endl;
}

sf::Vector2f Player::get_pos() {
    return position;
}

sf::Vector2f Player::get_size() {
    return size;
}
