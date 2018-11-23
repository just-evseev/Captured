#ifndef StructInit_h
#define StructInit_h

struct XY {
    float *x;
    float *y;
};

typedef struct XY Vector;
typedef struct XY Coord;
typedef struct XY* ArrayOfCoord; //TASK: Какой вид Список/Массив/Хеш-таблица????

struct PlayerArea {
    ArrayOfCoord AreaArray;
};

struct PlayerWayArray {
    ArrayOfCoord WayArray;
};

#endif /* StructInit_h */
