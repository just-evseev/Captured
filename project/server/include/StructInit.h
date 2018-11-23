#ifndef StructInit_h
#define StructInit_h

#include <vector>

struct XY {
    float *x;
    float *y;
};

typedef struct XY Vector;
typedef struct XY Coord;
typedef std::vector<Coord> VectorOfCoord; //TASK: Сделать вектор

#endif /* StructInit_h */