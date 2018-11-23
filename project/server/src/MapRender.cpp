#include "MapRender.h"

Coord MapRender::createNewPlayer() {
    Coord coord = generateCoord();
    createAreaOfNewPlayer(coord);
    return coord;
}

void MapRender::addWayCurve(Coord coord) {
    this->arrayOfWay.push_back(coord);
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

Coord MapRender::generateCoord() { //TODO: Build this method
    Coord coord;
    float lll = 0.01;
    coord.x += lll;
    coord.y += lll;
    return coord;
}

bool MapRender::isInArea(Coord coord) { //TODO: Build this method
    for (Coord n : this->arrayOfAreaCoord) {
        
    }

    return false;
}

bool MapRender::isWayEmpty(VectorOfCoord arrayOfWay) {
    return arrayOfWay.empty();
}
