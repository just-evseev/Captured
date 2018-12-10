//
// Created by Ilya on 06/12/2018.
//

#include "../include/RenderManager.h"

void RenderManager::acceptPlayer(int id) {
    Hex point = this->createNewPlayer(id);
    this->createAreaOfNewPlayer(point, id);
}

void RenderManager::getPlayerCoord(Move move, int id) {
    Hex point = this->points.at(id);
    switch (move) {
        case Move::UP:
            point.updateCoord(point.q, point.r - 1);
            break;
        case Move::RIGHT_UP:
            point.updateCoord(point.q + 1, point.r - 1);
            break;
        case Move::RIGHT_DOWN:
            point.updateCoord(point.q + 1, point.r);
            break;
        case Move::DOWN:
            point.updateCoord(point.q, point.r + 1);
            break;
        case Move::LEFT_DOWN:
            point.updateCoord(point.q - 1, point.r + 1);
            break;
        case Move::LEFT_UP:
            point.updateCoord(point.q - 1, point.r);
            break;
        default:
            break;
    }
    this->points.at(id) = point;
}

Hex RenderManager::createNewPlayer(int id) {
    Hex point = generateCoord(this->MAP_SIZE);
    this->points.insert(std::pair<int,Hex>(id, point));
    return point;
}

void RenderManager::createAreaOfNewPlayer(Hex point, int id) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (abs(i + j) < 2) {
                Hex newPoint(point.q + i, point.r + j);
                this->areas.insert(std::pair<Hex, int>(newPoint,id));
            }
        }
    }
}

Hex RenderManager::generateCoord(int size) {
    Hex coord(generateNumber(size), generateNumber(size));
    return coord;
}

int RenderManager::generateNumber(int size) {
    srand((unsigned)time(nullptr));
    int number = rand() % (size * 2) - size;
    return number;
}
