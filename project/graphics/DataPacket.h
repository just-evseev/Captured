//
// Created by Святослав Кряжев on 27.11.2018.
//

#ifndef GRAPHICS_DATAPACKET_H
#define GRAPHICS_DATAPACKET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Hex.h"
#include "Person Struct.h"

struct DataPacket {
    std::map<Hex, int> areas;
    std::map<Hex, int> tails;
    std::map<Hex, int> players;

    DataPacket();

    void make(Person& person)  {
        areas.clear();
        tails.clear();

        for (auto area : person.playerArea) {
            area.q -= person.point.q;
            area.r -= person.point.r;

            areas.emplace(area, 1);
        }

        for (auto tail : person.playerTails) {
            tail.q -= person.point.q;
            tail.r -= person.point.r;

            tails.emplace(tail, 1);
        }

    };
};

#endif //GRAPHICS_DATAPACKET_H
