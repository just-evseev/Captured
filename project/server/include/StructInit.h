#ifndef StructInit_h
#define StructInit_h

#include <vector>
#include <map>

#include "Hex.h"

#define START_AREA 7

enum Move {
    UP = 0,
    RIGHT_UP = 1,
    RIGHT_DOWN = 2,
    DOWN = 3,
    LEFT_DOWN = 4,
    LEFT_UP = 5
};

typedef std::vector<Hex> PlayerArea;
typedef std::vector<Hex> PlayerTails;

struct Person {
    int move;
    int areaSquare;
    Hex point;
    int kills;
    int bonusEffect;
    PlayerArea playerArea;
    PlayerTails playerTails;
    Person(Hex point)
            :move(0), areaSquare(START_AREA), point(point), kills(0), bonusEffect(0) {};
};

struct CellState {
    int id;
    int state;
    CellState(int id, int state)
            : id(id), state(state) {};
};

struct QPlusState {
    int q;
    int state;
    QPlusState(int q, int state)
            : q(q), state(state) {};
};

typedef std::map<Hex, int> Areas;
typedef std::map<Hex, CellState> Tails;
typedef std::map<int, Person> Persons;

#endif /* StructInit_h */
