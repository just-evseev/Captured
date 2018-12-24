//
// Created by Святослав Кряжев on 27.11.2018.
//

#ifndef GRAPHICS_DATAPACKET_H
#define GRAPHICS_DATAPACKET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Hex.h"
#include "Move.h"
#include "Person Struct.h"

#define VISIBLE_TILES 18

struct PlayerProperty {
    int id;
    Move move;

    PlayerProperty(int id, Move move)
    : id(id), move(move) {};
};

struct DataPacket {
    std::map<Hex, int> areas;
    std::map<Hex, int> tails;
    std::map<Hex, PlayerProperty> players;

    int my_id;



    DataPacket();

    void make(Persons people, int currId)  {
        areas.clear();
        tails.clear();
        players.clear();

        Hex my_pos = people.at(currId).point;
        my_id = currId;

        for (auto& person : people) {
            for (auto area : person.second.playerArea) {
                area.q -= my_pos.q;
                area.r -= my_pos.r;
                if (std::abs(area.q) < VISIBLE_TILES && std::abs(area.r) < VISIBLE_TILES)
                    areas.emplace(area, person.first);
            }

            for (auto tail : person.second.playerTails) {
                tail.q -= my_pos.q;
                tail.r -= my_pos.r;

                if (std::abs(tail.q) < VISIBLE_TILES && std::abs(tail.r) < VISIBLE_TILES)
                    tails.emplace(tail, person.first);
            }

            if (person.first == currId)
                continue;

            person.second.point.q -= my_pos.q;
            person.second.point.r -= my_pos.r;

            players.emplace(person.second.point, PlayerProperty(person.first, Move(person.second.move)));
        }

    };
};

#endif //GRAPHICS_DATAPACKET_H
