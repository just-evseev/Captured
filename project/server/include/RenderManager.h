//
// Created by Ilya on 06/12/2018.
//

#ifndef SERVER_RENDERMANAGER_H
#define SERVER_RENDERMANAGER_H

#include "StructInit.h"

class RenderManager {
public:

    RenderManager();
    ~RenderManager();

    void acceptPlayer(int id);
    void getPlayerCoord(Move move, int id);

private:
    void createAreaOfNewPlayer(Hex point, int id);

    Hex generateCoord();
    int generateNumber();

    void personKiller(int id);
    void playerKiller(int playerId);

    void updatePersonArea(int id);

    const int MAP_SIZE = 10; // Размер карты (кастомизируется под поле на клиенте)

    Persons persons;
    Areas areas;
    Tails tails;
};

#endif //SERVER_RENDERMANAGER_H
