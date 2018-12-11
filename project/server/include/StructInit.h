#ifndef StructInit_h
#define StructInit_h

#include <vector>
#include <map>

#include "Hex.h"
#include "CellState.h"

#define START_AREA 7

enum Move {
    UP = 0,
    RIGHT_UP = 1,
    RIGHT_DOWN = 2,
    DOWN = 3,
    LEFT_DOWN = 4,
    LEFT_UP = 5
};

struct Person {
    int area_sq;
    Hex point;
    int kills;
    int bonus_effect;
    Person(Hex point)
            :area_sq(START_AREA), point(point), kills(0), bonus_effect(0) {};
};

struct CellState {
    int id;
    int state;
    CellState(int id, int state)
            : id(id), state(state) {};
};

//typedef struct Per Person;

typedef std::map<Hex, int> Areas;
typedef std::map<Hex, CellState> Tails;
typedef std::map<int, Person> Persons;

#endif /* StructInit_h */
