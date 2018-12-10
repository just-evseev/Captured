#ifndef StructInit_h
#define StructInit_h

#include <vector>
#include <map>

#include "Hex.h"
#include "CellState.h"

enum Move {
    UP = 0,
    RIGHT_UP = 1,
    RIGHT_DOWN = 2,
    DOWN = 3,
    LEFT_DOWN = 4,
    LEFT_UP = 5
};

struct Per {
    int id;
    int state; // хз зачем эта характеристика
    int area_sq;
    int kills;
    int bonus_effect;
};

typedef struct Per Person;

typedef std::map<int, Person> Persons;

typedef std::map<Hex, int> Areas;
typedef std::map<Hex, CellState> Tails;
typedef std::map<int, Hex> Points;

#endif /* StructInit_h */
