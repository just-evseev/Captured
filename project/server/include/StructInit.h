#ifndef StructInit_h
#define StructInit_h

#include <vector>

struct XY {
    float x;
    float y;
};

typedef struct XY Vector;
typedef struct XY Coord;
typedef std::vector<Coord> VectorOfCoord;

enum Move {
    UP = 0,
    RIGHT_UP = 1,
    RIGHT_DOWN = 2,
    DOWN = 3,
    LEFT_DOWN = 4,
    LEFT_UP = 5
};

#endif /* StructInit_h */
