//
// Created by Ilya on 06/12/2018.
//

#ifndef SERVER_RENDERMANAGER_H
#define SERVER_RENDERMANAGER_H

#include <SFML/Network.hpp>
#include "StructInit.h"

class RenderManager {
public:

    RenderManager();
    ~RenderManager();

    void acceptPlayer(int id);

    void updateAt(int id);

    void updateEnum(int id, Move move);

    void printArea();
    void printTails();

    Persons persons;
    Tails tails;
    Areas areas;
    std::vector<int> killerList;

private:
    void createAreaOfNewPlayer(Hex point, int id);

    Hex generateCoord();
    int generateNumber();

    void playerKiller(int playerId);

    void updatePersonArea(int id);

    const int MAP_SIZE = 10; // Размер карты (кастомизируется под поле на клиенте)

};

#endif //SERVER_RENDERMANAGER_H
