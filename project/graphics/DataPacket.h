//
// Created by Святослав Кряжев on 27.11.2018.
//

#ifndef GRAPHICS_DATAPACKET_H
#define GRAPHICS_DATAPACKET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct DataPacket {
    struct Area {
        std::vector<sf::Vector2f> points;
        int id;
    };

    struct Enemy {
        sf::Vector2f pos;
        std::vector<sf::Vector2f> tails;
        int id;
    };

    std::vector<Area> areas;
    std::vector<Enemy> players;

    void move_up(float val);
    void move_down(float val);
    void move_left(float val);
    void move_right(float val);
};

#endif //GRAPHICS_DATAPACKET_H
