#ifndef MapRender_hpp
#define MapRender_hpp

#include <stdio.h>

#include "StructInit.h"

class MapRender {
public:

    MapRender();

    virtual ~MapRender();

    Coord createNewPlayer(); // Добавить нового игрока

    VectorOfCoord addWayCurve(Coord coord); // Добавить кривую пути в список пути
    VectorOfCoord updatePlayerArea(VectorOfCoord arrayOfCoord); // Обновить зону владения игрока
    Coord updatePlayerCoord(Coord coord);

    bool isInArea(Coord coord); // Точка в своей зоне?
    bool isWayEmpty(VectorOfCoord arrayOfWay); // Существует ли путь?

private:

    Coord playerCoord;
    VectorOfCoord arrayOfAreaCoord;
    VectorOfCoord arrayOfWay;

};

#endif /* MapRender_hpp */
