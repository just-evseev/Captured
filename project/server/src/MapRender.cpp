#include <time.h>
#include <stdlib.h>
#include <vector>

#include "../include/MapRender.h"

/* Я использую для генератора случайных чисел точность 0,0001 */

MapRender::MapRender() {
    
}

MapRender::~MapRender() {
    
}

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

Coord MapRender::generateCoord() {
    Coord coord;
    coord.x = generateNumber();
    coord.y = generateNumber();
    return coord;
}

float MapRender::generateNumber() {
    srand((unsigned)time(0));
    float number = (float)(rand() % 10001) / 10000;
    return number;
}

bool MapRender::isWayEmpty(VectorOfCoord arrayOfWay) {
    return arrayOfWay.empty();
}

void MapRender::updatePlayerArea() { // **************Дописать***************
    Coord backCoord = this->arrayOfWay.back();
    int indBackCoordInPlayerAreaArr = searchInCoordVector(backCoord); // последний
    if (indBackCoordInPlayerAreaArr == -1) {
        puts("updatePlayerAreaError");
        return;
    }
    
    Coord frontCoord = this->arrayOfWay.front();
    int indFrontCoordInPlayerAreaArr = searchInCoordVector(frontCoord); // первый
    if (indFrontCoordInPlayerAreaArr == -1) {
        puts("updatePlayerAreaError");
        return;
    }
}

int MapRender::searchInCoordVector(Coord coord){
    int mem = 0;
    for (Coord p : this->arrayOfAreaCoord) {
        if (p.x == coord.x && p.y == coord.y) {
            return mem;
        }
        mem++;
    }
    return -1;
}

// This code need in tests, я просто скопировал его с https://habr.com/post/125356/
bool MapRender::isInArea(const Coord test) {
    
    static const int q_patt[2][2]= { {0,1}, {3,2} };
    
    if (this->arrayOfAreaCoord.size()<3) return false;
    
    std::vector<Coord>::const_iterator end=this->arrayOfAreaCoord.end();
    Coord pred_pt=this->arrayOfAreaCoord.back();
    pred_pt.x-=test.x;
    pred_pt.y-=test.y;
    
    int pred_q=q_patt[pred_pt.y<0][pred_pt.x<0];
    
    int w=0;
    
    for(std::vector<Coord>::const_iterator iter=this->arrayOfAreaCoord.begin();iter!=end;++iter)
    {
        Coord cur_pt = *iter;
        
        cur_pt.x-=test.x;
        cur_pt.y-=test.y;
        
        int q=q_patt[cur_pt.y<0][cur_pt.x<0];
        
        switch (q-pred_q)
        {
            case -3:++w;break;
            case 3:--w;break;
            case -2:if(pred_pt.x*cur_pt.y>=pred_pt.y*cur_pt.x) ++w;break;
            case 2:if(!(pred_pt.x*cur_pt.y>=pred_pt.y*cur_pt.x)) --w;break;
        }
        
        pred_pt = cur_pt;
        pred_q = q;
        
    }
    
    return w!=0;
    
}
