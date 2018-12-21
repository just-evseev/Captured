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

    void make(Persons people, int currId)  {
        areas.clear();
        tails.clear();

        Hex my_pos = people.at(currId).point;

        for (auto& person : people) {
            for (auto area : person.second.playerArea) {
                area.q -= my_pos.q;
                area.r -= my_pos.r;

                areas.emplace(area, person.first);
            }

            for (auto tail : person.second.playerTails) {
                tail.q -= my_pos.q;
                tail.r -= my_pos.r;

                tails.emplace(tail, person.first);
            }

            if (person.first == currId)
                continue;

            players.emplace(person.second.point, person.first);
        }

    };
};

#endif //GRAPHICS_DATAPACKET_H
