//
// Created by Святослав Кряжев on 27.11.2018.
//

#include "DataPacket.h"

DataPacket::DataPacket() {
    //std::clog << "DataPacket: created" << std::endl;

//    areas.emplace(Hex(0, -4), 1);
//    areas.emplace(Hex(1, -4), 1);
//    areas.emplace(Hex(0, -5), 1);
//    areas.emplace(Hex(0, -6), 1);
//    areas.emplace(Hex(2, -4), 1);
//    areas.emplace(Hex(3, -4), 1);
//
//    areas.emplace(Hex(-1, -4), 1);
//    areas.emplace(Hex(-3, -6), 2);
//    areas.emplace(Hex(5, -9), 1);
//    areas.emplace(Hex(0, -9), 1);
//    areas.emplace(Hex(0, 9), 1);
//    areas.emplace(Hex(-4, -4), 1);
//
//    areas.emplace(Hex(4, -3), 1);
//    areas.emplace(Hex(5, -3), 1);
//    areas.emplace(Hex(4, -2), 1);
//    areas.emplace(Hex(3, -1), 1);
//    areas.emplace(Hex(3, 1), 1);
//    areas.emplace(Hex(4, 1), 1);
//    areas.emplace(Hex(2, 2), 1);
//    areas.emplace(Hex(4, -4), 1);
//    areas.emplace(Hex(-4, 4), 1);
//    areas.emplace(Hex(-5, 4), 1);
//    areas.emplace(Hex(-11, 7), 1);

    areas.emplace(Hex(0, 0), 1);
    areas.emplace(Hex(0, 1), 1);
    areas.emplace(Hex(0, -1), 1);
    areas.emplace(Hex(1, 0), 1);
    areas.emplace(Hex(-1, 0), 1);
    areas.emplace(Hex(1, -1), 1);
    areas.emplace(Hex(-1, 1), 1);


    players.emplace(Hex(5, -7), 1);
}