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
    Hex createNewPlayer(int id);
    void createAreaOfNewPlayer(Hex point, int id);

    Hex generateCoord(int size);
    int generateNumber(int size);

    const int MAP_SIZE = 10;

    Points points;
    Areas areas;
    Tails tails;
};


#endif //SERVER_RENDERMANAGER_H
