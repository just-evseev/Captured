#ifndef StructInit_h
#define StructInit_h

#include <vector>
#include <map>

#include "Hex.h"

typedef std::map<Hex, int> Areas;
typedef std::map<Hex, int> Tails;

typedef std::map<int, Hex> Points;

enum Move {
    UP = 0,
    RIGHT_UP = 1,
    RIGHT_DOWN = 2,
    DOWN = 3,
    LEFT_DOWN = 4,
    LEFT_UP = 5
};

#endif /* StructInit_h */
