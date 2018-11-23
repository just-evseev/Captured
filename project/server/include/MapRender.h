#ifndef MapRender_hpp
#define MapRender_hpp

#include <stdio.h>

#include "StructInit.h"

class MapRender {
public:

    MapRender();

    virtual ~MapRender();

    Coord createNewPlayer(); // Добавить нового игрока

    ArrayOfCoord addWayCurve(Coord coord); // Добавить кривую пути в список пути
    ArrayOfCoord updatePlayerArea(ArrayOfCoord arrayOfCoord); // Обновить зону владения игрока
    Coord updatePlayerCoord(Coord coord);

    bool isInArea(Coord coord); // Точка в своей зоне?
    bool isWayEmpty(ArrayOfCoord arrayOfWay); // Существует ли путь?

private:

    Coord playerCoord;
    ArrayOfCoord arrayOfAreaCoord;
    ArrayOfCoord arrayOfWay;

};

#endif /* MapRender_hpp */
