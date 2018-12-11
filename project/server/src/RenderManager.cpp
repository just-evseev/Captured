#include "../include/RenderManager.h"

RenderManager::RenderManager() = default;

RenderManager::~RenderManager() = default;

void RenderManager::acceptPlayer(int id) {
    Hex point = this->createNewPlayer(id);
    puts("получил id");
    this->createAreaOfNewPlayer(point, id);
    Person person(point);
    this->persons.insert(std::pair<int, Person>(id, person));
}

void RenderManager::getPlayerCoord(Move move, int id) {
    Hex point = this->persons.at(id).point;

    CellState cellState(id, 1);
    switch (move) {
        case Move::UP:
            point.updateCoord(point.q, point.r - 1);
            cellState.state = 1;
            break;
        case Move::RIGHT_UP:
            point.updateCoord(point.q + 1, point.r - 1);
            cellState.state = 1;
            break;
        case Move::RIGHT_DOWN:
            point.updateCoord(point.q + 1, point.r);
            cellState.state = -1;
            break;
        case Move::DOWN:
            point.updateCoord(point.q, point.r + 1);
            cellState.state = -1;
            break;
        case Move::LEFT_DOWN:
            point.updateCoord(point.q - 1, point.r + 1);
            cellState.state = -1;
            break;
        case Move::LEFT_UP:
            point.updateCoord(point.q - 1, point.r);
            cellState.state = 1;
            break;
    }

    auto t3 = tails.find(point);
    if (t3 != tails.end()) {  // Проверка на принадлежность кривым
        auto detectId = t3->second.id;
        if (detectId == id) {
            this->personKiller(detectId);
            return;
        } else {
            this->playerKiller(detectId);
            persons.at(id).kills += 1;
        }
    }

    auto t4 = areas.find(point);
    if (t4 != areas.end()) { // Проверка на окончание работы с зоной
        if (areas.at(point) == id) {
            this->updatePersonArea(id);
        }
    }

    auto t5 = tails.find(persons.at(id).point);
    if (t5->second.state != cellState.id) { // Обрабатываю угол
        cellState.id = 0;
    } else {
        puts("Ошибка в обработке острого угла");
    }

    persons.at(id).point = point; // Добавляем точку человеку
    this->tails.emplace(point, cellState); // Добавляем точку кривым
}

Hex RenderManager::createNewPlayer(int id) {
    Hex point = this->generateCoord();
    this->persons.emplace(id, Person(point));
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

Hex RenderManager::generateCoord() {
    Hex coord(this->generateNumber(), this->generateNumber());
    return coord;
}

int RenderManager::generateNumber() {
    srand((unsigned)time(nullptr));
    int number = rand() % (this->MAP_SIZE * 2) - this->MAP_SIZE;
    return number;
}

void RenderManager::personKiller(int id) { // в процессе разработки (самоубийство)
}

void RenderManager::playerKiller(int playerId) { // в процессе разработки (убийство другого игрока)
}

void RenderManager::updatePersonArea(int id) {
    auto counter = 0;
    for (int r = -(this->MAP_SIZE); r <= 0; r++) {
        for (int q = -r - (this->MAP_SIZE); q <= (this->MAP_SIZE); q++) {
            auto it5 = tails.find(Hex(q, r));
            if (it5 != tails.end()) {
                int state = it5->second.state;
                if (state == 0) {
                    areas.emplace(Hex(q, r), id);
                } else if (abs(state) == 1) {
                    counter += state;
                } else {
                    puts("Error in updatePersonArea");
                }
                if (abs(counter) > 0) {
                    areas.emplace(Hex(q, r), id);
                }
            }
        }
        if (counter != 0) {
            puts("Error in updatePersonArea");
            counter = 0;
        }
    }

    for (int r = 1; r <= this->MAP_SIZE; r++) {
        for (int q = -(this->MAP_SIZE); q <= this->MAP_SIZE - r; q++) {
            auto it5 = tails.find(Hex(q, r));
            if (it5 != tails.end()) {
                int state = it5->second.state;
                if (state == 0) {
                    areas.emplace(Hex(q, r), id);
                } else if (abs(state) == 1) {
                    counter += state;
                } else {
                    puts("Error in updatePersonArea");
                }
                if (abs(counter) > 0) {
                    areas.emplace(Hex(q, r), id);
                }
            }
        }
        if (counter != 0) {
            puts("Error in updatePersonArea");
            counter = 0;
        }
    }
}
