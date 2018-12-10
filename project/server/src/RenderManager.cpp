#include "../include/RenderManager.h"

RenderManager::RenderManager() = default;

RenderManager::~RenderManager() = default;

void RenderManager::acceptPlayer(int id) {
    Hex point = this->createNewPlayer(id);
    this->createAreaOfNewPlayer(point, id);
    Person person;
    person.id = id;
    person.state = 1;
    person.area_sq = 6;
    person.kills = 0;
    person.bonus_effect = 0;
    this->persons.insert(std::pair<int, Person>(id, person));
}

void RenderManager::getPlayerCoord(Move move, int id) {
    Hex point = this->points.at(id);
    CellState cellState(id, 1);
    switch (move) {
        case Move::UP:
            point.updateCoord(point.q, point.r - 1);
            cellState.updateCellState(id, 1);
            break;
        case Move::RIGHT_UP:
            point.updateCoord(point.q + 1, point.r - 1);
            cellState.updateCellState(id, 1);
            break;
        case Move::RIGHT_DOWN:
            point.updateCoord(point.q + 1, point.r);
            cellState.updateCellState(id, -1);
            break;
        case Move::DOWN:
            point.updateCoord(point.q, point.r + 1);
            cellState.updateCellState(id, -1);
            break;
        case Move::LEFT_DOWN:
            point.updateCoord(point.q - 1, point.r + 1);
            cellState.updateCellState(id, -1);
            break;
        case Move::LEFT_UP:
            point.updateCoord(point.q - 1, point.r);
            cellState.updateCellState(id, 1);
            break;
        default:
            break;
    }
    if (tails.count(point) != 0) { // Проверка на принадлежность кривым
        const auto detectId = tails.at(point).id;
        if (detectId == id) {
            this->personKiller(id);
            return;
        } else {
            this->playerKiller(detectId);
            persons.at(id).kills += 1;
        }
    }

    if (areas.count(point) != 0) { // Проверка на окончание работы с зоной
        if (areas.at(point) == id) {
            this->updatePersonArea(id);
        }
    }

    if (tails.at(this->points.at(id)).state != cellState.id) { // обрабатываю угол
        cellState.id = 0;
    }

    this->points.at(id) = point;

    this->tails.insert(std::pair<Hex, CellState>(point, cellState));
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

void RenderManager::personKiller(int id) { // в процессе разработки (самоубийство)
}

void RenderManager::playerKiller(int playerId) { // в процессе разработки (убийство другого игрока)
}

void RenderManager::updatePersonArea(int id) {
    auto counter = 0;
    for (int r = -MAP_SIZE; r <= 0; r++) {
        for (int q = -r - MAP_SIZE; q <= MAP_SIZE; q++) {
            int state = tails.at(Hex(q, r)).state;
            if (state == 0) {
                areas.at(Hex(q, r)) = id;
            } else if (abs(state) == 1) {
                counter += state;
            } else {
                puts("Error in updatePersonArea");
            }
            if (counter > 0) {
                areas.at(Hex(q, r)) = id;
            }
        }
    }

    for (int r = 1; r <= MAP_SIZE; r++) {
        for (int q = -MAP_SIZE; q <= MAP_SIZE - r; q++) {
            int state = tails.at(Hex(q, r)).state;
            if (state == 0) {
                areas.at(Hex(q, r)) = id;
            } else if (abs(state) == 1) {
                counter += state;
            } else {
                puts("Error in updatePersonArea");
            }
            if (counter > 0) {
                areas.at(Hex(q, r)) = id;
            }
        }
    }
}
