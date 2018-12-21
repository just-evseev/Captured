//
// Created by Святослав Кряжев on 18.12.2018.
//

#ifndef GRAPHICS_PERSON_STRUCT_H
#define GRAPHICS_PERSON_STRUCT_H

#include <vector>
#include <map>
#include "Hex.h"

typedef std::vector<Hex> PlayerArea;
typedef std::vector<Hex> PlayerTails;


struct Person {
    int move;
    Hex point;
    PlayerArea playerArea;
    PlayerTails playerTails;
    Person(Hex point)
            :move(0), point(point) {};
};

typedef std::map<int, Person> Persons;

#endif //GRAPHICS_PERSON_STRUCT_H
