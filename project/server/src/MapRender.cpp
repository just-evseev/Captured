#include "MapRender.h"

Coord MapRender::createNewPlayer() {
    Coord coord = generateCoord();
    createAreaOfNewPlayer(coord);
    return coord;
}

void  MapRender::createAreaOfNewPlayer(Coord coord) {
    Coord newCoord;
    newCoord.x = coord.x + 0.001;
    newCoord.y = coord.y + 0.001;
    this->arrayOfAreaCoord.push_back(newCoord);
    newCoord.x = coord.x + 0.001;
    newCoord.y = coord.y - 0.001;
    this->arrayOfAreaCoord.push_back(newCoord);
    newCoord.x = coord.x - 0.001;
    newCoord.y = coord.y - 0.001;
    this->arrayOfAreaCoord.push_back(newCoord);
    newCoord.x = coord.x - 0.001;
    newCoord.y = coord.y + 0.001;
    this->arrayOfAreaCoord.push_back(newCoord);
}

void MapRender::updatePlayerCoord(Vector vector) {
    this->playerCoord.x += vector.x;
    this->playerCoord.y += vector.y;
}

Coord MapRender::generateCoord() {
    Coord mem;
    return mem;
}

VectorOfCoord MapRender::addWayCurve(Coord coord) {
    VectorOfCoord mem;
    return mem;
}

bool MapRender::isInArea(Coord coord) {
    for (Coord n : this->arrayOfAreaCoord) {
        
    }

    return false;
}

bool MapRender::isWayEmpty(VectorOfCoord arrayOfWay) {
    return arrayOfWay.empty();
}
