#include <iostream>

#include "../include/RenderManager.h"

RenderManager::RenderManager() = default;

RenderManager::~RenderManager() = default;

void RenderManager::acceptPlayer(int id) {
    Hex point = this->generateCoord();
    std::cout << "Получил id " << id << std::endl;
    Person person(point);
    this->persons.emplace(id, person);  // TODO: Реализовать взаиможействия с вектором координат в Person
    this->createAreaOfNewPlayer(point, id);
    std::cout << "Сгенерировал точку" << point.r << " " << point.q << " для " << id << std::endl;

}

void RenderManager::getPlayerCoord(Move move, int id) {
    Hex point = this->persons.at(id).point;

    CellState cellState(id, 1);
    std::cout << "Игрок " << id << " получил движение " << move << std::endl;
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

    auto t6 = this->areas.find(point); // TODO: Гуляешь по своей зоне
    auto isPersonTailEmpty = this->persons.at(id).playerTails.empty();
    if (t6 != this->areas.end()) { // Проверка на попадение в зону
        if (t6->second == id && isPersonTailEmpty) {

            std::cout << "Попал к себе в зону в точке " << t6->first.q << ":" << t6->first.r << std::endl;

            auto t7 = this->tails.find(point);
            if (t7 != this->tails.end()) {  // Проверка на убийство внутри своей зоны другого игрока
                auto detectId = t7->second.id;
                if (detectId != id) {
                    std::cout << "Бил убит игрок " << detectId << " игроком " << id << std::endl;
                    this->playerKiller(detectId);
                    this->persons.at(id).kills += 1;
                }
            } else {
                std::cout << "Новая точка " << point.q << ":" << point.r << " игрока " << id
                          << " в зоне, но не пересекает кривые других игроков" << std::endl;
            }

        } else if (t6->second == id && !isPersonTailEmpty) { // TODO: Попал к себе в зону, при этом вектор кривых не пуст

            std::cout << "Игрок " << id << " завершил зону, происходит объединение" << std::endl;
            this->updatePersonArea(id);

            auto t7 = this->tails.find(point);
            if (t7 != this->tails.end()) {  // Проверка на убийство внутри своей зоны другого игрока
                auto detectId = t7->second.id;
                if (detectId != id) {
                    std::cout << "Бил убит игрок " << detectId << " игроком " << id << std::endl;
                    this->playerKiller(detectId);
                    this->persons.at(id).kills += 1;
                }
            } else {
                std::cout << "Новая точка " << point.q << ":" << point.r
                          << " игрока " << id
                          << " захватила зону, но не пересекает кривые других игроков"
                          << std::endl;
            }

            this->persons.at(id).playerTails.clear();
        } else {
            auto t7 = this->tails.find(point);
            if (t7 != this->tails.end()) {  // Проверка на убийство внутри своей зоны другого игрока
                auto detectId = t7->second.id;
                if (detectId != id) {
                    std::cout << "Бил убит игрок " << detectId << " игроком " << id << std::endl;
                    this->playerKiller(detectId);
                    this->persons.at(id).kills += 1;
                } else {

                }
            } else {
                std::cout << "Новая точка " << point.q << ":" << point.r
                          << " игрока " << id
                          << " в другой зоне"
                          << std::endl;
            }
            this->persons.at(id).playerTails.push_back(point);
            this->tails.emplace(point, cellState); // Добавляем точку кривым
            std::cout << "Добавил кривую игрока " << id << " с состоянием " << cellState.state << std::endl;
        }
    } else { // TODO: Попал не в зону
        auto t7 = this->tails.find(point);
        if (t7 != this->tails.end()) {  // Проверка на убийство внутри своей зоны другого игрока
            auto detectId = t7->second.id;
            if (detectId != id) {
                std::cout << "Бил убит игрок " << detectId << " игроком " << id << std::endl;
                this->playerKiller(detectId);
                this->persons.at(id).kills += 1;
            } else {

            }
        } else {
            std::cout << "Новая точка " << point.q << ":" << point.r
                      << " игрока " << id
                      << " вне зоны"
                      << std::endl;
        }
        this->persons.at(id).playerTails.push_back(point);
        this->tails.emplace(point, cellState); // Добавляем точку кривым
        std::cout << "Добавил кривую игрока " << id << " с состоянием " << cellState.state << std::endl;
    }

    persons.at(id).point = point; //Обновляем точку человеку
    std::cout << "Добавил поинт игрока " << id << " " << point.q << ":" << point.r << std::endl;
}

void RenderManager::createAreaOfNewPlayer(Hex point, int id) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (abs(i + j) < 2) {
                this->areas.emplace(Hex(point.q + i, point.r + j), id);
                std::cout << "Новая точка " << point.q + i << ":" << point.r + j << " принадлежит " << id << std::endl;
                this->persons.at(id).playerArea.push_back(Hex(point.q + i, point.r + j));
            }
        }
    }

//    std::cout << std::endl << areas << std::endl;
}

Hex RenderManager::generateCoord() {
    Hex coord(this->generateNumber(), this->generateNumber());
    std::cout << "Сгенерирована координата нового игрока " << coord.r << ":" << coord.q << std::endl;
    return coord;
}

int RenderManager::generateNumber() {
    srand((unsigned)time(nullptr));
    int number = rand() % (this->MAP_SIZE * 2) - this->MAP_SIZE; // TODO: Все таки ранд работает не правильно
//    return number; // TODO: Вернуть назад
    return 0;
}

void RenderManager::personKiller(int id) { // TODO: в процессе разработки (самоубийство)
}

void RenderManager::playerKiller(int playerId) { // TODO: в процессе разработки (убийство другого игрока)
}

void RenderManager::updatePersonArea(int id) { // добавление полигона к полигону игрока
    std::cout << std::endl << "++++Начинаем цикл присоединения++++" << std::endl;
    printArea();
    printTails();
    QPlusState prevState(-1, -2);

    for (int r = -(this->MAP_SIZE); r <= 0; r++) {
        for (int q = -r - (this->MAP_SIZE); q <= (this->MAP_SIZE); q++) {
            auto it5 = tails.find(Hex(q, r));
            if (it5 != tails.end()) {
                int currState = it5->second.state;
                int currId = it5->second.id;
                int currQ = it5->first.q;
                if (currId == id) {
                    areas.emplace(Hex(q, r), id);
                    persons.at(id).playerArea.push_back(Hex(q, r));
                    if (prevState.q == -1) { // первая кривая игрока за проход
                        prevState.q = currQ;
                        prevState.state = currState;
                    } else {
                        if (prevState.state != currState) {
                            std::cout << prevState.q << " " << currQ << std::endl;
                            for (int i = prevState.q + 1; i < currQ; i++) {
                                areas.emplace(Hex(i, r), id);
                                persons.at(id).playerArea.push_back(Hex(i, r));
                            }
                            prevState.q = -1;
                        } else {
                            prevState.q = currQ;
                            prevState.state = currState;
                        }
                    }
                }
            }
        }
        prevState.q = -1;
    }

    for (int r = 1; r <= this->MAP_SIZE; r++) {
        for (int q = -(this->MAP_SIZE); q <= this->MAP_SIZE - r; q++) {
            auto it5 = tails.find(Hex(q, r));
            if (it5 != tails.end()) {
                int currState = it5->second.state;
                int currId = it5->second.id;
                int currQ = it5->first.q;
                if (currId == id) {
                    areas.emplace(Hex(q, r), id);
                    persons.at(id).playerArea.push_back(Hex(q, r));
                    if (prevState.q != -1) { // первая кривая игрока за проход
                        prevState.q = currQ;
                        prevState.state = currState;
                    } else {
                        if (prevState.state != currState) {
                            for (int i = prevState.q + 1; i < currQ; i++) {
                                areas.emplace(Hex(i, r), id);
                                persons.at(id).playerArea.push_back(Hex(i, r));
                            }
                            prevState.q = currQ;
                            prevState.state = currState;
                        } else {
                            prevState.q = currQ;
                            prevState.state = currState;
                        }
                    }
                }
            }
        }
        prevState.q = -1;
    }
    std::cout << std::endl;
    printArea();
    printTails();
}

void RenderManager::printArea () {
    std::cout << std::endl << "print area" << std::endl;
    for (auto it = this->areas.begin(); it != this->areas.end(); ++it)
    {
        std::cout << it->first.q << ":" << it->first.r << " " << it->second << std::endl;
    }
}

void RenderManager::printTails () {
    std::cout << std::endl << "print tails" << std::endl;
    for (auto it = this->tails.begin(); it != this->tails.end(); ++it)
    {
        std::cout << it->first.q << ":" << it->first.r << " id = " << it->second.id << ":" << it->second.state << std::endl;
    }
}
