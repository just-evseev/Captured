//
// Created by Святослав Кряжев on 27.11.2018.
//

#ifndef GRAPHICS_DATAPACKET_H
#define GRAPHICS_DATAPACKET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Hex.h"

struct DataPacket {
    std::map<Hex, int> areas;
    std::map<Hex, int> tails;
    std::map<Hex, int> players;

    DataPacket();

    void unpack()  {

    };
};

#endif //GRAPHICS_DATAPACKET_H
