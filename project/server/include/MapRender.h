#ifndef MapRender_hpp
#define MapRender_hpp

#include <stdio.h>

#include "StructInit.h"

class MapRender {
public:

    MapRender();

    virtual ~MapRender();

    Coord createNewPlayer(); // Добавить нового игрока

    void addWayCurve(Coord coord); // Добавить кривую пути в список пути
    void updatePlayerCoord(Coord coord);

private:

    void createAreaOfNewPlayer(Coord coord);

    int searchInCoordVector(Coord coord);

    void updatePlayerArea(); // Обновить зону владения игрока

    Coord generateCoord();
    float generateNumber();

    bool isInArea(Coord coord); // Точка в своей зоне?
    bool isWayEmpty(VectorOfCoord arrayOfWay); // Существует ли путь?

    Coord playerCoord;
    VectorOfCoord arrayOfAreaCoord;
    VectorOfCoord arrayOfWay;
};

#endif /* MapRender_hpp */
