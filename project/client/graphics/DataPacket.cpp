//
// Created by Святослав Кряжев on 27.11.2018.
//

#include "DataPacket.h"

void DataPacket::move_up(float val) {
    for (auto& area : areas)
        for (auto& point : area.points)
            point.y -= val;
}

void DataPacket::move_down(float val) {
    for (auto& area : areas)
        for (auto& point : area.points)
            point.y += val;
}

void DataPacket::move_left(float val) {
    for (auto& area : areas)
        for (auto& point : area.points)
            point.x -= val;
}

void DataPacket::move_right(float val) {
    for (auto& area : areas)
        for (auto& point : area.points)
            point.x += val;
}